#pragma once
#include "../protocols/mtk_protocol.h"
#include "../keys.h"
#include <string>
#include <vector>
#include <map>

struct PartitionInfo {
    std::string name;
    uint32_t start;
    uint32_t size;
    bool active;
};

class MTKProcessor {
public:
    MTKProcessor(KeyManager& key_manager);
    
    bool Connect();
    bool Disconnect();
    bool SendDA(const std::string& da_path);
    bool SetBaudrate(int baud);
    
    std::vector<uint8_t> ReadMemory(uint32_t address, size_t size);
    bool WriteMemory(uint32_t address, const std::vector<uint8_t>& data);
    
    bool ReadPartition(const std::string& part_name, const std::string& output);
    bool WritePartition(const std::string& part_name, const std::string& input);
    bool ErasePartition(const std::string& part_name);
    bool ReadPartitionExact(const std::string& part_name, uint32_t offset, uint32_t size, const std::string& output);
    
    bool ReadPartitions(const std::string& list_file, const std::string& output_dir);
    bool WritePartitions(const std::string& input_dir, bool force_slot = false);
    
    bool WriteOffsetFile(const std::string& part_name, uint32_t offset, const std::string& file);
    bool WriteOffsetValue(const std::string& part_name, uint32_t offset, uint32_t value);
    
    bool EraseAll();
    bool ReadPartitionTable();
    bool Repartition(const std::string& xml_file);
    void PrintPartitionTable() const;
    uint32_t GetPartitionSize(const std::string& part_name) const;
    bool CheckPartitionExists(const std::string& part_name) const;
    
    bool SetVerityState(bool enabled);
    bool SetActiveSlot(char slot);
    bool SetBootMode(int mode_id);
    
    bool RebootToRecovery();
    bool RebootToFastboot();
    bool ResetDevice();
    bool PowerOff();
    
    bool UnlockBootloader();
    bool RemoveFRP();
    bool RemoveSecracy();
    bool RemoveDemoMode();

private:
    KeyManager& key_manager_;
    std::map<std::string, PartitionInfo> partition_table_;
};
