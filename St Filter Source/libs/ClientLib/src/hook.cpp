#include "hook.h"
#include <Windows.h>
#include <stdio.h>

void placeHook(int trampoline_location, int target_location)
{

    char jmp_inst[] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
    int distance;
    DWORD dwProtect = 0;

    distance = target_location - trampoline_location - 5;

    // Write jump-distance to instruction
    memcpy((jmp_inst + 1), &distance, 4);

    if (!VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    memcpy((LPVOID)trampoline_location, jmp_inst, sizeof(jmp_inst));

    VirtualProtect((LPVOID)trampoline_location, sizeof(jmp_inst), dwProtect, NULL);

}
bool RenderNop(void* addr, int count)
{
    DWORD oldProtect;
    if (!VirtualProtect(addr, count, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    memset(addr, 0x90, count);

    VirtualProtect(addr, count, oldProtect, &oldProtect);

    return true;
}

void replaceOffset(int trampoline_location, int target_location)
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

void replaceAddr(int addr, int value)
{
    DWORD dwProtect;

    if (!VirtualProtect((LPVOID)addr, sizeof(int), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    *((int*)addr) = value;

    VirtualProtect((LPVOID)addr, sizeof(int), dwProtect, NULL);
}

void vftableHook(unsigned int vftable_addr, int offset, int target_func)
{
    replaceAddr(vftable_addr + offset*sizeof(void*), target_func);
}
void replaceOffsetEdit(int trampoline_location, int target_location)
{

    char inst_offset[] = { 0x00, 0x00, 0x00, 0x00 };
    int distance;
    DWORD dwProtect = 0;

    int offset_location = trampoline_location + 1;

    distance = target_location;

    // Write jump-distance to instruction
    memcpy(inst_offset, &distance, 4);

    if (!VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), PAGE_EXECUTE_READWRITE, &dwProtect)) {
        perror("Failed to unprotect memory\n");
        return;
    }

    memcpy((LPVOID)offset_location, inst_offset, sizeof(inst_offset));

    VirtualProtect((LPVOID)offset_location, sizeof(inst_offset), dwProtect, NULL);

}
bool CopyBytes(uintptr_t dst, const void* src, size_t size)
{
    return CopyBytes(reinterpret_cast<void*>(dst), src, size);
}

bool CopyBytes(void* dst, const void* src, size_t size)
{
    DWORD oldProtect;
    if (VirtualProtect(dst, size, PAGE_READWRITE, &oldProtect) == FALSE)
        return false;
    memcpy(dst, src, size);
    if (VirtualProtect(dst, size, oldProtect, &oldProtect) == FALSE)
        return false;
    return true;
}
