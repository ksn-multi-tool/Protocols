#pragma once
#include "../protocols/spd_protocol.h"
#include "../keys.h"
#include <string>
#include <vector>
#include <map>

struct SPD_PartitionInfo {
    std::string name;
    uint32_t size;
};

class SPDProcessor {
public:
    SPDProcessor(KeyManager& key_manager);
    
    bool Connect();
    bool SetBlockSize(uint16_t size);
    
    bool ReadPartition(const std::string& part_spec, const std::string& output);
    bool WritePartition(const std::string& part_spec, const std::string& input);
    bool ReadPartitionExact(const std::string& part_name, uint32_t offset, uint32_t size, const std::string& output);
    
    bool ReadPartitions(const std::string& list_file, const std::string& output_dir);
    bool WritePartitions(const std::string& save_location, bool force_slot = false);
    
    bool WriteOffsetFile(const std::string& part_name, uint32_t offset, const std::string& file);
    bool WriteOffsetValue(const std::string& part_name, uint32_t offset, uint32_t value);
    
    bool ErasePartition(const std::string& part_name);
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

private:
    KeyManager& key_manager_;
    std::map<std::string, SPD_PartitionInfo> partition_table_;
};
