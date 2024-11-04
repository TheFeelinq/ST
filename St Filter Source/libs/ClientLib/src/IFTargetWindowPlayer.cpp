#include "IFTargetWindowPlayer.h"
#include "IFStatic.h"
#include "unsorted.h"
#include "TextStringManager.h"
#include "ICPlayer.h"
#include "GInterface.h"
#include "CPSMission.h"
#include "GameDataExt.h"

#include <remodel/MemberFunctionHook.h>

#define CHECK_INFO_BTN 101
GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFTargetWindowPlayer, 0x00eea5dc)

GFX_IMPLEMENT_DYNCREATE_FN(CIFTargetWindowPlayer, CIFWnd)

enum {
    GDR_TW_KINDRED_MARK = 10, // CIFStatic
    GDR_TWP_TEXT_NAME = 1, // CIFStatic
};

GFX_BEGIN_MESSAGE_MAP(CIFTargetWindowPlayer, CIFWnd)
                    ONG_COMMAND(CHECK_INFO_BTN, &OnClick_CharInfo)
GFX_END_MESSAGE_MAP()

bool CIFTargetWindowPlayer::OnCreate(long ln) {
    //printf("%s\n", __FUNCTION__);
    //return reinterpret_cast<bool (__thiscall *)(const CIFTargetWindowPlayer *, long)>(0x0069b180)(this, ln);

    m_IRM.LoadFromFile("resinfo\\iftw_player.txt");
    m_IRM.CreateInterfaceSection("Create", this);
    RECT rect_button = {236,1,16,35};
    //RECT rect_button = {35, 70, 140, 30};
    CIFButton* m_btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         CHECK_INFO_BTN,
                                                         1);
    m_btn->TB_Func_13("interface\\quick_slot\\qsl_hopen_button.ddj", 1, 1);
    return true;
}

HOOK_ORIGINAL_MEMBER(0x0069b0d0, &CIFTargetWindowPlayer::FUN_0069b0d0);
void CIFTargetWindowPlayer::FUN_0069b0d0(int objectId) {
    m_objectId = objectId;
    CIGIDObject* pObject = GetCharacterObjectByID_MAYBE(m_objectId);
    if(pObject != NULL) {
        CPSMission::CharNameSelected=pObject->GetName().c_str();
        m_IRM.GetResObj<CIFStatic>(GDR_TWP_TEXT_NAME, 1)->SetText(pObject->GetName().c_str());
        m_IRM.GetResObj<CIFStatic>(GDR_TW_KINDRED_MARK, 1)->TB_Func_13(GetKindredTextureFilePath(pObject->GetSData()->m_nationality, 0), 0, 0);
    }
}
void CIFTargetWindowPlayer::OnClick_CharInfo()
{
        CMsgStreamBuffer buf(0x1319);
        buf << TO_NSTRING(CPSMission::CharNameSelected);
        buf << std::n_string("!CHECKCHARINFO");
        SendMsg(buf);
        g_pCGInterface->GetCharInfoGUI()->m_slot->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot1->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot2->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot3->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot4->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot5->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot6->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot7->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot8->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot9->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot10->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot11->TB_Func_13("", 0, 0);
        g_pCGInterface->GetCharInfoGUI()->m_slot12->TB_Func_13("", 0, 0);
        SCharItemInfoList.clear();
        g_pCGInterface->GetCharInfoGUI()->ShowGWnd(true);
        g_pCGInterface->GetCharInfoGUI()->MoveGWnd(this->GetPos().x+236,this->GetPos().y+1);
        g_pCGInterface->GetCharInfoGUI()->BringToFront();
}