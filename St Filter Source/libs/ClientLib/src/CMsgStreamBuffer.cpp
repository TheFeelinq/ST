#include "CMsgStreamBuffer.h"

MsgStreamBuffer::MsgStreamBuffer(unsigned short opcode)
{
    reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, unsigned short)>(0x0053CEA0)(this, opcode);
}

MsgStreamBuffer::~MsgStreamBuffer(void)
{
}

void MsgStreamBuffer::Open(void)
{
    if (!IsOpen)
    {
        IsOpen = true;
        unk_0014 = unk_0010;
        TotalBytes = 0;
    }
}

void MsgStreamBuffer::Close(void)
{
    if (IsOpen)
    {
        IsOpen = false;
        unk_0014 = unk_0010;
        TotalReadBytes = 0;
    }
}

std::string MsgStreamBuffer::ReadStringA(void)
{
    unsigned short len = Read<unsigned short>();
    std::string str(len, 0);
    if (len)
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, char*, int)>(0x004F7220)(this, &str[0], len);
    return str;
}

std::wstring MsgStreamBuffer::ReadStringW(void)
{
    unsigned short len = Read<unsigned short>();
    std::string str(len, 0);
    if (len)
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, char*, int)>(0x004F7220)(this, &str[0], len);
    return std::wstring(str.begin(), str.end());
}

void MsgStreamBuffer::WriteStringA(const char* str)
{
    reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, const char*)>(0x0053D880)(this, str);
}

void MsgStreamBuffer::ReadBytes(char* ptr, std::size_t size)
{
    reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, char*, int)>(0x004F7220)(this, ptr, size);
}

void SendMsg1(MsgStreamBuffer* buffer)
{
    reinterpret_cast<void(__cdecl*)(MsgStreamBuffer*)>(0x008418D0)(buffer);
}

bool IsValidMsg(unsigned short opcode, int a2)
{
    return reinterpret_cast<bool(__cdecl*)(unsigned short, int)>(0x00841780)(opcode, a2);
}


