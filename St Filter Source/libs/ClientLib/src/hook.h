#pragma once

#include <stdarg.h>
#include <Windows.h>

template<typename T>
int addr_from_this(T funptr) {
    union  {
        int addr;
        T ptr;
    } myu;

    myu.ptr = funptr;
    return myu.addr;
}


template<typename T>
void placeHook(int trampoline_location, T& target_location)
{
    placeHook(trampoline_location, reinterpret_cast<int>(&target_location));
}
bool RenderNop(void* addr, int count);
void placeHook(int trampoline_location, int target_location);

void replaceOffset(int trampoline_location, int target_location);

void replaceAddr(int addr, int value);

void vftableHook(unsigned int vftable_addr, int offset, int target_func);
void replaceOffsetEdit(int trampoline_location, int target_location);
static bool CopyBytes(uintptr_t dst, const void* src, size_t size);
static bool CopyBytes(void* dst, const void* src, size_t size);

