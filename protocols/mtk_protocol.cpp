#include "mtk_protocol.h"
#include "usb_connection.h" 

bool MTKProtocol::handshake_completed = false;
bool MTKProtocol::security_bypassed = false;

bool MTKProtocol::Connect() {
    USBConnection::Open(0x0E8D, 0x0003); 
    return USBConnection::IsConnected();
}

bool MTKProtocol::SendDA(const std::vector<uint8_t>& da) {
    return USBConnection::SendPacket(0xA0, da);
}

std::vector<uint8_t> MTKProtocol::ReadMem(uint32_t addr, uint32_t size) {
    std::vector<uint8_t> cmd = {
        static_cast<uint8_t>(addr >> 24),
        static_cast<uint8_t>(addr >> 16),
        static_cast<uint8_t>(addr >> 8),
        static_cast<uint8_t>(addr),
        static_cast<uint8_t>(size >> 24),
        static_cast<uint8_t>(size >> 16),
        static_cast<uint8_t>(size >> 8),
        static_cast<uint8_t>(size)
    };
    USBConnection::SendPacket(0xD1, cmd);
    return USBConnection::ReceiveData(size);
}

bool MTKProtocol::BypassAuth(const std::string& key) {
    std::vector<uint8_t> key_data(key.begin(), key.end());
    return USBConnection::SendPacket(0xB0, key_data);
}
