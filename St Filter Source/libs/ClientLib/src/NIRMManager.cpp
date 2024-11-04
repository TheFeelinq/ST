//
// Created by Admin on 25/3/2022.
//

#include "NIRMManager.h"
void CNIRMManager::LoadFromFile(const char *filename, CObj *base, int a3) {
    reinterpret_cast<void (__thiscall *)(CNIRMManager *, const char *,CObj * ,int)>(0x00469140)(this, filename,base,a3);
}
CNIFWnd *CNIRMManager::GetResObj(int id){
    return reinterpret_cast<CNIFWnd *(__thiscall *)(CNIRMManager *, int)>(0x0046e060)(this, id);
}
