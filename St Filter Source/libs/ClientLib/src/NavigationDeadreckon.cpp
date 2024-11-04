#include "StdAfx.h"
#include "NavigationDeadreckon.h"
#include "../../../DevKit_DLL/src/Util.h"
#include "ICPlayer.h"
#include "Rebot.h"
#include "Pathfinder.h"
#include "EntityManagerClient.h"

MoveTo HookMoveTo=NULL;
static uregion locationRegion;
static D3DVECTOR locationPos;
static HANDLE ThreadHandel=0;

CNavigationDeadreckon::CNavigationDeadreckon(void) {
}


CNavigationDeadreckon::~CNavigationDeadreckon(void) {
}

/*void CNavigationDeadreckon::MoveTo(uregion &region, D3DVECTOR &coord) {
    reinterpret_cast<void (__thiscall *)(CNavigationDeadreckon *, uregion *, D3DVECTOR *)>(0x009EC570)(this, &region,
                                                                                                       &coord);
}*/
void CNavigationDeadreckon::MoveToHook(uregion *region, D3DVECTOR* coord) {

    HookMoveTo(region, coord);
    //_asm {
    //    pushad
    //    pushfd
    //}
    //locationPos = *coord;
    //locationRegion = *region;

    //LocationInfo l1 = { 0, 0, 0, 0 };
    //l1.region = g_pCICPlayer->GetRegion();
    //l1.pos = g_pCICPlayer->GetLocation();
    //l1.field_0 = g_pCICPlayer->m_navcell;
    //l1.field_1 = g_pCICPlayer->m_object_under_foot;
    ////l1.pos = D3DXVECTOR3(0, 0, 0);
    //LocationInfo l2 = { 0, 0, 0,0 };
    //l2.region = *region;
    //l2.pos = *coord;
    //if (g_CRegionManagerBody.SomethingWithMapCollision_MAYBE(1, 1, &l1, &l2, 0,
    //    g_pCICPlayer)) {
    //    D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 250, 50);
    //    CIFSystemMessage* systemmessage = g_pCGInterface->GetSystemMessageView();
    //    systemmessage->WriteMessage(255, color, L"Ñ°Â·µ¼º½¿ªÊ¼", 0, 1);
    //    if (ThreadHandel)
    //        CloseHandle(ThreadHandel);
    //    ThreadHandel = CreateThread(NULL, 0, CNavigationDeadreckon::AutoMove, NULL, 0, NULL);
    //}
    //else {
    //    SendMessageA(Rebot::GameHWND, WM_MOVECHAR, (DWORD32)&locationRegion, (DWORD32)&locationPos);
    //}

    //_asm {
    //    popfd
    //    popad
    //}

}
DWORD WINAPI CNavigationDeadreckon::AutoMove(PVOID pParam) {
    if (!g_pCICPlayer)
        return 0;

    std::map<int, CIObject *>::iterator it = g_pGfxEttManager->entities.begin();
    while (it != g_pGfxEttManager->entities.end())
    {
        uregion region = it->second->GetRegion();
        D3DVECTOR location = it->second->GetLocation();

        //printf("pppp:%d,%d,%f,%f,%f\r\n", region.single.x, region.single.y,
         //      location.x, location.y, location.z);

        SendMessageA(Rebot::GameHWND, WM_MOVECHAR, (DWORD32)&region, (DWORD32)&location);
        while (true)
        {
            D3DVECTOR endPos = GetSilkPosD3D(it->second->GetRegion(), it->second->GetLocation());
            ;            if (g_pCICPlayer&&Rebot::Distance(g_pCICPlayer->GetLocation(), endPos) <=3) {
                break;
            }
            Sleep(10);
        }
        it++;
    }

    D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 150, 250);
    CIFSystemMessage* systemmessage = g_pCGInterface->GetSystemMessageView();
    systemmessage->WriteMessage(255, color, L"........", 0, 1);
    return 0;

}
void CNavigationDeadreckon::MoveTo(uregion region, D3DVECTOR coord) {
    reinterpret_cast<void (__thiscall *)(CNavigationDeadreckon *, uregion *, D3DVECTOR *)>(0x009EC570)(this, &region,&coord);
    //reinterpret_cast<void (__thiscall *)(CNavigationDeadreckon *, uregion *, D3DVECTOR *)>(HookMoveTo)(this, &region, &coord);

}
void CNavigationDeadreckon::MoveToD3D(D3DVECTOR coord) {
    uregion region = {};
    SimplePosToSilkPos(coord, region);
    MoveTo(region, coord);
    //reinterpret_cast<void(__thiscall*)(CNavigationDeadreckon*, uregion*, D3DVECTOR*)>(0x009EC570)(this, &region,
    //    &coord);
}