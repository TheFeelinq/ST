#pragma once
#include "common.h"

enum E_DetourType
{
    Jmp,
    Call
};
class memmgr
{
public:
    static void Nop(DWORD dwAddr, size_t count);
    static void Detour(E_DetourType type, DWORD dwFrom, DWORD dwTo, size_t len);
    static void WriteBytes(DWORD dwDest, BYTE* bpData, size_t len);
    static BYTE* ReadBytes(DWORD dwFrom, size_t count);

};