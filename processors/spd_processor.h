#pragma once
#include "common.h"
#include "keys.h"
#include <string>
#include <vector>
#include <functional>

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
    
    void SetNandId(int id);
    void SetVerboseLevel(int level);
    void SetTimeout(int ms);
    void SetDefaultSavePath(const std::string& path);

private:
    KeyManager& key_manager_;
    spdio_t* io_ = nullptr;
    
    uint16_t block_size_ = 4096;
    bool fdl1_loaded_ = false;
    bool fdl2_executed_ = false;
    int selected_ab_ = -1;
    int nand_id_ = DEFAULT_NAND_ID;
    std::string save_path_ = ".";
    
    bool initialize_connection();
    bool send_and_receive(uint8_t cmd, const std::vector<uint8_t>& data, std::vector<uint8_t>& response);
    bool dump_partition(const std::string& part_name, uint32_t offset, uint32_t size, const std::string& output);
    bool load_partition(const std::string& part_name, const std::string& input);
    partition_t get_partition_info(const std::string& name);
    bool check_confirm(const std::string& action);
    bool select_active_slot();
};
