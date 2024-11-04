//
// Created by Admin on 19/9/2021.
//

#include "MemoryHelper.h"

void* MemoryHelper::m_tmpProtectAddr;
DWORD MemoryHelper::m_tmpProtect;
size_t MemoryHelper::m_tmpProtectSize;
bool MemoryHelper::UnProtect(void* addr, size_t count)
{
    if (VirtualProtect(addr, count, PAGE_READWRITE, &m_tmpProtect) == FALSE)
        return false;

    m_tmpProtectAddr = addr;
    m_tmpProtectSize = count;

    return true;
}
bool MemoryHelper::Detour(bool jmpOrCall, void* source, void* dest)
{
    if (!UnProtect(source, 5))
        return false;

    char instruction[5];
    instruction[0] = (jmpOrCall == false) ? 0xE9 : 0xE8;
    *(DWORD*)(instruction + 1) = reinterpret_cast<uintptr_t>(dest) - (reinterpret_cast<uintptr_t>(source) + 5);
    memcpy(source, instruction, 5);
    //restore original memory protection mode
    return ReProtect();
}

bool MemoryHelper::ReProtect()
{
    //restore original protection mode
    return VirtualProtect(m_tmpProtectAddr, m_tmpProtectSize, m_tmpProtect, &m_tmpProtect) != FALSE;
}

BOOL MemoryHelper::SetTrampoline(bool isLongJmp, void* src, void* dest, UINT32 nopSize)
{
    DWORD dwOldProtect = 0;
    VirtualProtect(src, nopSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);
    char instruction[5];
    instruction[0] = (isLongJmp) ? 0xE9 : 0xE8;
    *(DWORD*)(instruction + 1) = (reinterpret_cast<uintptr_t>(dest) - (reinterpret_cast<uintptr_t>(src) + 5));
    memset(src, 0x90, nopSize);
    memcpy(src, &instruction, 5);
    VirtualProtect(src, nopSize, dwOldProtect, &dwOldProtect);
    return TRUE;
}
void MemoryHelper::replaceOffset(int trampoline_location, int target_location)
{

    char inst_offset[] = { 0x00, 0x00, 0x00, 0x00 };
    int distance;
    DWORD dwProtect = 0;

    int offset_location = trampoline_location + 1;

    distance = target_location - trampoline_location - 5;

    // Write jump-distance to instruction
    memcpy(inst_offset, &distance, 4);

    if (!VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    memcpy((LPVOID)offset_location, inst_offset, sizeof(inst_offset));

    VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), dwProtect, NULL);

}

void MemoryHelper::replaceAddr(int addr, int value) {
    DWORD dwProtect;

    if (!VirtualProtect((LPVOID)addr, sizeof(int), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    *((int*)addr) = value;

    VirtualProtect((LPVOID)addr, sizeof(int), dwProtect, NULL);
}

void MemoryHelper::SetNop(DWORD addr, size_t Length)
{
    UnProtect(reinterpret_cast<void*>(addr), Length);
    for (size_t i = 0; i < Length; i++)
    {
        *(BYTE*)(addr + i) = 0x90;
    }
    ReProtect();
}

