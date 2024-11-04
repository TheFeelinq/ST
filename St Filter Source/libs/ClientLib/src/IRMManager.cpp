#include "StdAfx.h"
#include "IRMManager.h"

CIRMManager::CIRMManager() {
    N00009CBC = 0;
}

void CIRMManager::LoadFromFile(const char *filename) {
    reinterpret_cast<void (__thiscall *)(CIRMManager *, const char *)>(0x008B50A0)(this, filename);
}

void CIRMManager::CreateInterfaceSection(std::string section, CObj *base) {
    reinterpret_cast<void (__thiscall *)(CIRMManager *, std::string, CObj *)>(0x008B5580)(this, section, base);
}

CIFWnd *CIRMManager::GetResObj(int id, int a2) {
    return reinterpret_cast<CIFWnd *(__thiscall *)(CIRMManager *, int, int)>(0x008B51F0)(this, id, a2);
}
void* CIRMManager::GetWindowActive(DWORD WindowID)
{
    return reinterpret_cast<void*(__thiscall*)(CIRMManager*, DWORD)>(0x00798c50)(this, WindowID);
}

void CIRMManager::DeleteCreatedSection(std::string section) {
    reinterpret_cast<void (__thiscall *)(CIRMManager *, std::string)>(0x008b59f0)(this, section);
}
