#include "memhelp.h"


//TODO: Add support for short/relative jumps
bool memhelp::RenderDetour(UINT8 instruction, void* source, void* dest)
{
    DWORD oldProtect;
    UINT8 buffer[5];

    if(!VirtualProtect(source, sizeof(buffer), PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;


    buffer[0] = instruction; //ASM_JMP or ASM_CALL only for now
    *(DWORD*)(buffer + 1) = ((DWORD)dest  - ((DWORD)source + 5));

    memcpy(source, buffer, sizeof(buffer));


    VirtualProtect(source, sizeof(buffer), oldProtect, &oldProtect);

    return true;
}



bool memhelp::RenderNop(void* addr, UINT32 count)
{
    DWORD oldProtect;
    if(!VirtualProtect(addr, count, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    memset(addr, ASM_NOP, count);

    VirtualProtect(addr, count, oldProtect, &oldProtect);

    return true;

}




bool memhelp::WriteMem(void* addr, void* data, UINT32 count)
{
    DWORD oldProtect;
    if(!VirtualProtect(addr, count, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    memcpy(addr, data, count);

    VirtualProtect(addr, count, oldProtect, &oldProtect);
    return true;
}

UINT8* memhelp::ReadMem(void* addr, UINT32 count)
{
    UINT8* buffer = new UINT8[count];

    DWORD oldProtect;
    if(!VirtualProtect(addr, count, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    memcpy(buffer, addr, count);

    VirtualProtect(addr, count, oldProtect, &oldProtect);

    return buffer;
}