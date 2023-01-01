//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_ASYNCCHAINSCHEDULINGREQUEST_H
#define AVR_ASYNCCHAINSCHEDULINGREQUEST_H


#include "Message.h"
#include "AsyncChain.h"

class AsyncChainSchedulingRequest: public Message {
public:
    AsyncChainSchedulingRequest(AsyncChain* asyncChain);
    ~AsyncChainSchedulingRequest() override;
    AsyncChain* asyncChain;
};


#endif //AVR_ASYNCCHAINSCHEDULINGREQUEST_H
