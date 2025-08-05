#pragma once
#include <vector>
#include <cstdint>
#include <string>

class QCProtocol {
public:
    static bool EnterEDLMode();
    static bool LoadFirehose(const std::string& firehose_path);
    static bool FlashPartition(const std::string& part_name, const std::vector<uint8_t>& data);
    static std::vector<uint8_t> ReadPartition(const std::string& part_name);
    static bool UnlockBootloader();
    static bool RemoveFRP();
    static bool AuthWithMiKey(const std::string& key);
    
    static bool edl_mode_active;
};
