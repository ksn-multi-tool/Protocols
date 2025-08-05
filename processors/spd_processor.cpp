#include "spd_processor.h"

SPDProcessor::SPDProcessor(KeyManager& key_manager) : key_manager_(key_manager) {}

bool SPDProcessor::SetBlockSize(uint16_t size) {
    return SPDProtocol::SetBlockSize(size);
}

bool SPDProcessor::ReadPartition(const std::string& part_spec, const std::string& output) {
    if (part_spec == "all" || part_spec == "all_lite") {
        bool lite = (part_spec == "all_lite");
        for (const auto& [name, info] : partition_table_) {
            if (lite && (name == "blackbox" || name == "cache" || name == "userdata")) 
                continue;
            
            std::string out_file = output + "/" + name + ".bin";
            auto data = SPDProtocol::ReadPartition(name, 0, info.size);
            if (data.empty()) {
                LOG_ERROR("Failed to read partition: {}", name);
                continue;
            }
            
            std::ofstream file(out_file, std::ios::binary);
            if (!file) {
                LOG_ERROR("Cannot create file: {}", out_file);
                continue;
            }
            file.write(reinterpret_cast<char*>(data.data()), data.size());
        }
        return true;
    }
    
    auto it = partition_table_.find(part_spec);
    if (it == partition_table_.end()) {
        LOG_ERROR("Unknown partition: {}", part_spec);
        return false;
    }
    
    auto data = SPDProtocol::ReadPartition(part_spec, 0, it->second.size);
    if (data.empty()) {
        LOG_ERROR("Read failed for partition: {}", part_spec);
        return false;
    }
    
    std::ofstream file(output, std::ios::binary);
    if (!file) {
        LOG_ERROR("Cannot create file: {}", output);
        return false;
    }
    file.write(reinterpret_cast<char*>(data.data()), data.size());
    return true;
}

bool SPDProcessor::WritePartition(const std::string& part_spec, const std::string& input) {
    std::ifstream in_file(input, std::ios::binary | std::ios::ate);
    if (!in_file) return false;
    
    size_t size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    in_file.read(reinterpret_cast<char*>(data.data()), size);
    
    return SPDProtocol::WritePartition(part_spec, data);
}
