/*
 * Frame.h
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#ifndef SRC_PACKET_H_
#define SRC_PACKET_H_

#include <stdint.h>
#include <stdio.h>

class Packet {

public:
    Packet(uint8_t destination, uint8_t source, uint8_t id,
           uint8_t totalFragments, uint8_t fragment, uint8_t payload[],
           uint8_t payloadSize);

    explicit Packet(uint8_t *packetData);
    ~Packet();
    uint8_t next();
    bool hasNext();
    void reset();
    bool checkCrc();
    static const uint8_t PACKET_START = 0xA5;
    static const uint8_t HEADER_SIZE = 7;
    static const uint8_t CRC_SIZE = 1;
private:
    void copyPayload(const uint8_t *data, uint8_t size);
    void copyPacketData(const uint8_t *inputData, uint8_t size);
    void addCrc();
    uint8_t index;
    uint8_t packetSize;
    uint8_t *packetData;
};

#endif /* SRC_PACKET_H_ */
