#include "OptimizeCloth.h"
#include "GlobalDataManager.h"
#include "GameDataExt.h"
#include <algorithm>



#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
    (type)(((uintptr_t)ptr) + offset)


#define SETOPTIMIZECLOTH_FN_OFFSET					0x00A60F90
#define SETOPTIMIZECLOTH_APPLY_FN_OFFSET			0x00A61C60
#define GET_CICPLAYER_BY_GAME_ID_FN_OFFSET			0x009C3220
#define NET_PROCESS_ITEM_EQUIP_EFFECT_FN_OFFSET		0x008A9260
#define NET_PROCESS_ITEM_UNEQUIP_EFFECT_FN_OFFSET	0x008A9560

//Not a func, direct addr
#define CURRENT_REGION_ID_OFFSET					0x00EEF68C
class CICPlayer;
class CGame;



//Used to find out what is the object type right now.
//Can also call first vft func with LPCSTR& res to get type name of obj
#define CICPLAYER_VFT_ADDR	0x00DE2C24
#define CICUSER_VFT_ADDR	0x00DE2E7C

/*
 * 3 = Red
 * 4 = Blue
 * 0 = Green
 */

#define HIDE_CLOTHES_CLOTH_ID_FOR_SELF		4
#define HIDE_CLOTHES_CLOTH_ID_FOR_OTHERS	3

#define CURRENT_REGION_ID \
	*(__int16*)(0x00EEF68C)

void OptimizeCloth::Setup()
{

    s_lstHideClothesRegionIDs.push_back(25580);
}

void OptimizeCloth::SetOptimizeCloth(CICPlayer* player,int nClothID)
{
    player->m_CCObjAnimation_MAYBE->SetClothes(nClothID);
    player->m_CCObjAnimation_MAYBE->SetClothesApply();
}

//NOTE: You need to check if the returned CICPlayer ptr is null.
CICPlayer* OptimizeCloth::GetPlayerByGameID(DWORD dwGameID)
{
    return g_pCICPlayer->GetCICPlayerByUniqueID(dwGameID);
}

__int16 OptimizeCloth::GetCurRegionID()
{
    if (g_pCICPlayer != NULL && g_CGamePtr != NULL)
        return g_pCICPlayer->GetRegion().r;
    return 0;
}

void OptimizeCloth::ClearHideClothesRegions()
{
    s_lstHideClothesRegionIDs.clear();
}

void OptimizeCloth::AddHideClothesRegion(__int16 id)
{
    s_lstHideClothesRegionIDs.push_back(id);
}

bool OptimizeCloth::IsHideClothesRegion(__int16 id)
{
    __INDEV_HIDE_CLOTHES_REGION_ID_LST_IT it =
            std::find(s_lstHideClothesRegionIDs.begin(), s_lstHideClothesRegionIDs.end(),
                      id);
    return it != s_lstHideClothesRegionIDs.end();
}

void OptimizeCloth::ApplyHideNameClothes(CICPlayer* pObj)
{
    if (!pObj || pObj == NULL)
        return;

    DWORD dwVftAddr = *(DWORD*)(pObj);
    if (dwVftAddr == CICPLAYER_VFT_ADDR || dwVftAddr == CICUSER_VFT_ADDR)
    {
        CICPlayer* pPlayer = (CICPlayer*)(pObj);
        if (OptimizeCloth::IsHideClothesRegion(CURRENT_REGION_ID))
        {
            if (pPlayer == g_pCICPlayer)
            {
                OptimizeCloth::SetOptimizeCloth(pPlayer,4);
            }
            else
            {
                OptimizeCloth::SetOptimizeCloth(pPlayer,3);
            }
        }
    }
}

