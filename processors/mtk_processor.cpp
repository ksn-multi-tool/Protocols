#include "mtk_processor.h"
#include <fstream>
#include <iostream>

MTKProcessor::MTKProcessor(KeyManager& key_manager) : key_manager_(key_manager) {}

bool MTKProcessor::Connect() {
    return MTKProtocol::Connect();
}

bool MTKProcessor::SendDA(const std::string& da_path) {
    std::ifstream file(da_path, std::ios::binary | std::ios::ate);
    if (!file) return false;
    
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> da_data(size);
    file.read(reinterpret_cast<char*>(da_data.data()), size);
    return MTKProtocol::SendDA(da_data);
}

bool MTKProcessor::ReadPartition(const std::string& part_name, const std::string& output) {
    if (partition_table_.find(part_name) == partition_table_.end()) return false;
    
    const PartitionInfo& part = partition_table_[part_name];
    auto data = MTKProtocol::ReadMem(part.start, part.size);
    
    std::ofstream out_file(output, std::ios::binary);
    out_file.write(reinterpret_cast<char*>(data.data()), data.size());
    return true;
}

bool MTKProcessor::WritePartition(const std::string& part_name, const std::string& input) {
    std::ifstream in_file(input, std::ios::binary | std::ios::ate);
    if (!in_file) return false;
    
    size_t size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    in_file.read(reinterpret_cast<char*>(data.data()), size);
    
    return MTKProtocol::WriteMem(partition_table_[part_name].start, data);
}

bool MTKProcessor::UnlockBootloader() {
    std::string key = key_manager_.GetKey("mtk_unlock_key");
    return MTKProtocol::BypassAuth(key) && MTKProtocol::UnlockBootloader();
}
