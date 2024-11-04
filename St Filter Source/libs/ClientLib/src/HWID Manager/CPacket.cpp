#include "CPacket.h"

CPacket::CPacket(WORD wOpcode)
{
    this->m_bpBuffer = new BYTE[4096];
    this->m_bufferPos = 0;

    /*
        2b size
        2b opcode
        2b sec shit
    */
    WriteWORD(0x0000);
    WriteWORD(wOpcode);
    WriteWORD(0x0000);
}

CPacket::~CPacket()
{
    delete[] this->m_bpBuffer;
}

//+1
void CPacket::WriteByte(BYTE value)
{
    this->m_bpBuffer[this->m_bufferPos] = value;
    this->m_bufferPos++; //1
}

//+n
void CPacket::WriteBytes(BYTE * bpSrc, size_t len)
{
    memcpy(this->m_bpBuffer + this->m_bufferPos, bpSrc, len);
    this->m_bufferPos += len;
}

//+2
void CPacket::WriteWORD(WORD wValue)
{
    memcpy(this->m_bpBuffer + this->m_bufferPos, &wValue, sizeof(WORD));
    this->m_bufferPos += sizeof(WORD);
}

//+4
void CPacket::WriteDWORD(DWORD dwValue)
{
    memcpy(this->m_bpBuffer + this->m_bufferPos, &dwValue, sizeof(DWORD));
    this->m_bufferPos += sizeof(DWORD);
}

//len (2 bytes) + ascii len (NO ZERO TERMINATOR)
void CPacket::WriteASCII(const char * szStr)
{
    size_t len = strlen(szStr);
    this->WriteWORD(len);
    this->WriteBytes((BYTE*) szStr, len);
}

int CPacket::RawSize()
{
    return this->m_bufferPos;
}


BYTE * CPacket::RawBytes()
{
    //Calculate packet DATA block size
    *(WORD*)(this->m_bpBuffer) = this->m_bufferPos - 6;
    return this->m_bpBuffer;
    //return nullptr;
}
