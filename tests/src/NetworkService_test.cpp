/*
 * Frame_test.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include <gtest/gtest.h>
#include "NetworkInterfaceMock.cpp"
#include "NetworkService.cpp"

TEST(NetworkService, CreateService) {
	uint8_t address = 0xA;
	NetworkInterfaceMock mockInterface;
	NetworkService networkService = NetworkService(address);//, &mockInterface);
	uint8_t destination = 0x0B;
	uint8_t data[] = "abcde";
	uint16_t dataSize = 6;
	networkService.send(destination, data, dataSize);
}













