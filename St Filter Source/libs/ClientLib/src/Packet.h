#pragma once
#include "xlib.h"

class Packet
{
public:
    Packet(WORD wOpcode);
    ~Packet();

    void WriteByte(BYTE value);
    void WriteBytes(BYTE* bpSrc, size_t len);
    void WriteWORD(WORD wValue);
    void WriteDWORD(DWORD dwValue);

    void WriteASCII(const char* szStr, size_t len);
    int RawSize();
    BYTE* RawBytes();
private:
    BYTE* m_bpBuffer;
    int m_bufferPos;
};