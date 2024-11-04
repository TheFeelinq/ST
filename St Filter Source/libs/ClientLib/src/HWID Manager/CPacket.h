#pragma once
#include "common.h"

class CPacket
{
public:
    CPacket(WORD wOpcode);
    ~CPacket();

    void WriteByte(BYTE value);
    void WriteBytes(BYTE* bpSrc, size_t len);
    void WriteWORD(WORD wValue);
    void WriteDWORD(DWORD dwValue);

    void WriteASCII(const char* szStr);
    int RawSize();
    BYTE* RawBytes();
private:
    BYTE* m_bpBuffer;
    int m_bufferPos;
};