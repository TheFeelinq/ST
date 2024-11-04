#include "GameDataExt.h"


std::map<int, ItemMallData*> ItemMallDataList;
int ItemMallDataTotalCount;
D3DVECTOR CenterLocations;
uregion PatrolRegions;
std::map<int, LevelRankData*> LevelRankDataList;
int LevelRankDataTotalCount;

std::map<int, GoldRankData*> GoldRankDataList;
int GoldRankDataTotalCount;
std::map<int,CIFCustomRankSlot*> chatSlots;
int firstAppearIndex = 50;
int renderReference = 50;
std::map<string, ChatItemLink> ChatItemInfoList;
std::map<string, ItemLinking> ItemLinkInfoList;
std::map<string, ItemLinking> SCharItemInfoList;
std::map<string, CSOItem> CharInfoList1;
std::map<n_string, CSOItem> CharInfoList2;
std::map<n_string, CSOItem> CharInfoList3;
std::map<n_string, CSOItem> CharInfoList4;
std::map<n_string, CSOItem> CharInfoList5;
CIFSlotWithHelp* lastFoundEmptySlot;
CIFSlotWithHelp* Slotter;
std::map<string, string> emojiList;
byte LastEmptySlot;
std::map<int, void*> m_IconsData;
std::map<int, const IDirect3DBaseTexture9*> m_IconsDataStore;
std::map<int, const IDirect3DBaseTexture9*> m_IconsDataVipStore;
std::map<std::wstring, UINT32> m_CharacterIcons;
std::map<std::wstring, UINT32> m_CharacterVipIcons;
std::set<UINT16> m_PartyDisabledRegions;
std::list<__int16> s_lstHideClothesRegionIDs;
std::set<UINT16> TownRegion;
std::set<UINT16> RocRegion;
std::set<UINT16> DimenSionalRegion;
std::map<int, int> UniqueTargetHashmap;
std::map<int, int> UniqueTargetHashmapPlayer;
std::set<std::n_wstring> Blocked_Party_CharNameRequest;
std::list<GlobalChat> GlobalChatLog;
std::map<int, SRPartyMatch> PartyMatches;