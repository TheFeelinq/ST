#pragma once
#include "xlib.h"

class MsgStreamBuffer
{
private:
    int unk_0000; //0x0000

public:
    std::size_t TotalReadBytes; //0x0004
    std::size_t TotalBytes; //0x0008
private:
    bool IsOpen; //0x000C
    unsigned char unk_000D; //0x000D
    unsigned char unk_000E; //0x000E
    unsigned char unk_000F; //0x000F
    int unk_0010; //0x0010
    int unk_0014; //0x0014
public:
    unsigned short Opcode; //0x0018
    bool Sent; //0x001A
private:
    char pad_001B; //0x001B
    int pad_001C; //0x001C

public:
    MsgStreamBuffer(unsigned short opcode);
    ~MsgStreamBuffer(void);
    void Open();
    void Close();

    template<typename T>
    T Read(void)
    {
        T Data;
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, T*, int)>(0x004F7220)(this, &Data, sizeof(T));
        return Data;
    }

    template<typename T>
    T Read(std::size_t size)
    {
        T Data;
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, T*, int)>(0x004F7220)(this, &Data, size);
        return Data;
    }

    template <typename T>
    void Read(T& buffer, std::size_t size)
    {
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, T*, int)>(0x004F7220)(this, &buffer, size);
    }

    void ReadBytes(char* ptr, std::size_t size);

    template<typename T>
    void Write(T Data)
    {
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, T*, int)>(0x00508FE0)(this, &Data, sizeof(Data));
    }

    template<typename T>
    void Write(T* DataPtr, std::size_t size)
    {
        reinterpret_cast<void(__thiscall*)(MsgStreamBuffer*, T*, int)>(0x00508FE0)(this, DataPtr, size);
    }

    std::string ReadStringA();
    std::wstring ReadStringW();
    void WriteStringA(const char* str);
    void WriteStringW(const wchar_t* wcs);

};

void SendMsg1(MsgStreamBuffer* buffer);
bool IsValidMsg(unsigned short opcode, int a2);