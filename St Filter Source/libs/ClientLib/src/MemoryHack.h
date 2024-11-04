#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <intrin.h>
#include <cstring>


class MemoryHack
{
public:
    static void* AddPtr(void* ptr, intptr_t offset);
    static const void* AddPtr(const void* ptr, intptr_t offset);
    template<typename T>
    inline static T& RefPtr(uintptr_t ptr)
    {
        return *reinterpret_cast<T*>(ptr);
    }
    template<typename T>
    inline static const T& RefPtr(const void* ptr, intptr_t offset)
    {
        return *static_cast<const T*>(AddPtr(ptr, offset));
    }
    template<typename T>
    inline static T& RefPtr(void* ptr, intptr_t offset)
    {
        return *static_cast<T*>(AddPtr(ptr, offset));
    }
    static __declspec(noinline) void AppMark(const char* ptr);
    static bool CopyBytes(uintptr_t dst, const void* src, size_t size);
    static bool CopyBytes(void* dst, const void* src, size_t size);


};

