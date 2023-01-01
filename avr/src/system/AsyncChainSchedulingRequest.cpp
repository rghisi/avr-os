//
// Created by ghisi on 12/31/22.
//

#include "AsyncChainSchedulingRequest.h"

AsyncChainSchedulingRequest::AsyncChainSchedulingRequest(AsyncChain* asyncChain)
: Message(MessageType::ASYNC_CHAIN_SCHEDULED) {
    this->asyncChain = asyncChain;
}

AsyncChainSchedulingRequest::~AsyncChainSchedulingRequest() = default;
