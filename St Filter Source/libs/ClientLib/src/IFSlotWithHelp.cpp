#include "IFSlotWithHelp.h"
#include "IFHelperBubbleWindow.h"
#include "GInterface.h"
#include "IFEquipment.h"
#include "SOItem.h"
#include "ObjectData.h"
#include "IFflorian0Guide.h"
#include "IFChatViewer.h"
#include "GlobalDataManager.h"

#include <ctime>
#include <GFX3DFunction/RStateMgr.h>
#include <SimpleViewer/VBDynamic.h>
#include <GFXMainFrame/Controler.h>

bool CIFSlotWithHelp::OnCreateIMPL(long ln) {

    bool b = reinterpret_cast<bool (__thiscall *)(CIFSlotWithHelp *, long)>(0x0066b460)(this, ln);
    return b;
}

void CIFSlotWithHelp::RenderMyselfIMPL() {



    reinterpret_cast<void (__thiscall *)(CIFSlotWithHelp *)>(0x00685e50)(this);


    bool show = false;
    if(this->GetParentWindowId()==70)
    {
        if(this->ItemInfo && this->ItemInfo != 0 && g_pCGInterface)
        {
            CSOItem* myitem = this->ItemInfo;
            CSOItem* curritem;

            int dmii = myitem->GetObjectData()->Rarity;
            int rqlevel = myitem->GetObjectData()->ReqLevel1;
            int otplevel = myitem->OptLevel;
            int itempoint = otplevel+rqlevel+(dmii*3);
            switch (myitem->GetObjectData()->TID)
            {
                case 0x132C: //ch sword
                case 0x1B2C: //ch blade
                case 0x232C: //ch spear
                case 0x2B2C: //ch glaive
                case 0x332C: //ch bow
                case 0x6B2C: //eu dagger
                case 0x3B2C: //eu 1h
                case 0x432C: //eu 2h
                case 0x4B2C: //eu axe
                case 0x632C: //eu crossbow
                case 0x532C: //eu warlock
                case 0x5B2C: //eu 2hstaff
                case 0x732C: //eu harp
                case 0x7B2C: //eu staff
                {

                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6)->dwObjID != 0)
                    {
                        curritem=g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6);
                        if(curritem && curritem !=0)
                        {
                            int dmii1 = curritem->GetObjectData()->Rarity;
                            int rqlevel1 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel1 = curritem->OptLevel;
                            int itempoint1 = otplevel1+rqlevel1+(dmii1*3);
                            if(itempoint>itempoint1)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                case 0x0A2C: //ch shield
                case 0x122C: //eu shield
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7)
                    && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                case 0x0AAC: //ch earring
                case 0x0E2C: //eu earring
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                case 0x12AC: //ch necklace
                case 0x162C: //eu necklace
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                case 0x1AAC: //ch ring
                case 0x1E2C: //eu ring
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(11);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                    //Head
                case 0x0D2C: //giap nhe eu
                case 0x092C: //2348 - giap nhe asian
                case 0x0CAC: //giap vai eu
                case 0x0DAC: //giap nang - eu
                case 0x08AC: //2220 - giap vai asian
                case 0x09AC: //2476 -  giap nang asian
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                    //Shoulder
                case 0x15AC: //giap nang eu
                case 0x10AC: //giap vai asian
                case 0x152C: //giap nhe eu
                case 0x11AC: //giap nang asian
                case 0x112C: // giap nhe asian
                case 0x14AC: //giap vai eu
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                    //Chest
                case 0x1CAC: //giap vai eu
                case 0x192C: //giap nhe asian
                case 0x18AC: //giap vai asian
                case 0x1DAC: //giap nang eu
                case 0x19AC: //giap nang asian
                case 0x1D2C: //giap nhe eu
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                    //Legs
                case 0x25AC: //giap nang eu
                case 0x21AC: //giap nang asian
                case 0x252C: //giap nhe eu
                case 0x212C: //giap nhe asian
                case 0x24AC: //giap vai eu
                case 0x20AC: //giap vai asian
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }
                    break;
                }

                    //Hands
                case 0x2CAC: //giap vai eu
                case 0x292C: //giap nhe asian
                case 0x28AC: //giap vai asian
                case 0x2DAC: //giap nang eu
                case 0x2D2C: //giap nhe eu
                case 0x29AC: //giap nang asian
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }

                    break;
                }

                    //Foot
                case 0x30AC: //giap vao asian
                case 0x312C: //giap nhe asian
                case 0x31AC: //giap nang asian
                case 0x34AC: //giap vai eu
                case 0x352C: //giap nhe eu
                case 0x35AC: //giap nang eu
                {
                    if(g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5)
                       && g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5)->dwObjID != 0)
                    {
                        curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5);
                        if(curritem && curritem !=0)
                        {
                            int dmii2 = curritem->GetObjectData()->Rarity;
                            int rqlevel2 = curritem->GetObjectData()->ReqLevel1;
                            int otplevel2 = curritem->OptLevel;
                            int itempoint2 = otplevel2+rqlevel2+(dmii2*3);
                            if(itempoint>itempoint2)
                            {
                                show = true;
                            }
                            else
                            {
                                show = false;
                            }
                        }
                        else
                        {
                            show = false;
                        }
                    }
                    else
                    {
                        show = false;
                    }

                    break;
                }
            }
        }

        SYSTEMTIME time;
        GetSystemTime(&time);
        int ms = time.wMilliseconds;
        int loop = ms/111;
        if(show)
        {
            std::ostringstream temp;
            int img = loop + 1;
            temp << img;
            std::string imgpath = "interface\\ifcommon\\thaidu0ngpr0\\bestslot\\bestslot_" + temp.str() + ".ddj";
            std::wstring imgpaths = TO_WSTRING(imgpath).c_str();
            const IDirect3DBaseTexture9* puVarxx = Fun_CacheTexture_Create_3D(TO_NSTRING(imgpaths));
            g_RStateMgr.SetTextureForStage(0, puVarxx); // icon\\etc\\icon_rudiment.ddj
            int local_159 = 0;
            //printf("%d\n",(float *)((int)this + 0x24c));
            if (g_pDynamicVertexBuffer->IVBDynamic_Func_6(&N0000062D, 0x60, &local_159) != 0) {
                IDirect3DVertexBuffer9 *iVar5 = g_pDynamicVertexBuffer->IVBDynamic_Func_5();
                g_RStateMgr.m_pDevice->SetStreamSource(0, iVar5, 0, 0x18);
                g_RStateMgr.FUN_00470060(6, local_159, 2);
            }
        }

    }



    /*    D3DVECTOR dataOut_2[6];
    g_RStateMgr.FUN_00470310(0x104);
    g_RStateMgr.SetTextureForStage(0, m_icon_item_warning); //0x63c

    int uVar9 = 0x20 - field_0x668;
    int iVar8 = (int)(uVar9 + ((int)uVar9 >> 0x1f & 7U)) >> 3;
    uVar9 = uVar9 & 0x80000007;
    if ((int)uVar9 < 0) {
        uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
    }
    dataOut_2[0].x = (float)uVar9 * 32.0 * 0.00390625; //local_6c
    dataOut_2[2].z = (float)iVar8 * 32.0 * 0.0078125; //local_4c
    dataOut_2[4].y = (float)(uVar9 + 1) * 32.0 * 0.00390625;
    dataOut_2[0].y = (float)(iVar8 + 1) * 32.0 * 0.0078125;
    dataOut_2[2].y = dataOut_2[0].x;
    dataOut_2[4].z = dataOut_2[2].z;
    dataOut_2[6].y = dataOut_2[4].y;
    dataOut_2[6].z = dataOut_2[0].y;

    int local_159 = 0;
    if (g_pDynamicVertexBuffer->IVBDynamic_Func_6(dataOut_2, 0x60, &local_159) != 0) {
        IDirect3DVertexBuffer9 *iVar5 = g_pDynamicVertexBuffer->IVBDynamic_Func_5();
        g_RStateMgr.m_pDevice->SetStreamSource(0, iVar5, 0, 0x18);
        g_RStateMgr.FUN_00470060(6, local_159, 2);

    }*/
/*    g_RStateMgr.FUN_00470310(0x104);
    g_RStateMgr.SetTextureForStage(0, m_icon_edge_rare); //0x63c
    int uVar9 = 0x20 - field_0x668;
    int iVar8 = (int)(uVar9 + ((int)uVar9 >> 0x1f & 7U)) >> 3;
    uVar9 = uVar9 & 0x80000007;
    if ((int)uVar9 < 0) {
        uVar9 = (uVar9 - 1 | 0xfffffff8) + 1;
    }

    D3DVECTOR dataOut_2[6];

    dataOut_2[0].x = (float)uVar9 * 32.0 * 0.00390625; //local_6c
    dataOut_2[2].z = (float)iVar8 * 32.0 * 0.0078125; //local_4c
    dataOut_2[4].y = (float)(uVar9 + 1) * 32.0 * 0.00390625;
    dataOut_2[0].y = (float)(iVar8 + 1) * 32.0 * 0.0078125;
    dataOut_2[2].y = dataOut_2[0].x;
    dataOut_2[4].z = dataOut_2[2].z;
    dataOut_2[6].y = dataOut_2[4].y;
    dataOut_2[6].z = dataOut_2[0].y;
    int local_159 = (int)dataOut_2[1].z;
    if (g_pDynamicVertexBuffer->IVBDynamic_Func_6(dataOut_2, 0x60, &local_159) != 0) {
        IDirect3DVertexBuffer9 *iVar5 = g_pDynamicVertexBuffer->IVBDynamic_Func_5();
        g_RStateMgr.m_pDevice->SetStreamSource(0, iVar5, 0, 0x18);
        g_RStateMgr.FUN_00470060(6, dataOut_2[0].z, 2);

    }*/


/*    D3DVECTOR dataOut_2[6];
    g_RStateMgr.SetTextureForStage(0, m_pt_edge_effect); //0x640
    dataOut_2[0].x = ((float)(-*(int *)((int)this + 0x66c) + 9) * 32.0) / 288.0;
    dataOut_2[2].z = 0.0;
    dataOut_2[4].y = 288.0 / ((float)(-*(int *)((int)this + 0x66c) + 10) * 32.0);
    dataOut_2[2].y = dataOut_2[0].x;
    dataOut_2[4].z = dataOut_2[2].z;
    dataOut_2[6].y = dataOut_2[4].y;
    dataOut_2[6].z = dataOut_2[0].y;

    int local_159 = 0;
    if (g_pDynamicVertexBuffer->IVBDynamic_Func_6(dataOut_2, 0x60, &local_159) != 0) {
        IDirect3DVertexBuffer9 *iVar5 = g_pDynamicVertexBuffer->IVBDynamic_Func_5();
        g_RStateMgr.m_pDevice->SetStreamSource(0, iVar5, 0, 0x18);
        g_RStateMgr.FUN_00470060(6, local_159, 2);

    }*/
}
void CIFSlotWithHelp::HelperBubbleInventoryAndEquipment(class CIFHelperBubbleWindow *helperBubble)
{

/*

    int Slot = GetSlotInInventory(); /// get slot in inventory
    printf("Slot:%d\n", Slot);
    int a = GetInventorySlotIndex();
    int b = GetItemSourceParentWindowId();
    int c = GetSkillSlotInDex();
    int GetParentWindow = GetParentWindowId(); /// 70 inventory - 71 equipment
    printf("GetInventorySlotIndex:%d\n", a);
    printf("GetSlotInInventory:%d\n", Slot);
    printf("GetSkillSlotInDex:%d\n", c);
    printf("GetItemSourceParentWindowId:%d\n", b);
    printf("GetParentWindowId:%d\n", GetParentWindow );
*/

/*
        if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp")) {
            if (this->ItemInfo) {

                CSOItem *myitem11 = this->ItemInfo;
                int GetSlot;
                if (this->ItemInfo && myitem11->GetObjectData()->ObjID == 3768 && GetParentWindow == 70) {
                    GetSlot = GetSlotInInventory() + 0xD;
                    CIFSTExtraFeature::m_dame_abs_slot = GetSlot;
                }
                if (this->ItemInfo && myitem11->GetObjectData()->ObjID == 3767 && GetParentWindow == 70) {
                    GetSlot = GetSlotInInventory() + 0xD;
                    CIFSTExtraFeature::m_dame_inc_slot = GetSlot;
                }

            }
        }
*/



    /*        if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp") ||
                !strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFExtQuickSlotSlot")) {
                if (this->ItemInfo) {

                    CSOItem *myitem11 = this->ItemInfo;
                    int GetSlot;
                    if (myitem11->GetObjectData()->ObjID == 3851 && this->ItemInfo) {
                        GetSlot = GetInventorySlotIndex() + 0xD;
                        CIFGlobalLink::GlobalSlot = GetSlot;
                      //  printf("Get Global slot 12:%d\n", GetSlot);
                       // printf("This Is GlobalChat");
                    }

                    if (this->ItemInfo && myitem11->GetObjectData()->ObjID == 3851 && GetParentWindow == 70) {
                        GetSlot = GetSlotInInventory() + 0xD;
                        CIFGlobalLink::GlobalSlot = GetSlot;
                       // printf("Get Global slot 70:%d\n", GetSlot);
                    }

                }
            }
*/

    /*
   CSOItem* myitem11=this->ItemInfo;;

   short ALTState1 = GetKeyState(VK_LCONTROL);
   if (ALTState1 == -127 || ALTState1 == -128) // ALT is hold
   {

           if (GetParentWindow == 70) {


               CIFChatViewer *systemmessage1 = reinterpret_cast<CIFChatViewer *>(g_pCGInterface->m_IRM.GetResObj(1,
                                                                                                                 1));
               CSOItem *this_03 = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(Slot);
               systemmessage1->m_ChatLinking->FUN_00b9daf0(1); /// unknow
               systemmessage1->m_ChatLinking->FUN_00666810(1); /// dis/en mouse click on item
               systemmessage1->m_ChatLinking->FUN_00666830(0); /// set   blur icon of item
               systemmessage1->m_ChatLinking->FUN_00666850(0); /// set   blur icon of item

               printf("ItemID:%d\n", myitem11->GetObjectData()->ObjID);
               const wchar_t *ItemName = g_CTextStringManager->GetStringTextByCode(
                       myitem11->GetObjectData()->ObjNameStrID.c_str())->c_str();

               systemmessage1->m_ChatLinking->FUN_006871d0(this_03); /// put item to slot with help
               systemmessage1->m_ChatLinking->SetInventorySlotIndex(Slot);

               wchar_t *NewMsg = new wchar_t[1024];
               wsprintfW(NewMsg, L"%s<%s>", systemmessage1->m_InputBox->GetText(), ItemName);
               systemmessage1->m_InputBox->SetText(NewMsg);
               systemmessage1->SetFocus_MAYBE();
               systemmessage1->m_InputBox->SetFocus_MAYBE();
               std::n_wstring ItemNameW = std::n_wstring(ItemName);
               UINT16 Size = ItemNameW.length();

               if((GetKeyState(VK_RBUTTON) & 0x8000) != 0) {
               NEWMSG(0x180B)
                   pReq << Slot << myitem11->GetObjectData()->ObjID;
               SENDMSG()

               }
               if((GetKeyState(VK_LBUTTON) & 0x8000) != 0) {
                   NEWMSG(0x180C)
               pReq.Write(&Size, 2);
               pReq.Write(ItemName, Size * 2);
               pReq << *ItemInfo;
               SENDMSG()
               }

       }

   }*/
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, CIFHelperBubbleWindow*)>(0x00686C50)(this, helperBubble);

}
void CIFSlotWithHelp::MakeBubble()
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*)>(0x00686DB0)(this);

}
void CIFSlotWithHelp::ShowGWnd(bool bVisible)
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, bool)>(0x00652B70)(this, bVisible);
}
void CIFSlotWithHelp::UpdateLocation(DWORD x, DWORD y)
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, int, int)>(0x6529A0)(this, x, y);
}
void CIFSlotWithHelp::FUN_006871d0(CSOItem *itemInfo)
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, CSOItem*)>(0x006871d0)(this, itemInfo);
}

void CIFSlotWithHelp::FUN_00686db0()
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*)>(0x006871d0)(this);
}
void CIFSlotWithHelp::SetInventorySlotIndex(int SlotIndex)
{
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, int)>(0x006667f0)(this, SlotIndex);
}

void CIFSlotWithHelp::FUN_00666810(undefined a1) {
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*,undefined)>(0x00666810)(this,a1);

}
void CIFSlotWithHelp::FUN_00666830(undefined a1) {
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*,undefined)>(0x00666830)(this,a1);

}
void CIFSlotWithHelp::FUN_00666850(int a1) {
    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*,int)>(0x00666830)(this,a1);

}
int CIFSlotWithHelp::GetSlotInInventory() {
    return reinterpret_cast<int (__thiscall *)(CIFSlotWithHelp *)>(0x006667e0)(this);
}
int CIFSlotWithHelp::GetInventorySlotIndex() {
    return reinterpret_cast<int (__thiscall *)(CIFSlotWithHelp *)>(0x00666800)(this);
}

int CIFSlotWithHelp::GetItemSourceParentWindowId() {
    return reinterpret_cast<int (__thiscall *)(CIFSlotWithHelp *)>(0x00666720)(this);
}
int CIFSlotWithHelp::GetParentWindowId() {
    return reinterpret_cast<int (__thiscall *)(CIFSlotWithHelp *)>(0x00666700)(this);
}
int CIFSlotWithHelp::GetSkillSlotInDex() {
    return reinterpret_cast<int (__thiscall *)(CIFSlotWithHelp *)>(0x00666730)(this);
}

void CIFSlotWithHelp::AppendAdvancedInfo(CIFHelperBubbleWindow* window)
{


    reinterpret_cast<void(__thiscall*)(CIFSlotWithHelp*, CIFHelperBubbleWindow*)>(0x0066FD60)(this, window);

    /*0: EQUIP_SLOT_HELM
    1: EQUIP_SLOT_MAIL,
    2: EQUIP_SLOT_SHOULDERGUARD,
    3: EQUIP_SLOT_GAUNTLET,
    4: EQUIP_SLOT_PANTS,
    5: EQUIP_SLOT_BOOTS,
    6: EQUIP_SLOT_WEAPON,
    7: EQUIP_SLOT_SHIELD or ARROW,
    9: EQUIP_SLOT_EARRING,
    10: EQUIP_SLOT_NECKLACE,
    11: EQUIP_SLOT_L_RING,
    12: EQUIP_SLOT_R_RING,
    */

    short ALTState = GetKeyState(VK_MENU);
    CSOItem* myitem = this->ItemInfo;
    CSOItem* curritem;

    int dmii = myitem->GetObjectData()->Rarity;
    int rqlevel = myitem->GetObjectData()->ReqLevel1;
    int otplevel = myitem->OptLevel;
    int itempoint = otplevel+rqlevel+(dmii*3);

    wchar_t buffer[45];
    wchar_t buffer1[45];
    std::wstring mymsg(L"\n     <<So Sanh Bam Alt>>");
    std::wstring mymsg1(L"\n     <<So Sanh Bam Alt>>");
    UINT msgcolor = 0xFFFFD953; //No Difference: FFFEFEFF | Better: FFFFD953 | Worse: FFFF4A4A
    UINT msgcolor1 = 0xFFFF0099;
    swprintf_s(buffer1, sizeof(buffer1), L"         ItemPoint :  %d ", itempoint);
    mymsg1.assign(buffer1);
    window->WriteLine(mymsg1, 0, msgcolor1, 0, 3);
    window->WriteLine(mymsg, 0, msgcolor, 0, 3);

    //m_brokenIcon->TB_Func_13("interface\\ifcommon\\com_item_select.ddj", 0, 0);


    if (ALTState == -127 || ALTState == -128) // ALT is hold
    {
        //printf("PVP:%d\n", Type);
        switch (myitem->GetObjectData()->TID)
        {
            case 0x132C: //ch sword
            case 0x1B2C: //ch blade
            case 0x232C: //ch spear
            case 0x2B2C: //ch glaive
            case 0x332C: //ch bow
            case 0x6B2C: //eu dagger
            case 0x3B2C: //eu 1h
            case 0x432C: //eu 2h
            case 0x4B2C: //eu axe
            case 0x632C: //eu crossbow
            case 0x532C: //eu warlock
            case 0x5B2C: //eu 2hstaff
            case 0x732C: //eu harp
            case 0x7B2C: //eu staff
            {
                int dmi = 0, dma = 0;
                float drmi = 0, drma = 0;

                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(6);


                if (myitem->PhyAtkPwrMax || curritem->PhyAtkPwrMax)
                {

                    dmi = myitem->PhyAtkPwrMin - curritem->PhyAtkPwrMin;
                    dma = myitem->PhyAtkPwrMax - curritem->PhyAtkPwrMax;

                    if (dmi == 0 && dma == 0)
                    {
                        msgcolor = 0xFFFEFEFF;
                    }
                    else if (dmi > -1 && dma > -1)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"[+%d ~ +%d]", dmi, dma);
                    }
                    else if (dmi < 0 && dma < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong vat ly. %d ~ %d", dmi, dma);
                    }
                    else if (dmi > 0 && dma < 0 && (dmi - dma) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Cong vat ly. +%d ~ %d", dmi, dma);
                    }
                    else if (dma > 0 && dmi < 0 && (dma - dmi) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Cong vat ly. %d ~ +%d", dmi, dma);
                    }
                    else if (dmi > 0 && dma < 0 && (dmi - dma) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong vat ly. +%d ~ %d", dmi, dma);
                    }
                    else if (dma > 0 && dmi < 0 && (dma - dmi) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong vat ly. %d ~ +%d", dmi, dma);
                    }


                    mymsg.assign(buffer);
                    window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                }

                if (myitem->MagAtkPwrMax || curritem->MagAtkPwrMax)
                {
                    dmi = myitem->MagAtkPwrMin - curritem->MagAtkPwrMin;
                    dma = myitem->MagAtkPwrMax - curritem->MagAtkPwrMax;

                    if (dmi == 0 && dma == 0)
                    {
                        msgcolor = 0xFFFEFEFF;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. +0 ~ +0");
                    }
                    else if (dmi > -1 && dma > -1)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. +%d ~ +%d", dmi, dma);
                    }
                    else if (dmi < 0 && dma < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. %d ~ %d", dmi, dma);
                    }
                    else if (dmi > 0 && dma < 0 && (dmi - dma) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. +%d ~ %d", dmi, dma);
                    }
                    else if (dma > 0 && dmi < 0 && (dma - dmi) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. %d ~ +%d", dmi, dma);
                    }
                    else if (dmi > 0 && dma < 0 && (dmi - dma) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. +%d ~ %d", dmi, dma);
                    }
                    else if (dma > 0 && dmi < 0 && (dma - dmi) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Cong phep thuat. %d ~ +%d", dmi, dma);
                    }

                    mymsg.assign(buffer);
                    window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                }

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->AttackRateValue - curritem->AttackRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Khoang cach tan cong +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Khoang cach tan cong %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Khoang cach tan cong +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->CriticalValue - curritem->CriticalValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le ra don chi mang +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le ra don chi mang %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le ra don chi mang +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                if (myitem->PhyReinforcementMax || curritem->PhyReinforcementMax)
                {
                    drmi = myitem->PhyReinforcementMin - curritem->PhyReinforcementMin;
                    drma = myitem->PhyReinforcementMax - curritem->PhyReinforcementMax;

                    if (drmi == 0 && drma == 0)
                    {
                        msgcolor = 0xFFFEFEFF;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly +0%% ~ +0%%");
                    }
                    else if (drmi > -1 && drma > -1)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly +%.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi < 0 && drma < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly %.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi > 0 && drma < 0 && (drmi - drma) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drma > 0 && drmi < 0 && (drma - drmi) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi > 0 && drma < 0 && (drmi - drma) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drma > 0 && drmi < 0 && (drma - drmi) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }

                    mymsg.assign(buffer);
                    window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                }

                if (myitem->MagReinforcementMax || curritem->MagReinforcementMax)
                {
                    drmi = myitem->MagReinforcementMin - curritem->MagReinforcementMin;
                    drma = myitem->MagReinforcementMax - curritem->MagReinforcementMax;

                    if (drmi == 0 && drma == 0)
                    {
                        msgcolor = 0xFFFEFEFF;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat +0%% ~ +0%%");
                    }
                    else if (drmi > -1 && drma > -1)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat +%.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi < 0 && drma < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat %.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi > 0 && drma < 0 && (drmi - drma) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drma > 0 && drmi < 0 && (drma - drmi) > 0)
                    {
                        msgcolor = 0xFFFFD953;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drmi > 0 && drma < 0 && (drmi - drma) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat +%.1f%% ~ %.1f%%", drmi * 100, drma * 100);
                    }
                    else if (drma > 0 && drmi < 0 && (drma - drmi) < 0)
                    {
                        msgcolor = 0xFFFF4A4A;
                        swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat %.1f%% ~ +%.1f%%", drmi * 100, drma * 100);
                    }

                    mymsg.assign(buffer);
                    window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                }
                break;
            }

            case 0x0A2C: //ch shield
            case 0x122C: //eu shield
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(7);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->BlockingRateValue - curritem->BlockingRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le chan +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le chan %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le chan +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

            case 0x0AAC: //ch earring
            case 0x0E2C: //eu earring
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(9);
                float drmi = 0;
                drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagAbsorption - curritem->MagAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

            case 0x12AC: //ch necklace
            case 0x162C: //eu necklace
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(10);
                float drmi = 0;
                drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagAbsorption - curritem->MagAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

            case 0x1AAC: //ch ring
            case 0x1E2C: //eu ring
            {
                CIFEquipment* myequipments = g_pCGInterface->GetMainPopup()->GetEquipment();
                curritem = myequipments->GetEquipmentObjectBySlot(11);

                float drmi = 0;
                mymsg.assign(L"<<Tr¸i>>");
                msgcolor = 0xFFEFDAA4;
                window->WriteLine(mymsg, 0, msgcolor, 0, 2);

                drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagAbsorption - curritem->MagAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                curritem = myequipments->GetEquipmentObjectBySlot(12);

                mymsg.assign(L"\n<<Ph¶i>>");
                msgcolor = 0xFFEFDAA4;
                window->WriteLine(mymsg, 0, msgcolor, 0, 2);

                drmi = myitem->PhyAbsorption - curritem->PhyAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu vat ly +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagAbsorption - curritem->MagAbsorption;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le hap thu phep thuat +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Head
            case 0x0D2C: //giap nhe eu
            case 0x092C: //2348 - giap nhe asian
            case 0x0CAC: //giap vai eu
            case 0x0DAC: //giap nang - eu
            case 0x08AC: //2220 - giap vai asian
            case 0x09AC: //2476 -  giap nang asian
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(0);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Shoulder
            case 0x15AC: //giap nang eu
            case 0x10AC: //giap vai asian
            case 0x152C: //giap nhe eu
            case 0x11AC: //giap nang asian
            case 0x112C: // giap nhe asian
            case 0x14AC: //giap vai eu
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(2);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Chest
            case 0x1CAC: //giap vai eu
            case 0x192C: //giap nhe asian
            case 0x18AC: //giap vai asian
            case 0x1DAC: //giap nang eu
            case 0x19AC: //giap nang asian
            case 0x1D2C: //giap nhe eu
            {
                curritem =g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(1);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Legs
            case 0x25AC: //giap nang eu
            case 0x21AC: //giap nang asian
            case 0x252C: //giap nhe eu
            case 0x212C: //giap nhe asian
            case 0x24AC: //giap vai eu
            case 0x20AC: //giap vai asian
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(4);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Hands
            case 0x2CAC: //giap vai eu
            case 0x292C: //giap nhe asian
            case 0x28AC: //giap vai asian
            case 0x2DAC: //giap nang eu
            case 0x2D2C: //giap nhe eu
            case 0x29AC: //giap nang asian
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(3);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }

                //Foot
            case 0x30AC: //giap vao asian
            case 0x312C: //giap nhe asian
            case 0x31AC: //giap nang asian
            case 0x34AC: //giap vai eu
            case 0x352C: //giap nhe eu
            case 0x35AC: //giap nang eu
            {
                curritem = g_pCGInterface->GetMainPopup()->GetEquipment()->GetEquipmentObjectBySlot(5);
                int dmi = 0;
                float drmi = 0;
                drmi = myitem->PhyDefPwrValue - curritem->PhyDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu vat ly. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagDefPwrValue - curritem->MagDefPwrValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +%.1f", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. %.1f", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Thu phep thuat. +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->MaxDurability - curritem->MaxDurability;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Do ben +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                dmi = myitem->ParryRateValue - curritem->ParryRateValue;
                if (dmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +%d", dmi);
                }
                else if (dmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do %d", dmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Ty le do +0");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->PhyReinforcementValue - curritem->PhyReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang vat ly. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);

                drmi = myitem->MagReinforcementValue - curritem->MagReinforcementValue;
                if (drmi > 0)
                {
                    msgcolor = 0xFFFFD953;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +%.1f%%", drmi);
                }
                else if (drmi < 0)
                {
                    msgcolor = 0xFFFF4A4A;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. %.1f%%", drmi);
                }
                else
                {
                    msgcolor = 0xFFFEFEFF;
                    swprintf_s(buffer, sizeof(buffer), L"Gia tang phep thuat. +0%%");
                }
                mymsg.assign(buffer);
                window->WriteLine(mymsg, 0, msgcolor, 0, 1);
                break;
            }
        }
    }
}
