#include "keys.h"
#include <regex>
#include <sstream>

bool KeyManager::LoadKeys(const std::string& xml_data) {
    std::regex key_regex("<key name=\"([^\"]+)\">([^<]+)</key>");
    auto words_begin = std::sregex_iterator(xml_data.begin(), xml_data.end(), key_regex);
    
    for (auto it = words_begin; it != std::sregex_iterator(); ++it) {
        std::smatch match = *it;
        keys_[match[1].str()] = match[2].str();
    }
    return !keys_.empty();
}

std::string KeyManager::GetKey(const std::string& key_name) const {
    auto it = keys_.find(key_name);
    return (it != keys_.end()) ? it->second : "";
}

const std::map<std::string, std::string>& KeyManager::GetAllKeys() const {
    return keys_;
}
