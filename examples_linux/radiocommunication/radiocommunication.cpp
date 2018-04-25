#include "radiocommunication.h"

//class IRadioCommunication;

void RadioCommunication::setupRadio() {
  minPayloadSize = MIN_PAYLOAD_SIZE;
  maxPayloadSize = MAX_PAYLOAD_SIZE;
  payloadSizeIncrementsBy = PAYLOAD_SIZE_INCREMENTS_BY;
  nextPayloadSize = minPayloadSize;

  /****************** Raspberry Pi ***********************/

  // Radio CE Pin, CSN Pin, SPI Speed
  // See http://www.airspayce.com/mikem/bcm2835/group__constants.html#ga63c029bd6500167152db4e57736d0939 and the related enumerations for pin information.

  // Setup for GPIO 22 CE and CE0 CSN with SPI Speed @ 4Mhz
  //RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_4MHZ);

  // NEW: Setup for RPi B+
  //RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);

  // Setup for GPIO 15 CE and CE0 CSN with SPI Speed @ 8Mhz
  //RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

  /*** RPi Alternate ***/
  //Note: Specify SPI BUS 0 or 1 instead of CS pin number.
  // See http://tmrh20.github.io/RF24/RPi.html for more information on usage

  //RPi Alternate, with MRAA
  //RF24 radio(15,0);

  //RPi Alternate, with SPIDEV - Note: Edit RF24/arch/BBB/spi.cpp and  set 'this->device = "/dev/spidev0.0";;' or as listed in /dev
  //RF24 radio(22,0);
  

  // Setup and configure rf radio
  // Begin operation of chip (must called before any other methods)
  radio.begin();
  radio.enableDynamicPayloads();
  // Waits 5*250us between retries. Retry 15 times
  radio.setRetries(5, 15);
  // Print debugging info t stdout
  radio.printDetails();


  radio.openWritingPipe(pipeOther);
  // Open pipe number 1 (1-5)
  radio.openReadingPipe(1, pipeMe); 

  radio.startListening();
}

RadioCommunication::RadioCommunication(const uint64_t pipeMe, const uint64_t pipeOther) :
  radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ),
  pipeMe(pipeMe),
  pipeOther(pipeOther)  
{
  setupRadio();
}

RadioCommunication::~RadioCommunication() {
}

void RadioCommunication::send(char *sendPayload) {
}

//void RadioCommunication::receive(char *msg) {
uint8_t RadioCommunication::receive(char *receivePayload) {
  printf("RadioCommunication - Ready to receive\n");
  // If there is data ready
  //radio.printDetails();
  radio.startListening();

  while (1) {
    if (radio.available()) {

      uint8_t len;
      // Dump the payload until we've received everything
      while (radio.available()) {
        printf("Reading...\n");
        // Fetch the payload, and see if this was the last one
        len = radio.getDynamicPayloadSize();
        radio.read(receivePayload, len);

        // Put a zero at the end for easy printing
        receivePayload[len] = 0;

        // Print to stdout
        //printf("Got payload size=%i value=%s\n\r", len, receivePayload);
      }
      radio.stopListening();
      return len;
    }
  }
}
