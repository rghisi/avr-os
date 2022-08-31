/*
 * Network.h
 *
 *  Created on: Aug 29, 2022
 *      Author: ghisi
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_
#include <stdint.h>
//#include "NetworkInterface.h"

class NetworkService {
public:
	NetworkService(uint8_t address);//, NetworkInterface* networkInterface);
	void send(uint8_t destination, uint8_t* data, uint16_t dataSize);
};

#endif /* SRC_NETWORK_H_ */
