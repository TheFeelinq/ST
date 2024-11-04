#pragma once
#ifndef Q_MEMORY_HELPER_H
#define Q_MEMORY_HELPER_H
#include "stdafx.h"
#include "xlib.h"

class MemoryHelper
{
public:
    template<typename T>
    inline static T & RefPtr(uintptr_t ptr)
    {
        return *reinterpret_cast<T*>(ptr);
    }

    template<typename T>
    static int addr_from_this(T funptr) {
        union {
            int addr;
            T ptr;
        } myu;

        myu.ptr = funptr;
        return myu.addr;
    }

    static void SetNop(DWORD addr, size_t Length);
    BOOL SetTrampoline(bool isLongJmp, void* src, void* dest, UINT32 nopSize);

    static void replaceAddr(int addr, int value);
    static void replaceOffset(int trampoline_location, int target_location);
    static bool UnProtect(void* addr, size_t count);
    static bool ReProtect();
    static void ReplaceByte(void* addr, UINT8 value);
    /*JMP = FALSE CALL = TRUE*/
    static bool Detour(bool jmpOrCall, void* source, void* dest);
private:
    static void* m_tmpProtectAddr;
    static DWORD m_tmpProtect;
    static size_t m_tmpProtectSize;
};

#endif
inline void MemoryHelper::ReplaceByte(void* addr, UINT8 value)
{
    UnProtect(addr, sizeof(value));
    *(UINT8*)addr = value;
    ReProtect();
}
