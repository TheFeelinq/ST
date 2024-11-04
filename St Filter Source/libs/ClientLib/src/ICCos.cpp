//
// Created by Admin on 20/5/2021.
//

#include "ICCos.h"

void CICCos::OnRender()
{
    this->cosnameforegroundcolor = 0xFF4CFF00;
    reinterpret_cast<void(__thiscall*)(CICCos*)>(0x009C57D0)(this); //Render
    //printf("Rendering CICCos with UniqueID (0x%04X), Name (%s), Pointer (0x%08X).\n", this->UniqueID, std::string(this->cosname.begin(), this->cosname.end()).c_str(), this);
}
