#include "qc_protocol.h"

bool QCProtocol::edl_mode_active = false;

bool QCProtocol::EnterEDLMode() {
    return USBConnection::SendSpecialCommand("edl");
}

bool QCProtocol::LoadFirehose(const std::string& firehose_path) {
    return USBConnection::SendFile(firehose_path);
}

bool QCProtocol::FlashPartition(const std::string& part_name, const std::vector<uint8_t>& data) {
    return USBConnection::SendCommand("flash:" + part_name, data);
}
