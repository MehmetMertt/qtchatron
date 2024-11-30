#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>

/*
 *
 * MessageType (2 bytes)
 * nameLength (4 bytes)
 * name (variable length)
 * payloadLength (4 bytes)
 * payload (variable length)
 *
 */

enum MessageType : uint16_t {
    FILE_TRANSFER = 0x01,
    MESSAGE_TRANSFER = 0x02,
    COMMAND_TRANSFER = 0x03
};

class protocol {
public:
    // Header fields
    MessageType msgType;  // Type of message
    std::string name;     // Name or identifier (e.g., command name)
    std::string payload;  // Content of the message (text or binary as a string)

    // Constructor for creating a protocol object
    protocol(MessageType msgT, const std::string& name, const std::string& payload)
        : msgType(msgT), name(name), payload(payload) {}

    // Default constructor
    protocol() : msgType(MessageType::MESSAGE_TRANSFER), name(""), payload("") {}

    // Constructor for deserialization
    protocol(const std::string& data) {
        deserialize(data);
    }

    // Serialize the protocol object to a string
    std::string serialize() const;

    // Deserialize a string to a protocol object
    void deserialize(const std::string& data);
};

#endif // PROTOCOL_H
