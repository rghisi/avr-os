/*
 * Frame.h
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#ifndef SRC_PACKET_H_
#define SRC_PACKET_H_

#include "cstdint"

class Packet {
public:
    Packet(uint8_t destination, uint8_t source, uint16_t id, uint8_t service, uint8_t payload[], uint8_t payloadLength);
    Packet(uint8_t destination, uint8_t source, uint16_t id, uint8_t service, uint8_t crc, uint8_t payload[], uint8_t payloadLength);
    ~Packet();
    bool isValid();
    [[nodiscard]] uint8_t source() const;
    [[nodiscard]] uint8_t destination() const;
    [[nodiscard]] uint8_t length() const;
    [[nodiscard]] uint16_t id() const;
    [[nodiscard]] uint8_t service() const;
    [[nodiscard]] uint8_t crc() const;
    uint8_t* payload();
    [[nodiscard]] uint8_t payloadLength() const;
    static const uint8_t START_INDEX = 0;
    static const uint8_t DESTINATION_INDEX = 1;
    static const uint8_t SOURCE_INDEX = 2;
    static const uint8_t LENGTH_INDEX = 3;
    static const uint8_t ID_MSB_INDEX = 4;
    static const uint8_t ID_LSB_INDEX = 5;
    static const uint8_t SERVICE_INDEX = 6;
    static const uint8_t CRC_INDEX = 7;
    static const uint8_t HEADER_SIZE = 8;
    static const uint8_t PACKET_START_SYMBOL = 0xA5;
private:
    uint8_t sourceAddress;
    uint8_t destinationAddress;
    uint8_t packetLength;
    uint16_t packetId;
    uint8_t serviceId;
    uint8_t *payloadBytes;
    uint8_t packetCrc;
    uint8_t calculateCrc();
};

#endif /* SRC_PACKET_H_ */
