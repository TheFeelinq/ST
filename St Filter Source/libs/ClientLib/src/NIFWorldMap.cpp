//
// Created by Admin on 25/8/2021.
//

#include <GFX3DFunction/RStateMgr.h>
#include <SimpleViewer/VBDynamic.h>
#include "NIFWorldMap.h"
#include "memhelp.h"
#include "NIFButton.h"
#include "unsorted.h"
#include "Rebot.h"
#include "GlobalDataManager.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "../../../DevKit_DLL/src/Util.h"
#include "GameDataExt.h"

#define _DAT_01112830 (*reinterpret_cast<int*>(0x01112830))
#define _DAT_01112e48 (*reinterpret_cast<int*>(0x01112e48))
bool CNIFWorldMap::OnCreateIMPL(long ln) {

    bool b = reinterpret_cast<bool (__thiscall *)(CNIFWorldMap *, long)>(0x006964e0)(this, ln);
    RECT Spinect = { 20,50,50,16 };
    CNIFStatic*  UniqueName = (CNIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CNIFStatic), Spinect, 5564, 0);
    UniqueName->ShowGWnd(true);
    UniqueName->SetText(L"xxxxxx");
    UniqueName->BringToFront();
    return b;
}
void CNIFWorldMap::OnUpdateIMPL()
{
    reinterpret_cast<void (__thiscall *)(CNIFWorldMap *)>(0x00697e70)(this);
}
void CNIFWorldMap::RenderMyselfIMPL() {

    reinterpret_cast<void (__thiscall *)(CNIFWorldMap *)>(0x00624380)(this);
    //reinterpret_cast<void (__thiscall *)(CNIFWorldMap *)>(0x00697e90)(this);
    if(m_map_state_change != 0)
    {
        if (DimenSionalRegion.find(g_pCICPlayer->GetRegion().r) != DimenSionalRegion.end())
        {

            //Rebot::Config.cercle = -60;
            float x1 = Rebot::Config.x1 + Rebot::Config.cercle + *((float *)((int)this + 0x95cc)); // kéo dãn bên trái
            float x2 = Rebot::Config.x2 - Rebot::Config.cercle + *((float *)((int)this + 0x95e4)); // kéo dãn bên phải
            float y1 = Rebot::Config.y1 + Rebot::Config.cercle + *((float *)((int)this + 0x95d0)); // kéo dãn bên trên
            float y2 = Rebot::Config.y2 - Rebot::Config.cercle + *((float *)((int)this + 0x9600)); //kéo dãn bên dưới

            D3DVECTOR local_6c[9];
            local_6c[0].z = 1.0;
            local_6c[2].z = 1.0;
            local_6c[4].z = 1.0;
            local_6c[6].z = 1.0;
            local_6c[8].z = 0.0;

            local_6c[1].z = 0.0;
            local_6c[3].z = 0.0;
            local_6c[5].z = 1.0;
            local_6c[7].z = 1.0;

            local_6c[1].x = 0.1;
            local_6c[3].x = 0.1;
            local_6c[5].x = 0.1;
            local_6c[7].x = 0.1;

            local_6c[1].y = 0.0;
            local_6c[3].y = 1.0;
            local_6c[5].y = 1.0;
            local_6c[7].y = 0.0;


            local_6c[0].x = x1;
            local_6c[0].y = y1;
            local_6c[2].x = x2;
            local_6c[2].y = y1;
            local_6c[4].x = x2;
            local_6c[4].y = y2;
            local_6c[6].x = x1;
            local_6c[6].y = y2;



            SYSTEMTIME time;
            GetSystemTime(&time);
            int ms = time.wMilliseconds;
            int loop = ms/200;

            std::ostringstream temp;
            int img = loop + 1;
            temp << img;
            std::string imgpath = "interface\\royale\\circle_" + temp.str() + ".ddj";
            std::wstring imgpaths = TO_WSTRING(imgpath).c_str();
            const IDirect3DBaseTexture9* puVarxx = Fun_CacheTexture_Create_3D(TO_NSTRING(imgpaths));
            g_RStateMgr.SetTextureForStage(0, puVarxx);
            g_RStateMgr.FUN_00470310(0x104);
            int local_159 = 0;
            //if (g_pDynamicVertexBuffer->IVBDynamic_Func_6((float *)((int)this + 0x95cc), 0x60, &local_159) != 0) {
            if (g_pDynamicVertexBuffer->IVBDynamic_Func_6(local_6c, 0x60, &local_159) != 0) {
                IDirect3DVertexBuffer9 *iVar5 = g_pDynamicVertexBuffer->IVBDynamic_Func_5();
                g_RStateMgr.m_pDevice->SetStreamSource(0, iVar5, 0, 0x18);
                g_RStateMgr.FUN_00470060(6, local_159, 2);
            }

            CNIFStatic *notshow1 = LoadResObj<CNIFStatic>(26);
            CNIFStatic *notshow3 = LoadResObj<CNIFStatic>(13);
            CNIFButton *notshow4 = LoadResObj<CNIFButton>(7);
            CNIFButton *notshow5 = LoadResObj<CNIFButton>(6);
            CNIFButton *notshow6 = LoadResObj<CNIFButton>(15);
            CNIFStatic *notshow7 = LoadResObj<CNIFStatic>(30);
            CNIFWnd *notshow8 = LoadResObj<CNIFWnd>(31);

            notshow1->ShowGWnd(false);
            notshow3->ShowGWnd(false);
            notshow4->ShowGWnd(false);
            notshow5->ShowGWnd(false);
            notshow6->ShowGWnd(false);
            notshow7->ShowGWnd(false);
            notshow8->ShowGWnd(false);


           /* float CenPosX = 20109.00;
            float CenPosY = 174.00;

            unsigned char byteK[2];

            byte Xsec = byteK[0] = (unsigned char)g_pCICPlayer->GetRegion().r & 0xFF;
            byte Ysec = byteK[1] = (unsigned char)((g_pCICPlayer->GetRegion().r >> 8) & 0xFF);

            float PosX = (float)((Xsec - 135) * 192 + g_pCICPlayer->GetLocation().x / 10);  // -619 2032 tọa độ trong game // =0
            float PosY = (float)((Ysec - 92) * 192 + g_pCICPlayer->GetLocation().z / 10); //-619 2032 là tâm vòng bo // = -145

            float dis = sqrt(pow(CenPosX - PosX, 2) + pow(CenPosY - PosY, 2));
            fabs(dis);
            printf(" Dis %f  \n",dis);*/
        }

    }

    //FUN_00610d30(26012,403,-79,977);
}
void CNIFWorldMap::FUN_006192f0()
{
    reinterpret_cast<void(__thiscall*)(CNIFWorldMap*)>(0x00692180)(this);
}
void CNIFWorldMap::FUN_00610d30(short region,float x,float y,float z)
{
    reinterpret_cast<void(__thiscall*)(CNIFWorldMap*,short , float,float,float)>(0x00610d30)(this,region,x,y,z);
}
int CNIFWorldMap::FUN_00620f70()
{

    if(this->IsVisible())
    {
        if (DimenSionalRegion.find(g_pCICPlayer->GetRegion().r) != DimenSionalRegion.end())
        {
            CNIFStatic *bg = LoadResObj<CNIFStatic>(666);
            wnd_rect bounds = this->GetBounds();
            bg->TB_Func_13("interface\\royale\\roc_royale.ddj",1,1);
            bg->MoveGWnd(bounds.pos.x+6,bounds.pos.y+34);
            bg->SetGWndSize(640,384);

            D3DVECTOR PlayerPos = g_pCICPlayer->GetLocation();
            D3DVECTOR CenterPos;
            CenterPos.x = 776.00;
            CenterPos.y = -13.71;
            CenterPos.z = 1780.00;
            uregion PlayerRegion = g_pCICPlayer->GetRegion();
            SimplePosToSilkPos(PlayerPos, PlayerRegion);


            CNIFStatic *icon_player = LoadResObj<CNIFStatic>(667);
            icon_player->TB_Func_13("interface\\royale\\icon_player.ddj",1,1);
            icon_player->MoveGWnd(bounds.pos.x+PlayerPos.x,bounds.pos.y+PlayerPos.y);
            icon_player->SetGWndSize(12,12);
            icon_player->BringToFront();

            CNIFStatic *notshow1 = LoadResObj<CNIFStatic>(26);
            CNIFStatic *notshow3 = LoadResObj<CNIFStatic>(13);
            CNIFButton *notshow4 = LoadResObj<CNIFButton>(7);
            CNIFButton *notshow5 = LoadResObj<CNIFButton>(6);
            CNIFButton *notshow6 = LoadResObj<CNIFButton>(15);
            CNIFStatic *notshow7 = LoadResObj<CNIFStatic>(30);
            CNIFWnd *notshow8 = LoadResObj<CNIFWnd>(31);

            notshow1->ShowGWnd(false);
            notshow3->ShowGWnd(false);
            notshow4->ShowGWnd(false);
            notshow5->ShowGWnd(false);
            notshow6->ShowGWnd(false);
            notshow7->ShowGWnd(false);
            notshow8->ShowGWnd(false);
        }
    }




    return reinterpret_cast<int(__thiscall*)(CNIFWorldMap*)>(0x00620f70)(this);

}
