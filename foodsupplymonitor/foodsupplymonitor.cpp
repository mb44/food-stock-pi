/*
	TMRh20 2014 - Optimized RF24 Library Fork
*/

/**
 * Food Supply Monitor application for Raspberry Pi
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "../RF24.h"
#include <stdio.h>
#include <stdlib.h>
#include "networkfacade/networkfacade.h"
#include "radio/packer.h"
#include "database/auth.h"
#include "database/firebaseadapter.h"
#include "database/resthandler.h"

using namespace std;

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

int main(int argc, char** argv){
  IPacker *packer = new Packer;
  IRadio *radio = new RF24Adapter(pipes, packer);  
  IRESTHandler *rest =  new RESTHandler;
  IAuth *auth = new Auth(rest);
  IDatabase *db = new FirebaseAdapter(auth, rest, "firebaseConfig.txt");
  INetworkFacade *networkFacade = new NetworkFacade(radio, db);

  // Print preamble:
  cout << "Welcome to Food Supply Monitor\n";

  networkFacade->handleNetwork();

  delete auth;
  delete rest;
  delete packer;
  delete radio;
  delete db;
  delete networkFacade;
}
