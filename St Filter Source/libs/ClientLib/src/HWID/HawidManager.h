#pragma once
#include "BSLib/BSLib.h"
#include <Game.h>

class HawidManager
{
public:

    static const char* GetMac();
    static const char* GetHWID();
    static const char* cpuId(void);
    static std::string GetCPUID();
    static std::string getHWID();
    static const char* GetSerial();
    static const char *GetPcName();
    static unsigned short getCpuHash();
    static unsigned short getVolumeHash();
    static std::string GetRandomString(size_t length);
    static std::string Xor(std::string toEncrypt);
    static std::string GetDate();
    static std::string GetDate2();
};