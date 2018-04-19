/*
	TMRh20 2014 - Optimized RF24 Library Fork
*/

/**
 * Food Supply Monitor application for Raspberry Pi
 *
 * Payloads can be of a varying (dynamic) size.
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
//#include <string>
#include "../RF24.h"

// Morten's includes
#include <stdio.h>
#include <stdlib.h>
#include "database/firebaseadapter.h"

using namespace std;
//
// Hardware configuration
// Configure the appropriate pins for your connections

/****************** Raspberry Pi ***********************/

// Radio CE Pin, CSN Pin, SPI Speed
// See http://www.airspayce.com/mikem/bcm2835/group__constants.html#ga63c029bd6500167152db4e57736d0939 and the related enumerations for pin information.

// Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
//RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

// NEW: Setup for RPi B+
//RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

// Setup for GPIO 15 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

/*** RPi Alternate ***/
//Note: Specify SPI BUS 0 or 1 instead of CS pin number.
// See http://tmrh20.github.io/RF24/RPi.html for more information on usage

//RPi Alternate, with MRAA
//RF24 radio(15,0);

//RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
//RF24 radio(22,0);


/****************** Linux (BBB,x86,etc) ***********************/

// See http://tmrh20.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV

// Setup for ARM(Linux) devices like BBB using spidev (default is "/dev/spidev1.0" )
//RF24 radio(115,0);

//BBB Alternate, with mraa
// CE pin = (Header P9, Pin 13) = 59 = 13 + 46 
//Note: Specify SPI BUS 0 or 1 instead of CS pin number. 
//RF24 radio(59,0);

/**************************************************************/

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };


const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 1;
const int id_token_size = 945;
int next_payload_size = min_payload_size;

char receive_payload[max_payload_size+1]; // +1 to allow room for a terminating NULL char

char id_token[id_token_size];

void get_id_token(void);

void setupRadio() {
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(5, 15);
  radio.printDetails();

  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
}

int main(int argc, char** argv){
  IDatabase *db = new FirebaseAdapter;
  cJSON *reply = db->getContainerItem(1);

  char *res = cJSON_Print(reply);
  printf("Containers: %s\n", res);
  delete db;
  // Print preamble:
  cout << "Welcome to Food Supply Monitor\n";

  // Setup and configure rf radio
  setupRadio();

  // forever loop, listen for incoming messages
  while (1) {
    //FILE *fpipe;
    //char *command = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8 -H 'Content-Type: application/json' --data-binary '{\"email\":\"mortenbeuchert@gmail.com\",\"password\":\"123456\",\"returnSecureToken\":true}'";
    //char *command = "curl -X PUT -d '{ \"measurement\": \"from pi\" }' 'https://foodwastereduction-6ca48.firebaseio.com/raspberri-pi/data.json?auth=eyJhbGciOiJSUzI1NiIsImtpZCI6IjZlYThhZmIwMjFjMjEzMDhjNzkzMDI2ZTMzNDA4ZGI3MDc2ODc0MWEifQ.eyJpc3MiOiJodHRwczovL3NlY3VyZXRva2VuLmdvb2dsZS5jb20vZm9vZHdhc3RlcmVkdWN0aW9uLTZjYTQ4IiwiYXVkIjoiZm9vZHdhc3RlcmVkdWN0aW9uLTZjYTQ4IiwiYXV0aF90aW1lIjoxNTIyNzUyMTEzLCJ1c2VyX2lkIjoiSHF6Y1FXUXV4aWIzQ2FEV3FSWVVMb1lySGowMyIsInN1YiI6IkhxemNRV1F1eGliM0NhRFdxUllVTG9ZckhqMDMiLCJpYXQiOjE1MjI3NTIxMTMsImV4cCI6MTUyMjc1NTcxMywiZW1haWwiOiJtb3J0ZW5iZXVjaGVydEBnbWFpbC5jb20iLCJlbWFpbF92ZXJpZmllZCI6ZmFsc2UsImZpcmViYXNlIjp7ImlkZW50aXRpZXMiOnsiZW1haWwiOlsibW9ydGVuYmV1Y2hlcnRAZ21haWwuY29tIl19LCJzaWduX2luX3Byb3ZpZGVyIjoicGFzc3dvcmQifX0.H6nELd3HLxBqyTpw3djnz_2dDivSuAgWz27kt-s2KGfzM6mzdxNewrkId2qL3g8WFPTzlCpncxnFp_Z5AOiGPHHU3xxCGQUxt1KyYvSbZniqnPz9asvpQJq6gOESKb66ValBeMJhGq-asCGGsZsNOMVZ7vIOwQHDUlzCZLScnYpb20EXb2aPbJBUwDEDGns5aNGnmQ8ZDUY5PHKqsxHyCld5oHqhCV2KWegBadlH5vi_9TvnEQQnhXgShK-iFahhNOAJQHXsjoJ6k3nK-SfFhtpWR88ffu7wy46W7_YRBHHS-zekMuzDkiKvyYF5eTU0yZsikINzYhkagGfyoMTaZg'";
    //char c = 0;


    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      uint8_t len;

      while (radio.available())
      {
        // TODO
        // 1. Receive message
        // 2. Inpterpret message
        // 3. ACK and talk to Firebase

        // Fetch the payload, and see if this was the last one.
	len = radio.getDynamicPayloadSize();
	radio.read( receive_payload, len );

	// Put a zero at the end for easy printing
	receive_payload[len] = 0;

	// Spew it
	printf("Got payload size=%i value=%s\n\r",len,receive_payload);
	// Send to firebase
	if (receive_payload[len-1] == '2') {
	  cout << "Received a 2" << endl;
	  get_id_token();
	}
      }

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      radio.write( receive_payload, len );
      printf("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
}


void get_id_token(void) {
  FILE *fpipe;
  const char *command = "curl https://www.googleapis.com/identitytoolkit/v3/relyingparty/verifyPassword?key=AIzaSyBxlo2I0gI-2c5nb3w9feXabKInEvVotj8 -H 'Content-Type: application/json' --data-binary '{\"email\":\"mortenbeuchert@gmail.com\",\"password\":\"123456\",\"returnSecureToken\":true}'";
  char c = 0;

  if (0 == (fpipe = (FILE*)popen(command, "r")))
  {
    perror("popen() failed");
    exit(1);
  }

  while (fread(&c, sizeof c, 1, fpipe))
  {
    printf("%c", c);
  }

  pclose(fpipe);
}
