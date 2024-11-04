#pragma once
#include "xlib.h"

class memhelp
{
public:

    //Templates
    template<typename T>
    inline static T & RefPtr(uintptr_t ptr)
    {
        return *reinterpret_cast<T*>(ptr);
    }


    //Bigger funcs go to cpp file
    static bool RenderDetour(UINT8 instruction, void* source, void* dest);
    static bool RenderNop(void* addr, UINT32 count);

    static bool WriteMem(void* addr, void* data, UINT32 count);
    static UINT8* ReadMem(void* addr, UINT32 count);
private:


};