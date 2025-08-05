#pragma once
#include <map>
#include <string>

class KeyManager {
public:
    bool LoadKeys(const std::string& xml_data);
    std::string GetKey(const std::string& key_name) const;
    const std::map<std::string, std::string>& GetAllKeys() const;

private:
    std::map<std::string, std::string> keys_;
};
