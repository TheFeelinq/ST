//
// Created by Admin on 22/3/2022.
//

#include "NIFTextBoard.h"
void CNIFTextBoard::TB_Func_3()
{
    return; // empty
}
void CNIFTextBoard::TB_Func_4()
{
    return; // empty
}

void CNIFTextBoard::TB_Func_5(int a2)
{
    this->N000096C1 = a2;
    TB_Func_3();
}

void CNIFTextBoard::TB_Func_6(int a2)
{
    this->N000096C2 = a2;
    TB_Func_3();
}

void CNIFTextBoard::TB_Func_7()
{
    return; // emtpy
}
char CNIFTextBoard::TB_Func_8()
{
    return N00009BB9;
}
void CNIFTextBoard::TB_Func_9(char a2)
{
    N00009BB9 = a2;
}
void CNIFTextBoard::TB_Func_10()
{
    return; // empty
}
void CNIFTextBoard::TB_Func_11()
{
    return; // empty
}
void CNIFTextBoard::TB_Func_12(const char* str, int a3, int a4)
{
    TB_Func_13(str, a3, a4);
}
void CNIFTextBoard::TB_Func_13(const std::n_string str, int a3, int a4)
{
    reinterpret_cast<void(__thiscall*)(CNIFTextBoard*, const std::n_string, int, int)>(0x00470ce0)(this, str, a3, a4);
}
void CNIFTextBoard::TB_Func_14(const std::string str, int a3, int a4)
{
    reinterpret_cast<void(__thiscall*)(CNIFTextBoard*, const std::string, int, int)>(0x00470ea0)(this, str, a3, a4);
}