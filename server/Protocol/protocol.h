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

class Protocol {
public:
    // Header fields


    // Constructor for creating a Protocol object
    Protocol(MessageType msgT, const std::string& name, const std::string& payload)
        : msgType(msgT), name(name), payload(payload) {}

    // Default constructor
    Protocol() : msgType(MessageType::MESSAGE_TRANSFER), name(""), payload("") {}

    // Constructor for deserialization
    Protocol(const std::string& data) {
        deserialize(data);
    }

    // Serialize the Protocol object to a string
    std::string serialize() const;

    // Deserialize a string to a Protocol object
    void deserialize(const std::string& data);

    MessageType getMsgType() const;
    void setMsgType(MessageType newMsgType);

    std::string getName() const;
    void setName(const std::string &newName);

    std::string getPayload() const;
    void setPayload(const std::string &newPayload);

private:
    MessageType msgType;  // Type of message
    std::string name;     // Name or identifier (e.g., command name)
    std::string payload;  // Content of the message (text or binary as a string)
};

#endif // Protocol_H
