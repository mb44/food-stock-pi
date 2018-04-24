#include "radiocommunicationfacade.h"


RadioCommunicationFacade::RadioCommunicationFacade(const uint64_t addrMe, const uint64_t addrOther) 
	: addrMe(addrMe),
	  addrOther(addrOther)
{
  radio = new RadioCommunication(0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL);
}

RadioCommunicationFacade::~RadioCommunicationFacade() {
}

void RadioCommunicationFacade::handleRadioCommunication() {
  char receivePayload[32+1];

  printf("Handle radio communication\n");
  while (1) {
    radio->receive(receivePayload);
  }
}
