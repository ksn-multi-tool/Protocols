#include "spd_protocol.h"

uint16_t SPDProtocol::current_block_size = 4096;

bool SPDProtocol::SetBlockSize(uint16_t size) {
    if (size > 65535) return false;
    current_block_size = size;
    return USBConnection::SendCommand("block_size", {static_cast<uint8_t>(size >> 8), static_cast<uint8_t>(size)});
}

std::vector<uint8_t> SPDProtocol::ReadPartition(const std::string& part_name, uint32_t offset, uint32_t size) {
    std::vector<uint8_t> cmd;
    cmd.insert(cmd.end(), part_name.begin(), part_name.end());
    cmd.push_back(0);
    cmd.push_back(static_cast<uint8_t>(offset >> 24));
    cmd.push_back(static_cast<uint8_t>(offset >> 16));
    cmd.push_back(static_cast<uint8_t>(offset >> 8));
    cmd.push_back(static_cast<uint8_t>(offset));
    cmd.push_back(static_cast<uint8_t>(size >> 24));
    cmd.push_back(static_cast<uint8_t>(size >> 16));
    cmd.push_back(static_cast<uint8_t>(size >> 8));
    cmd.push_back(static_cast<uint8_t>(size));
    
    USBConnection::SendCommand("read_part", cmd);
    return USBConnection::ReceiveData(size);
}
