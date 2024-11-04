#pragma once

class CNPCPosData
{
public:
    struct SData {
        unsigned __int32 m_NpcID; // 0x0000
        char gap2[12];
        float m_PosX; // 0x0010
        float m_PosY; // 0x0014
        float m_PosZ; // 0x0018
    };
    char gap[4];

    SData data;
};