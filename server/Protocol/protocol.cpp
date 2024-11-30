#include "protocol.h"

std::string protocol::serialize() const {
    std::string serializedData;

    // Serialize MessageType (2 bytes)
    uint16_t type = static_cast<uint16_t>(msgType);
    serializedData.push_back(static_cast<char>((type >> 8) & 0xFF)); // High byte
    serializedData.push_back(static_cast<char>(type & 0xFF));        // Low byte

    // Serialize the name length (4 bytes)
    uint32_t nameLength = name.size();
    serializedData.push_back(static_cast<char>((nameLength >> 24) & 0xFF));
    serializedData.push_back(static_cast<char>((nameLength >> 16) & 0xFF));
    serializedData.push_back(static_cast<char>((nameLength >> 8) & 0xFF));
    serializedData.push_back(static_cast<char>(nameLength & 0xFF));

    // Serialize the name
    serializedData.append(name);

    // Serialize the payload length (4 bytes)
    uint32_t payloadLength = payload.size();
    serializedData.push_back(static_cast<char>((payloadLength >> 24) & 0xFF));
    serializedData.push_back(static_cast<char>((payloadLength >> 16) & 0xFF));
    serializedData.push_back(static_cast<char>((payloadLength >> 8) & 0xFF));
    serializedData.push_back(static_cast<char>(payloadLength & 0xFF));

    // Serialize the payload
    serializedData.append(payload);

    return serializedData;
}

void protocol::deserialize(const std::string& data) {
    if (data.size() < 10) { // Minimum size: 2 (type) + 4 (name length) + 4 (payload length)
        throw std::runtime_error("Data too small to deserialize");
    }

    size_t offset = 0;

    // Deserialize MessageType (2 bytes)
    uint16_t type = (static_cast<uint8_t>(data[offset]) << 8) | static_cast<uint8_t>(data[offset + 1]);
    msgType = static_cast<MessageType>(type);
    offset += 2;

    // Deserialize name length (4 bytes)
    uint32_t nameLength = (static_cast<uint8_t>(data[offset]) << 24) |
                          (static_cast<uint8_t>(data[offset + 1]) << 16) |
                          (static_cast<uint8_t>(data[offset + 2]) << 8) |
                          static_cast<uint8_t>(data[offset + 3]);
    offset += 4;

    if (offset + nameLength > data.size()) {
        throw std::runtime_error("Invalid name length");
    }

    // Deserialize the name
    name = data.substr(offset, nameLength);
    offset += nameLength;

    // Deserialize payload length (4 bytes)
    uint32_t payloadLength = (static_cast<uint8_t>(data[offset]) << 24) |
                             (static_cast<uint8_t>(data[offset + 1]) << 16) |
                             (static_cast<uint8_t>(data[offset + 2]) << 8) |
                             static_cast<uint8_t>(data[offset + 3]);
    offset += 4;

    if (offset + payloadLength > data.size()) {
        throw std::runtime_error("Invalid payload length");
    }

    // Deserialize the payload
    payload = data.substr(offset, payloadLength);
}
