#pragma once
#include <string>
#include <map>
#include <BSLib/_internal/custom_stl.h>
#include <SOItem.h>
#include "ChatItemLink.h"
#include "IFSlotWithHelp.h"
#include "IFSTCustomRankSlot.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"

using namespace std;
struct ItemMallData
{
    n_wstring ItemName;
    n_wstring Src;
    int Num;
    int OptLevel;
    int ID;
};
extern std::map<int, ItemMallData*> ItemMallDataList;
extern int ItemMallDataTotalCount;

struct LevelRankData
{
    n_wstring Name;
    int Level;
    int Rank;
};
extern std::map<int, LevelRankData*> LevelRankDataList;
extern int LevelRankDataTotalCount;

struct GoldRankData
{
    n_wstring Name;
    unsigned long long Gold;
    int Rank;
};
struct GlobalChat
{
    int index;
    std::wstring msg;
    bool completed;
    CMsgStreamBuffer* buffer;
};
struct SRPartyMatch
{
    int Number;
    int MasterJoinID;
    std::n_string MasterName;
    std::n_string Title;
    byte Racetype;
    byte LevelMin;
    byte LevelMax;
    byte setup;
    byte Purpose;
    byte MemberCount;
};
extern std::map<int, GoldRankData*> GoldRankDataList;
extern int GoldRankDataTotalCount;
extern D3DVECTOR CenterLocations;
extern uregion PatrolRegions;
extern std::map<string, ChatItemLink> ChatItemInfoList;
extern std::map<string, ItemLinking> ItemLinkInfoList;
extern std::map<string, ItemLinking> SCharItemInfoList;
extern std::map<string, CSOItem> CharInfoList1;
extern std::map<n_string, CSOItem> CharInfoList2;
extern std::map<n_string, CSOItem> CharInfoList3;
extern std::map<n_string, CSOItem> CharInfoList4;
extern std::map<n_string, CSOItem> CharInfoList5;
extern CIFSlotWithHelp* lastFoundEmptySlot;
extern byte LastEmptySlot;
extern bool isLoginScreen;
extern std::map<int,CIFCustomRankSlot*> chatSlots;
extern int firstAppearIndex;
extern int renderReference;
extern  std::map<string, string> emojiList;
extern CIFSlotWithHelp* Slotter;
extern std::map<int, void*> m_IconsData;
extern std::map<int, const IDirect3DBaseTexture9*> m_IconsDataStore;
extern std::map<int, const IDirect3DBaseTexture9*> m_IconsDataVipStore;
extern std::map<std::wstring, UINT32> m_CharacterIcons;
extern std::map<std::wstring, UINT32> m_CharacterVipIcons;
extern std::set<UINT16> m_PartyDisabledRegions;
extern std::list<__int16> s_lstHideClothesRegionIDs;
extern std::set<UINT16> TownRegion;
extern std::set<UINT16> RocRegion;
extern std::set<UINT16> DimenSionalRegion;
extern std::map<int, int> UniqueTargetHashmap;
extern std::map<int, int> UniqueTargetHashmapPlayer;
extern std::set<std::n_wstring> Blocked_Party_CharNameRequest;
extern std::list<GlobalChat> GlobalChatLog;
extern std::map<int, SRPartyMatch> PartyMatches;