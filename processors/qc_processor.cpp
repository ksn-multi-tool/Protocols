#include "qc_processor.h"

QCProcessor::QCProcessor(KeyManager& key_manager) : key_manager_(key_manager) {}

bool QCProcessor::EnterEDLMode() {
    return QCProtocol::EnterEDLMode();
}

bool QCProcessor::UnlockBootloader() {
    return QCProtocol::UnlockBootloader();
}

bool QCProcessor::AuthWithMiKey() {
    std::string key = key_manager_.GetKey("xiaomi_auth_key");
    return QCProtocol::AuthWithMiKey(key);
}

bool QCProcessor::FlashPartition(const std::string& part_name, const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file) return false;
    
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> data(size);
    file.read(reinterpret_cast<char*>(data.data()), size);
    
    return QCProtocol::FlashPartition(part_name, data);
}
