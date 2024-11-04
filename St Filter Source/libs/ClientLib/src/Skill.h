#pragma once
#include <BSLib/_internal/custom_stl.h>
struct Skill
{
    std::n_string SkillName;
    bool TargetRequired;
    bool TargetEtc_SelectDeadBody;
    int Param1;
    int Param8;
    int Param2;
    int Param3;
    int Param4;
    int Param5;
    std::list<std::wstring> m_CharNeedBuff;
};

struct BuffSkill
{
    std::wstring SkillNames;
    std::list<std::wstring> m_CharNeedBuff;
    std::list<short> m_SkillNeedBuff;
    std::map<short,std::wstring> m_SkillNeedBuffMap;
};