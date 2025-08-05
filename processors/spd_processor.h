#pragma once
#include "spd_protocol.h"
#include "keys.h"
#include <string>
#include <vector>
#include <map>
#include <functional>

struct SPD_PartitionInfo {
    std::string name;
    uint32_t size;
    uint32_t start;
    bool active;
};

class SPDProcessor {
public:
    SPDProcessor(KeyManager& key_manager);
    ~SPDProcessor();
    
    bool Connect(int wait_seconds = 30);
    bool Disconnect();
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
    bool UnlockBootloader();
    
    bool DumpFullBackup(bool lite);
    bool LoadFDL(const std::string& file, uint32_t addr);
    bool ExecuteFDL();
    bool SendCommand(uint8_t cmd, const std::vector<uint8_t>& data = {});
    bool ReadChipUID();

private:
    KeyManager& key_manager_;
    std::map<std::string, SPD_PartitionInfo> partition_table_;
    spdio_t* io_ = nullptr;
    
    uint16_t block_size_ = 4096;
    bool fdl1_loaded_ = false;
    bool fdl2_executed_ = false;
    int selected_ab_ = -1;
    int nand_id_ = DEFAULT_NAND_ID;
    
    bool initialize_connection();
    bool send_and_receive(uint8_t cmd, const std::vector<uint8_t>& data, std::vector<uint8_t>& response);
    bool dump_partition(const std::string& part_name, uint32_t offset, uint32_t size, const std::string& output);
    bool load_partition(const std::string& part_name, const std::string& input);
    SPD_PartitionInfo get_partition_info(const std::string& name);
    bool check_confirm(const std::string& action);
};
