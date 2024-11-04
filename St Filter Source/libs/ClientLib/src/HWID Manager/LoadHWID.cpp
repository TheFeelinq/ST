#include <HWID/HawidManager.h>
#include <HWID/base64.h>
#include "common.h"
#include "hwidmgr.h"
#include "md5.h"
#include "LoadHWID.h"
#include "BSLib/multibyte.h"

void LoadHWID::HWIDLoad() {



    const char* hwid = HawidManager::GetHWID();
    std::string hwid_X = HawidManager::Xor(hwid);
    std::string hwid_1 = base64_encode(hwid_X);
    byte v211 = 122;
    byte v240 = 250;
    //std::string date = hwidmgr::GetDate2();
    //const char* date2 = date.c_str();
    const char* mac = HawidManager::GetMac();
    const char* serial = HawidManager::GetSerial();
    std::string date = HawidManager::GetDate2();
    const char* date2 = date.c_str();



    if (!hwid_1.empty()) {
        hwidmgr::Initialize();

        CPacket *packet = new CPacket(0xCAFE);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteByte(v211);
        packet->WriteASCII(hwid_1.c_str());
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        packet->WriteByte(v240);
        hwidmgr::Setup(packet, 2000);
    }
}
