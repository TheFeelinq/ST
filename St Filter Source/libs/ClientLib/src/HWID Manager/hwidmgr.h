#pragma once
#include "common.h"


class hwidmgr
{
public:
    static void Initialize();

    //interval in milliseconds
    static void Setup(CPacket* hwidPacket, int interval);

    static void web();

    static char* Encryption();

    static char * HhhHHh();

    static char* GetMac();

    static char* GetHWID();
    static char* GetSerial();
    static std::string GetRandomString(size_t length);
    static std::string GetDate();
    static std::string GetDate2();
};