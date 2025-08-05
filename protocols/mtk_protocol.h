#pragma once
#include <vector>
#include <cstdint>
#include <string>

class MTKProtocol {
public:
    static bool Connect();
    static bool Disconnect();
    static bool SendDA(const std::vector<uint8_t>& da);
    static std::vector<uint8_t> ReadMem(uint32_t addr, uint32_t size);
    static bool WriteMem(uint32_t addr, const std::vector<uint8_t>& data);
    static bool SendCmd(uint8_t cmd, const std::vector<uint8_t>& data = {});
    static bool SetBaudrate(int baud);
    static bool BypassAuth(const std::string& key);
    static bool UnlockBootloader();
    static bool RemoveFRP();
    
    static bool handshake_completed;
    static bool security_bypassed;
};
