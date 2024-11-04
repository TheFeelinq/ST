//
// Created by Admin on 9/3/2022.
//

#include "IFSTEffect.h"
#include "Game.h"
#include "IFflorian0Guide.h"
#include "GInterface.h"
#include "IFChatViewer.h"
#include "Rebot.h"
#include <sstream>
#include <HWID/HawidManager.h>
#include <HWID/base64.h>

#define TIMER_IGNORE_DAMAGE 503
#define TIMER_PICKUP 502
#define TIMER_DPS_ONOFF 504
#define TIMER_ABS_ONOFF 505
#define TIMER_INC_ONOFF 506
#define TIMER_ABSBUBBLE_ONOFF 507
#define TIMER_INCBUBBLE_ONOFF 508
#define TIMER_RESSURECT_ONOFF 509
#define TIMER_BATTLE_ROYALE_MAP_STAGE_1 610
#define TIMER_BATTLE_ROYALE_MAP_STAGE_2 611
#define TIMER_BATTLE_ROYALE_MAP_STAGE_3 612
#define TIMER_BATTLE_ROYALE_MAP_STAGE_4 613
#define TIMER_BATTLE_ROYALE_MAP_STAGE_5 614
#define TIMER_BATTLE_ROYALE_MAP_STAGE_6 615

#define TIMER_HWID_HANDLE 710
#define TIMER_BATTLE_REGION_HANDLE 711

GFX_IMPLEMENT_DYNCREATE(CIFSTEffect, CIFWnd)

GFX_BEGIN_MESSAGE_MAP(CIFSTEffect, CIFWnd)
                    ONG_VISIBLE_CHANGE()
GFX_END_MESSAGE_MAP()
CIFSTEffect::CIFSTEffect(void)
{

}

CIFSTEffect::~CIFSTEffect(void)
{

}
bool CIFSTEffect::OnCreate(long ln)
{
    CIFWnd::OnCreate(ln);


    RECT rect_IgnoreDamage = {10, 10, 230, 50};
    IgnoreDamageEffect = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_IgnoreDamage,2234,1);
    IgnoreDamageEffect->BringToFront();

    RECT rect_m_ChatLinking = { 376,157,34,34};
    m_ChatLinking = (CIFSlotWithHelp *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelp),rect_m_ChatLinking,2235,1);
    RECT rect_PickupEffect = {100, 100, 246, 246};
    PickupEffect = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_PickupEffect,2233,1);

    PickupEffect->ShowGWnd(false);
    m_ChatLinking->ShowGWnd(false);
    this->ShowGWnd(false);
    return true;
}

void CIFSTEffect::OnTimer(int timerId) {

    if (timerId == TIMER_IGNORE_DAMAGE) {

        const ClientRes &client = theApp.GetRes();
        g_pCGInterface->GetCIFSTEffectGUI()->ShowGWnd(true);
        wnd_size v109 = IgnoreDamageEffect->GetSize();
        IgnoreDamageEffect->TB_Func_13("interface\\hitcount\\ignore.ddj", 0, 0);
        IgnoreDamageEffect->BringToFront();
        if(m_IgnoreDamage_SecondsLeft > 6 )
        {
            m_IgnoreDamage_SecondsLeft--;
            IgnoreDamageEffect->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / m_IgnoreDamage_SecondsLeft);
        }
        else
        {
            g_pCGInterface->GetCIFSTEffectGUI()->ShowGWnd(false);
            this->KillTimer(TIMER_IGNORE_DAMAGE);
        }

    }
    if (timerId == TIMER_PICKUP) {

        const ClientRes &client = theApp.GetRes();
        wnd_size v108 = m_ChatLinking->GetSize();
        wnd_size v109 = PickupEffect->GetSize();

        PickupEffect->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 8);
        m_ChatLinking->MoveGWnd(PickupEffect->GetPos().x+106, PickupEffect->GetPos().y+106);
        g_pCGInterface->GetCIFSTEffectGUI()->ShowGWnd(true);
        m_ChatLinking->ShowGWnd(true);
        PickupEffect->ShowGWnd(true);
        PickupEffect->BringToFront();

        std::ostringstream temp;
        temp << m_PickUp_SecondsLeft;
        std::string imgpath = "interface\\ifcommon\\pickup_rarebox_" + temp.str() + ".ddj";
        std::n_string imgpath1 = std::n_string((imgpath.c_str()));
        PickupEffect->TB_Func_13(imgpath1, 0, 0);

        if (m_PickUp_SecondsLeft > -1) {
            m_PickUp_SecondsLeft--;
        } else {
            g_pCGInterface->GetCIFSTEffectGUI()->ShowGWnd(false);
            m_ChatLinking->ShowGWnd(false);
            PickupEffect->ShowGWnd(false);
            this->KillTimer(TIMER_PICKUP);

        }
    }
    if (timerId == TIMER_DPS_ONOFF) {

        if (m_Dps_SecondsLeft > -1) {
            m_Dps_SecondsLeft--;
        } else {
            g_pCGInterface->GetDpsMetterGUI()->ShowGWnd(false);
            this->KillTimer(TIMER_DPS_ONOFF);
        }
    }
    if (timerId == TIMER_HWID_HANDLE) {

        const char* hwid = HawidManager::GetHWID();
        std::string hwid_X = HawidManager::Xor(hwid);
        std::string hwid_1 = base64_encode(hwid_X);
        CMsgStreamBuffer packet(0x1790);
        if (!hwid_1.empty())
        {
            packet << std::n_string(hwid_1.c_str());
            SendMsg(packet);
        }
    }
    if (timerId == TIMER_BATTLE_REGION_HANDLE) {

        /*uregion CurRegion = g_pCICPlayer->GetRegion();
        D3DVECTOR CurPos = g_pCICPlayer->GetLocation();
        CMsgStreamBuffer buf(0x3561);
        buf << CurRegion.r;
        buf << (short)CurPos.x;
        buf << (short)CurPos.y;
        buf << (short)CurPos.z;
        SendMsg(buf);*/
    }
    if (timerId == TIMER_BATTLE_ROYALE_MAP_STAGE_1) {

        Rebot::Config.x1 = m_battleroyale_stage1_SecondsLeft;
        Rebot::Config.x2 = - m_battleroyale_stage1_SecondsLeft;
        if (m_battleroyale_stage1_SecondsLeft < 119) {
            m_battleroyale_stage1_SecondsLeft++;
        } else {
            Rebot::Config.cercleX = 275;
            Rebot::Config.cercleY = 202;
            Rebot::Config.cercleRadius = 134;
            this->KillTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_1);
        }
    }
    if (timerId == TIMER_BATTLE_ROYALE_MAP_STAGE_2) {

        Rebot::Config.x1 = 119 - m_battleroyale_stage2_SecondsLeft;
        Rebot::Config.x2 = -119 - m_battleroyale_stage2_SecondsLeft;
        Rebot::Config.cercle = -47 + m_battleroyale_stage2_SecondsLeft;
        if (m_battleroyale_stage2_SecondsLeft < 48) {
            m_battleroyale_stage2_SecondsLeft++;
        } else {
            Rebot::Config.cercleX = 233;
            Rebot::Config.cercleY = 202;
            Rebot::Config.cercleRadius = 114;
            this->KillTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_2);
        }
    }
    //41s
    if (timerId == TIMER_BATTLE_ROYALE_MAP_STAGE_3) {

        Rebot::Config.x1 =  71 - m_battleroyale_stage3_SecondsLeft;
        Rebot::Config.x2 = -171 - m_battleroyale_stage3_SecondsLeft;
        Rebot::Config.cercle =  m_battleroyale_stage3_SecondsLeft;
        if (m_battleroyale_stage3_SecondsLeft < 41) {
            m_battleroyale_stage3_SecondsLeft++;
        } else {
            Rebot::Config.cercleX = 233;
            Rebot::Config.cercleY = 155;
            Rebot::Config.cercleRadius = 72.5;
            this->KillTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_3);
        }
    }
    //47s
    if (timerId == TIMER_BATTLE_ROYALE_MAP_STAGE_4) {

        Rebot::Config.x1 =  31;
        Rebot::Config.x2 = - 212;
        Rebot::Config.y1 = -m_battleroyale_stage4_SecondsLeft;
        Rebot::Config.y2 = -m_battleroyale_stage4_SecondsLeft;
        Rebot::Config.cercle =  41 + m_battleroyale_stage4_SecondsLeft;
        if (m_battleroyale_stage4_SecondsLeft < 48) {
            m_battleroyale_stage4_SecondsLeft++;
        } else {
            Rebot::Config.cercleX = 235;
            Rebot::Config.cercleY = 155;
            Rebot::Config.cercleRadius = 36;
            this->KillTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_4);
        }
    }
    //51s
    if (timerId == TIMER_BATTLE_ROYALE_MAP_STAGE_5) {

        Rebot::Config.x1 =  31;
        Rebot::Config.x2 = - 212;
        Rebot::Config.y1 = -47;
        Rebot::Config.y2 = -47;
        Rebot::Config.cercle = 94 + m_battleroyale_stage5_SecondsLeft;
        if (m_battleroyale_stage5_SecondsLeft < 52) {
            m_battleroyale_stage5_SecondsLeft++;
        } else {
            Rebot::Config.cercleX = 235;
            Rebot::Config.cercleY = 155;
            Rebot::Config.cercleRadius = 15;
            this->KillTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_5);
        }
    }
    if (timerId == TIMER_RESSURECT_ONOFF) {

        wchar_t buffer[255];
        swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_AUTO_RESSURECT_TIMER"), m_Ressurect_SecondsLeft);
        CIFChatViewer *main12 = g_pCGInterface->m_IRM.GetResObj<CIFChatViewer>(1, 1);
        main12->m_ChatBlockLabel->m_FontTexture.sub_8B4400(5, 1);
        main12->m_ChatBlockLabel->SetText(buffer);
        main12-> m_ChatBlockLabel->ShowGWnd(true);


        if(m_Ressurect_SecondsLeft == 1)
        {
            CIFSlotWithHelp* pSlot;
            CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
            for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
            {
                pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                {
                    if ( pSlot->ItemInfo->GetObjectData()->TID == 14061 || pSlot->ItemInfo->GetObjectData()->TID == 14060)
                    {
                        if(pSlot->ItemInfo->m_quantity == 1)
                        {
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot5->FUN_006871d0(0);
                            g_pCGInterface->GetExtraFeatureGUI()->m_slot5->TB_Func_13("", 1, 1);
                            g_pCGInterface->GetExtraFeatureGUI()->SetAutoRessurect = false;
                            g_pCGInterface->GetExtraFeatureGUI()->m_btn7->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                        }
                        else
                        {
                            g_pCGInterface->GetExtraFeatureGUI()-> m_ressurect_slot = pSlot->UniqueID()- 100 + 0xD;
                            CMsgStreamBuffer buf(0x704C);
                            buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_ressurect_slot;
                            buf <<  pSlot->ItemInfo->GetObjectData()->TID ;
                            SendMsg(buf);
                            break;
                        }
                    }
                }

            }
        }
        if (m_Ressurect_SecondsLeft > -1) {
            m_Ressurect_SecondsLeft--;
        } else {
            main12-> m_ChatBlockLabel->ShowGWnd(false);
            this->KillTimer(TIMER_RESSURECT_ONOFF);
        }
    }
    if (timerId == TIMER_ABS_ONOFF) {

        if (m_ABS_SecondsLeft > -1) {
            m_ABS_SecondsLeft--;
        } else {

            if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS)
            {
                CIFSlotWithHelp* pSlot;
                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
                {
                    pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                    if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                    {
                        if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3768)
                        {
                            if(pSlot->ItemInfo->m_quantity == 1)
                            {
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(0);
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot1->TB_Func_13("", 1, 1);
                                g_pCGInterface->GetExtraFeatureGUI()->SetAutoABS = false;
                                g_pCGInterface->GetExtraFeatureGUI()->m_btn1->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                            }
                            else
                            {
                                g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot = pSlot->UniqueID()- 100 + 0xD;
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                break;
                            }

                        }
                    }

                }
                SetABSTime(1805);
            }
            else
                this->KillTimer(TIMER_ABS_ONOFF);

        }
    }
    if (timerId == TIMER_INC_ONOFF) {

        if (m_INC_SecondsLeft > -1) {
            m_INC_SecondsLeft--;
        } else {

            if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC)
            {
                CIFSlotWithHelp* pSlot;
                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();

                for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
                {
                    pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                    if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                    {
                        if ( pSlot->ItemInfo->GetObjectData()->ObjID == 3767)
                        {
                            if(pSlot->ItemInfo->m_quantity == 1)
                            {
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->FUN_006871d0(0);
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot2->TB_Func_13("", 1, 1);
                                g_pCGInterface->GetExtraFeatureGUI()->SetAutoINC = false;
                                g_pCGInterface->GetExtraFeatureGUI()->m_btn2->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                            }
                            else
                            {
                                g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot = pSlot->UniqueID()- 100 + 0xD;
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_inc_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                break;
                            }
                        }
                    }

                }
                SetINCTime(1805);
            }
            else
                this->KillTimer(TIMER_INC_ONOFF);

        }
    }
    if (timerId == TIMER_INCBUBBLE_ONOFF) {

        if (m_INCBUBBLE_SecondsLeft > -1) {
            m_INCBUBBLE_SecondsLeft--;
        } else {

            if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble)
            {
                CIFSlotWithHelp* pSlot;
                CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
                {
                    pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                    if(pSlot->ItemInfo && pSlot->ItemInfo != 0)
                    {
                        if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24393 ||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24389||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24385||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24401) )
                        {
                            if(pSlot->ItemInfo->m_quantity == 1)
                            {
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(0);
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot4->TB_Func_13("", 1, 1);
                                g_pCGInterface->GetExtraFeatureGUI()->SetAutoINCbubble = false;
                                g_pCGInterface->GetExtraFeatureGUI()->m_btn4->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                            }
                            else
                            {
                                g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot = pSlot->UniqueID()- 100 + 0xD;
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_Increasebubble_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                break;
                            }

                        }
                    }

                }
                SetINCBUBBLETime(1805);
            }
            else
                this->KillTimer(TIMER_INCBUBBLE_ONOFF);

        }
    }
    if (timerId == TIMER_ABSBUBBLE_ONOFF) {

        if (m_ABS_SecondsLeft > -1) {
            m_ABS_SecondsLeft--;
        } else {

            if(g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble)
            {
                for (int i = 0; i < g_pCICPlayer->m_inventorySize; i++)
                {
                    CIFSlotWithHelp* pSlot;
                    CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
                    pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
                    if(pSlot->ItemInfo && pSlot->ItemInfo != 0 )
                    {
                        if ( (pSlot->ItemInfo->GetObjectData()->ObjID == 24394 ||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24390||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24386||
                              pSlot->ItemInfo->GetObjectData()->ObjID == 24402))
                        {
                            if(pSlot->ItemInfo->m_quantity == 1)
                            {
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(0);
                                g_pCGInterface->GetExtraFeatureGUI()->m_slot3->TB_Func_13("", 1, 1);
                                g_pCGInterface->GetExtraFeatureGUI()->SetAutoABSbubble = false;
                                g_pCGInterface->GetExtraFeatureGUI()->m_btn3->SetText(TSM_GETTEXTPTR("UIIT_ST_EXTRAFEATURE_TOOLTIP12"));
                            }
                            else
                            {
                                g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot = pSlot->UniqueID()- 100 + 0xD;
                                CMsgStreamBuffer buf(0x704C);
                                buf << (byte)g_pCGInterface->GetExtraFeatureGUI()-> m_dame_absorbbubble_slot;
                                buf << (UINT16)0x0EED ;
                                SendMsg(buf);
                                break;
                            }

                        }
                    }

                }

                SetABSBUBBLETime(1805);
            }
            else
                this->KillTimer(TIMER_ABSBUBBLE_ONOFF);

        }
    }
}
void CIFSTEffect::SetPickupTime(int timeoutSeconds) {

    this->m_PickUp_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_PICKUP, 15);
}
void CIFSTEffect::SetDPSTime(int timeoutSeconds) {

    this->m_Dps_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_DPS_ONOFF, 1000);
}
void CIFSTEffect::SetABSTime(int timeoutSeconds) {

    this->m_ABS_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_ABS_ONOFF, 1000);
}
void CIFSTEffect::SetINCTime(int timeoutSeconds) {

    this->m_INC_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_INC_ONOFF, 1000);
}
void CIFSTEffect::SetABSBUBBLETime(int timeoutSeconds) {

    this->m_ABSBUBBLE_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_ABSBUBBLE_ONOFF, 1000);
}
void CIFSTEffect::SetINCBUBBLETime(int timeoutSeconds) {

    this->m_INCBUBBLE_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_INCBUBBLE_ONOFF, 1000);
}

void CIFSTEffect::SetIgnoreDamageTime(int timeoutSeconds) {

    this->m_IgnoreDamage_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_IGNORE_DAMAGE, 110);
}
void CIFSTEffect::SetRessuretTime(int timeoutSeconds) {

    this->m_Ressurect_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_RESSURECT_ONOFF, 1000);
}
void CIFSTEffect::SetBattleRoyaleStage_1_Time(int timeoutSeconds) {

    this->m_battleroyale_stage1_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_1, 1000);
}
void CIFSTEffect::SetBattleRoyaleStage_2_Time(int timeoutSeconds) {

    this->m_battleroyale_stage2_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_2, 2500);
}
void CIFSTEffect::SetBattleRoyaleStage_3_Time(int timeoutSeconds) {

    this->m_battleroyale_stage3_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_3, 3000);
}
void CIFSTEffect::SetBattleRoyaleStage_4_Time(int timeoutSeconds) {

    this->m_battleroyale_stage4_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_4, 2500);
}
void CIFSTEffect::SetBattleRoyaleStage_5_Time(int timeoutSeconds) {

    this->m_battleroyale_stage5_SecondsLeft = timeoutSeconds;
    StartTimer(TIMER_BATTLE_ROYALE_MAP_STAGE_5, 2400);
}
void CIFSTEffect::SetHWIDTime() {
    StartTimer(TIMER_HWID_HANDLE, 2 * 60000);
}
void CIFSTEffect::SetBattleRoyaleRegionStartTime() {
    StartTimer(TIMER_BATTLE_REGION_HANDLE, 5000);
}
void CIFSTEffect::SetBattleRoyaleRegionKillTime() {
    KillTimer(TIMER_BATTLE_REGION_HANDLE);
}
int CIFSTEffect::OnVisibleStateChange(int newstate, int a2)
{
    if(newstate == 1){
        IgnoreDamageEffect->sub_6526E0(0, 255, 0.2, 0.0, 1);
    }
    else
    {
        IgnoreDamageEffect->sub_6526E0(255, 0, 0.2, 0.0, 1);
    }
    return 0;

}
