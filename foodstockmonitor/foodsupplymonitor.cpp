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
#include "networkfacade/networkfacade.h"
//#include "radiocommunication/radiocommunication.h"


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
//// RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

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


//const int min_payload_size = 4;
//const int max_payload_size = 32;
//const int payload_size_increments_by = 1;
//int next_payload_size = min_payload_size;


//char receive_payload[max_payload_size+1]; // +1 to allow room for a terminating NULL char


/*
void setupRadio() {
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(5, 15);
  radio.printDetails();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
}*/

int main(int argc, char** argv){
  //RadioCommunication *radio = new RadioCommunication(0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL);

  NetworkFacade *networkFacade = new NetworkFacade(pipes);//0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL);

  //IDatabase *db = new FirebaseAdapter;
  //cJSON *reply = db->getContainerItem(1);
  //cJSON *reply = db->getContainerState(2);
  //cJSON *reply = db->getUpdateFrequency(3);
  //cJSON *reply = db->setMaximumCapacity(0, 12.56);
  //cJSON *reply = db->setEmptyContainerWeight(1, 4.33);
  //cJSON *reply = db->setMeasurement(1, 33.87);
  //cJSON *reply = db->createContainerItem();

  //char *res = cJSON_Print(reply);
  //printf("Reply: %s\n", res);

  // Print preamble:
  cout << "Welcome to Food Supply Monitor\n";

  // Setup and configure rf radio
  // setupRadio();

  networkFacade->handleNetwork();

  //char receivePayload[32+1]; 
  //radio->receive(receivePayload);
  //networkFacade->handleNetwork();

  delete networkFacade;
}
