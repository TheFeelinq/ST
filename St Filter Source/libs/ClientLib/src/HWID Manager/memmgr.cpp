#include "memmgr.h"

void memmgr::Nop(DWORD dwAddr, size_t count)
{
    DWORD dwOldProtect = 0;

    VirtualProtect((LPVOID)dwAddr, count, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    memset((LPVOID)dwAddr, ASM_NOP, count);

    //Restore original memory protection
    VirtualProtect((LPVOID)dwAddr, count, dwOldProtect, &dwOldProtect);
}

void memmgr::Detour(E_DetourType type, DWORD dwFrom, DWORD dwTo, size_t len)
{
    //VP is also set from there, but who cares about optimization n stuff...
    //for now :D
    memmgr::Nop(dwFrom, len);

    DWORD dwOldProtect = 0;
    VirtualProtect((LPVOID)dwFrom, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    BYTE instr[5];

    if (type == E_DetourType::Jmp)
        instr[0] = ASM_JMP;
    if (type == E_DetourType::Call)
        instr[0] = ASM_CALL;
    *(DWORD*)(instr + 1) = (dwTo - (dwFrom + 5));


    memcpy((LPVOID)dwFrom, instr, 5);

    //Restore original memory protection
    VirtualProtect((LPVOID)dwFrom, len, dwOldProtect, &dwOldProtect);
}

void memmgr::WriteBytes(DWORD dwDest, BYTE * bpData, size_t len)
{
    DWORD dwOldProtect = 0;
    VirtualProtect((LPVOID)dwDest, len, PAGE_EXECUTE_READWRITE, &dwOldProtect);

    memcpy((LPVOID)dwDest, bpData, len);

    //Restore original memory protection
    VirtualProtect((LPVOID)dwDest, len, dwOldProtect, &dwOldProtect);
}


BYTE* memmgr::ReadBytes(DWORD dwFrom, size_t count)
{
    BYTE* buffer = new BYTE[count];

    DWORD dwOldProtect = 0;
    VirtualProtect((LPVOID)dwFrom, count, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    memcpy(buffer, (LPVOID)dwFrom, count);
    VirtualProtect((LPVOID)dwFrom, count, dwOldProtect, &dwOldProtect);

    return buffer;
}

