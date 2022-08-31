#include <gmock/gmock.h>
#include "NetworkInterface.h"

class NetworkInterfaceMock: public NetworkInterface {
public:
	MOCK_METHOD(bool, pushToSendQueue, (Packet* packet), (override));
	MOCK_METHOD(bool, sendQueueIsEmpty, (), (override));
	MOCK_METHOD(bool, receiveQueueIsEmpty, (), (override));
	MOCK_METHOD(bool, popFromReceiveQueue, (Packet* packet), (override));
};
