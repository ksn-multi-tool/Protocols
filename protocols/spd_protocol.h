#pragma once
#include <vector>
#include <cstdint>
#include <string>

class SPDProtocol {
public:
    static bool Connect();
    static bool SetBlockSize(uint16_t size);
    static std::vector<uint8_t> ReadPartition(const std::string& part_name, uint32_t offset, uint32_t size);
    static bool WritePartition(const std::string& part_name, const std::vector<uint8_t>& data);
    static bool ErasePartition(const std::string& part_name);
    static bool Repartition(const std::string& xml_content);
    static bool SetBootMode(int mode_id);
    static bool RebootToRecovery();
    
    static uint16_t current_block_size;
};
