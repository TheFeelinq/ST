
#include "CInterfaceNetSender.h"
#include "GInterface.h"
#define GP_LIMIT 0x00989680


void CInterfaceNetSender::DonateGuildPoints(unsigned int GP)
{
    if (GuildSkillPoints == GP_LIMIT)
    {
       // CGInterface* g_interface = CGInterface::GetInterface();
        if (g_pCGInterface)
        {
            g_pCGInterface->HandleSystemMessages(1, L"You have reached maximum limit of guild skills points.");
            g_pCGInterface->ShowBlueNotify(L"You have reached maximum limit of guild skills points.");
        }
    }
    else
    {
        unsigned int TotalGP = GuildSkillPoints + GP;
        if (TotalGP > GP_LIMIT && GuildSkillPoints < GP_LIMIT)
            GP = GP_LIMIT - GuildSkillPoints;
        reinterpret_cast<void(__thiscall*)(CInterfaceNetSender*, unsigned int)>(0x0081FAB0)(this, GP);
    }
}