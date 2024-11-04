#pragma once
#include <Windows.h>
#include <list>
#include "BSLib/BSLib.h"
#include <Test/Test.h>
#include "detours.h"
#include "CObjAnimation.h"
#include "ICPlayer.h"


#define __INDEV_HIDE_CLOTHES_REGION_IDS_LST        std::list<__int16>
#define __INDEV_HIDE_CLOTHES_REGION_ID_LST_IT    __INDEV_HIDE_CLOTHES_REGION_IDS_LST::iterator

class OptimizeCloth
{

public:

    static void Setup();
    static void SetOptimizeCloth(CICPlayer* player,int nClothID);
    static CICPlayer* GetPlayerByGameID(DWORD dwGameID);
    static __int16 GetCurRegionID();
    static void ClearHideClothesRegions();
    static void AddHideClothesRegion(__int16 id);
    static void ApplyHideNameClothes(CICPlayer* pObj);
    static bool IsHideClothesRegion(__int16 id);

};