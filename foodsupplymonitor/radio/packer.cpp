#include "packer.h"

/*! \file packer.cpp
    \brief Implementation of pack and unpack functionality.
*/

/*! \brief Destructor.
*/
Packer::~Packer() 
{}

/*! \brief Method to pack data.
	\param[out] payload a char array with the packed data.
	\param[in] scaleId The scale ID.
	\param[in] scaleId The message type.
	\param[in] updateFrequency The update frequency.
	\returns 0 on success and 1 otherwise.
*/
uint8_t Packer::pack(char *payload, const int scaleId, const uint8_t messageType, const int updateFrequency) {
  if (scaleId < 0 || scaleId > MAX_CONTAINERS) {
    return 1;
  } else if (updateFrequency < 0) {
    return 1;
  }

  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  payload[3] = updateFrequency>>24;
  payload[4] = updateFrequency>>16;
  payload[5] = updateFrequency>>8;
  payload[6] = updateFrequency;
  return 0;
}

/*! \brief Method to pack data.
	\param[out] payload a char array with the packed data.
	\param[in] scaleId The scale ID.
	\param[in] scaleId The message type.
	\returns 0 on success and 1 otherwise.
*/
uint8_t Packer::pack(char *payload, const int scaleId, const uint8_t messageType) {
  if (scaleId < 0 || scaleId > MAX_CONTAINERS) {
    return 1;
  }

  payload[0] = messageType;
  payload[1] = scaleId>>8;
  payload[2] = scaleId;
  return 0;
}

/*! \brief Method to unpack data.
	\param[in] payload a char array with the packed data.
	\param[out] scaleId The scale ID.
	\param[out] messageType The message type.
	\param[out] data The data.
	\returns 0 on success and 1 otherwise.
*/
uint8_t Packer::unpack(const char *payload, int *scaleId, uint8_t *messageType, int *data) {
  *scaleId = payload[2] | payload[1]<<8;

  if (*scaleId < 0 || *scaleId > MAX_CONTAINERS) {
    return 1;
  }

  *messageType = payload[0];

  *data = payload[3]<<24 | payload[4]<<16 | payload[5]<<8 | payload[6]; 
  return 0;
}
