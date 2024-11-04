#pragma once
#include <iostream>

class CInterfaceNetSender
{
private:
    char pad_0000[8504]; //0x0000
    unsigned int GuildSkillPoints; //0x2138
    char pad_2140[8]; //0x213C
    std::wstring GuildName; //0x2140
    std::wstring CharName; //0x2160

public:
    void DonateGuildPoints(unsigned int GP);
};