//
// Created by ghisi on 12/31/22.
//

#include "AsyncChainSchedulingRequest.h"

AsyncChainSchedulingRequest::AsyncChainSchedulingRequest(AsyncChain* asyncChain)
: Event(EventType::ASYNC_CHAIN_SCHEDULED) {
    this->asyncChain = asyncChain;
}

AsyncChainSchedulingRequest::~AsyncChainSchedulingRequest() = default;
