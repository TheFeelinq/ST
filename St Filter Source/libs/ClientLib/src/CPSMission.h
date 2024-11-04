#include "IFDecoratedStatic.h"
#include "IFflorian0Guide.h"
#include "PSilkroad.h"

#define GET_OWN_GAME_ID() \
	MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0xF8, DWORD)
class CPSMission
{
public:
    int OnPacketRecv(class CMsgStreamBuffer* MsgBuffer);
    void SkillDamageParsing (class CMsgStreamBuffer* MsgBuffer);
    static bool char_is_ready;
    static BYTE CurHawn;
    static bool Gui_GrantName;
    static bool Gui_UniqueHistory;
    static bool Gui_CustomTitle;
    static bool Gui_SwitchTitle;
    static bool Gui_EventTimer;
    static bool Gui_CharacterLock;
    static bool Gui_CustomRank;
    static bool Gui_ColorsRender;
    static bool Gui_GlobalColors;
    static bool Gui_TotalPoint;
    static bool Gui_CustomNPC;
    static std::n_wstring CharNameSelected;
    static std::n_wstring CharNameRequest;
    static bool Npc_Is_Opening;
    static bool Icon_TaiXiu;
    static bool Icon_DailyLogin;
    static bool Icon_ExtralFeature;
    static bool Icon_ReBot;
    static bool Icon_Chest;
    static bool Icon_Event;
    static bool Icon_LiveStream;
    static bool Double_Click_ToLogin;
    static bool XSMB_ENABLE;
    static bool LOTO_ENABLE;
    static std::string DiscordUrl;
    static std::string FacebookUrl;
    static std::string WebsiteUrl;
    static bool m_IsRegionChange;
    static bool m_CharSelectOn;
    static int m_UserJID;
    static std::string m_szToken;
    wchar_t* Convert(std::n_string name);
};
