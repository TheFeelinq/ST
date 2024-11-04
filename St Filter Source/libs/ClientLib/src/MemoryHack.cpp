#include "MemoryHack.h"


void* MemoryHack::AddPtr(void* ptr, intptr_t offset)
{
    return static_cast<char*>(ptr)+offset;
}

const void* MemoryHack::AddPtr(const void* ptr, intptr_t offset)
{
    return static_cast<const char*>(ptr)+offset;
}


bool MemoryHack::CopyBytes(uintptr_t dst, const void* src, size_t size)
{
    return CopyBytes(reinterpret_cast<void*>(dst), src, size);
}

bool MemoryHack::CopyBytes(void* dst, const void* src, size_t size)
{
    DWORD oldProtect;
    if (VirtualProtect(dst, size, PAGE_READWRITE, &oldProtect) == FALSE)
        return false;
    memcpy(dst, src, size);
    if (VirtualProtect(dst, size, oldProtect, &oldProtect) == FALSE)
        return false;
    return true;
}

