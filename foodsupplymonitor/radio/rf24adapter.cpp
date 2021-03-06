#include "rf24adapter.h"

/*! \file radio.cpp
    \brief Implementation of radio communication.
*/

/*! \brief Method to setup the radio.
*/
void RF24Adapter::setupRadio() {
  minPayloadSize = MIN_PAYLOAD_SIZE;
  maxPayloadSize = MAX_RCV_PAYLOAD_SIZE;
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


  radio.openWritingPipe(radioPipes[1]);
  // Open pipe number 1 (1-5)
  radio.openReadingPipe(1, radioPipes[0]); 

  radio.startListening();
}

/*! \brief Constructor
	\param[in] pipes[2] Pipes/addresses of the two nodes to communicate.
	\param[in] packer pointer to a packer reference.
*/
RF24Adapter::RF24Adapter(const uint64_t pipes[2], IPacker *packer) :
  radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ),
  packer(packer)
{
  radioPipes[0] = pipes[0];
  radioPipes[1] = pipes[1];
  setupRadio();
}

/*! \brief Destructor
*/
RF24Adapter::~RF24Adapter() {
}

/*! \brief Method to receive data.
	\param[out] scaleId The scale ID.
	\param[out] scaleId The message type.
	\param[out] data The data.
	\returns 0 on success and 1 otherwise.
*/
uint8_t RF24Adapter::receive(int *scaleId, uint8_t *messageType, int *data) {
  printf("Radio communication - Ready to receive\n");
  // If there is data ready
  radio.startListening();

  while (1) {
    if (radio.available()) {

      uint8_t len;
      // Dump the payload until we've received everything
      while (radio.available()) {
        // printf("Reading...\n");
        // Fetch the payload, and see if this was the last one
        len = radio.getDynamicPayloadSize();
        radio.read(receivePayload, len);

        // Put a zero at the end for easy printing
        receivePayload[len] = 0;

        // Print to stdout
        //printf("Got payload size=%i value=%s\n\r", len, receivePayload);
      }
      radio.stopListening();
      
      packer->unpack(receivePayload, scaleId, messageType, data);

      // Checkfor invalid message type
      if (*messageType==RADIO_RCV_MSG_TYPE_MEASUREMENT  
	|| *messageType==RADIO_RCV_MSG_TYPE_POWER_DOWN_REQ) {
        return 0;
      } else {
	return 1;
      }
    }
  }
}

/*! \brief Method to set the update frequency.
	\param[in] scaleId The scale ID.
	\param[in] updateFrequency The update frequency.
	\returns 0 on success and 1 otherwise.
*/
uint8_t RF24Adapter::setUpdateFrequency(const int scaleId, const int updateFrequency) {
  if (scaleId<0 || scaleId>MAX_CONTAINERS) {
    return 1;
  } else if (updateFrequency<0) {
    return 1;
  }

  radio.stopListening();

  packer->pack(sendPayload, scaleId, RADIO_SEND_MSG_TYPE_SET_UPDATE_FREQUENCY, updateFrequency);
  radio.write(sendPayload, MAX_SEND_PAYLOAD_SIZE);

  radio.startListening();
  return 0;
}

/*! \brief Method send a power down response.
	\param[in] scaleId The scale ID.
	\returns 0 on success and 1 otherwise.
*/
uint8_t RF24Adapter::powerDown(const int scaleId) {
  if (scaleId<0 || scaleId>MAX_CONTAINERS) {
    return 1;
  }

  radio.stopListening();

  packer->pack(sendPayload, scaleId, RADIO_SEND_MSG_TYPE_POWER_DOWN_RSP);

  radio.write(sendPayload, MAX_SEND_PAYLOAD_SIZE);

  radio.startListening();
  return 0;
}
