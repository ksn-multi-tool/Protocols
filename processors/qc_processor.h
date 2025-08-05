#pragma once
#include "../protocols/qc_protocol.h"
#include "../keys.h"
#include <string>
#include <vector>
#include <map>

class QCProcessor {
public:
    QCProcessor(KeyManager& key_manager);
    
    bool EnterEDLMode();
    bool LoadFirehose(const std::string& firehose_path);
    
    bool FlashPartition(const std::string& part_name, const std::string& file_path);
    bool FlashRawSparse(const std::string& file_path);
    
    bool BackupPartition(const std::string& part_name, const std::string& output);
    bool ErasePartition(const std::string& part_name);
    
    bool ReadPartitions(const std::string& list_file, const std::string& output_dir);
    
    bool SetActiveSlot(char slot);
    bool RebootTo(DeviceMode mode);
    
    bool UnlockBootloader();
    bool RemoveFRP();
    bool AuthWithMiKey();
    bool RemoveMiAccount();
    bool FixAntiRollback();

private:
    KeyManager& key_manager_;
};
