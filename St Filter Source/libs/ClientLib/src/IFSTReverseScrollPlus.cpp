#include "IFSTReverseScrollPlus.h"
#include "IFNormalTile.h"
#include <ctime>
#include "GInterface.h"
#include "IFMessageBox.h"
#include "IFflorian0Guide.h"
#include "PartyData.h"
#include "CharacterDependentData.h"
#include "Game.h"
#include <BSLib/multibyte.h>
#include <sstream>
#define GDR_PARTY_MEMBER_RT_LABEL 10
#define GDR_PARTY_MEMBER_RT_BTN 11
#define GDR_PARTY_MEMBER_RT_LABEL_TIME 13
#define GDR_PARTY_MEMBER_RT_MAIN_FRAME 20
#define GDR_PARTY_MEMBER_RT_BTN_APPLY 21
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)
byte CIFSTReverseScrollPlus::ReverseSlot;
GFX_IMPLEMENT_DYNCREATE(CIFSTReverseScrollPlus, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFSTReverseScrollPlus, CIFMainFrame)
                    ONG_COMMAND(GDR_PARTY_MEMBER_RT_BTN_APPLY, &On_BtnClick)
GFX_END_MESSAGE_MAP()

std::vector<CIFSTReverseScrollPlus::ReverseScrollPlus> CIFSTReverseScrollPlus::ReverseScrollPlusList;
CIFSTReverseScrollPlus::CIFSTReverseScrollPlus() :
        m_custom_label(NULL) {

}

bool CIFSTReverseScrollPlus::OnCreate(long ln) {
    CIFMainFrame::OnCreate(ln);

    // Set own title
    RECT rect_m_tile = {195, 9, 100, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_LABLE"));

    TB_Func_13("interface\\frame\\mframe_wnd_", 1, 0);


    RECT rect_frame = {12, 40, 478,298};

    CIFFrame *frame = (CIFFrame *) CreateInstance(this,
                                                  GFX_RUNTIME_CLASS(CIFFrame),
                                                  rect_frame,
                                                  GDR_PARTY_MEMBER_RT_MAIN_FRAME,
                                                  1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 0);

    RECT rect_background = {rect_frame.left + 10,
                            rect_frame.top + 10,
                            rect_frame.right - 20,
                            rect_frame.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_PARTY_MEMBER_RT_MAIN_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    /////////////////
    RECT Butt1rect = { 25,56,59,24 };
    RECT Butt2rect = { 83,56,163,24 };
    RECT Butt3rect = { 241,56,139,24 };
    RECT Butt4rect = { 376,56,102,24 };


    Num = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_PARTY_MEMBER_RT_MAIN_FRAME, 0);
    CharName = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt2rect, GDR_PARTY_MEMBER_RT_MAIN_FRAME, 0);
    Location = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt3rect, GDR_PARTY_MEMBER_RT_MAIN_FRAME, 0);
    Move = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_PARTY_MEMBER_RT_MAIN_FRAME, 0);
    wchar_t buffer[80];
    wchar_t buffer1[80];
    wchar_t buffer2[80];
    wchar_t buffer3[80];
    swprintf_s(buffer, TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_STT"));
    swprintf_s(buffer1, TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_CHARNAME"));
    swprintf_s(buffer2, TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_LOCATION"));
    swprintf_s(buffer3, TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_GUILD"));

    Num->SetText(buffer);
    CharName->SetText(buffer1);
    Location->SetText(buffer2);
    Move->SetText(buffer3);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 40, 0);
    m_slot2 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 41, 0);
    m_slot3 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 42, 0);
    m_slot4 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 43, 0);
    m_slot5 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 44, 0);
    m_slot6 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 45, 0);
    m_slot7 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 46, 0);
    m_slot8 = (CIFSTReverseScrollPlusSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSTReverseScrollPlusSlotList), rect, 47, 0);


    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);

    Num->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    CharName->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    Location->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    Move->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);

    ///////// button
    RECT rect_button = {195,284,114,24};
    //RECT rect_button = {35, 70, 140, 30};
    btn = (CIFButton *) CGWnd::CreateInstance(this,
                                                         GFX_RUNTIME_CLASS(CIFButton),
                                                         rect_button,
                                                         GDR_PARTY_MEMBER_RT_BTN_APPLY,
                                                         1);

    btn->SetText(TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_MOVE"));
    btn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    HideLists();
    m_slot1->ShowGWnd(true);


    m_ReverseScollSlot=0;
    ReverseSlot=0;
    //////////////
    this->ShowGWnd(false);
    return true;
}

bool CIFSTReverseScrollPlus::GetBtnStatus() const
{
    return m_BtnState;
}

void CIFSTReverseScrollPlus::On_BtnClick() {
    if (!SelectedCharName.empty())
    {
        std::n_string CharName;
        for (int i = 0; i < ReverseScrollPlusList.size(); ++i)
        {
            if (wcscmp(ReverseScrollPlusList[i].CharName.c_str(), SelectedCharName.c_str()) == 0)
            {
                CharName = TO_NSTRING(ReverseScrollPlusList[i].CharName);
            }
        }
        CSOItem *this_03 = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(m_ReverseScollSlot);
        if(this_03)
        {
            if(this_03->GetObjectData()->TID == 0x19EC || this_03->GetObjectData()->TID == 0x19ED)
            {
                BYTE Slot =  m_ReverseScollSlot+0xD;
                const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
                if(partyData.NumberOfMembers > 0)
                {
                    CMsgStreamBuffer buf(0x704c);
                    buf << (BYTE)Slot;
                    buf << this_03->GetObjectData()->TID;
                    buf << (BYTE)0x8;
                    buf <<  (BYTE)(partyData.NumberOfMembers);
                    for (size_t i = 0; i < partyData.NumberOfMembers; ++i)
                    {
                        const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);
                        if (wcscmp(memberData.m_charactername.c_str(), SelectedCharName.c_str()) == 0)
                        {
                            buf << (UINT32)(memberData.UserJID);
                            buf << (UINT32)(memberData.currentLevel);
                            buf << std::n_string(TO_NSTRING(memberData.m_charactername));
                            buf << (short)(memberData.region.r);
                            if(memberData.region.r > 0)
                            {
                                buf << (int)(memberData.position.x);
                                buf << (int)(memberData.position.y);
                                buf << (int)(memberData.position.z);
                            } else
                            {
                                buf << (UINT16)(memberData.position.x);
                                buf << (UINT16)(memberData.position.y);
                                buf << (UINT16)(memberData.position.z);
                            }
                            break;
                        }
                    }
                    SendMsg(buf);
                    SelectedCharName=L"";
                }
                ClearDDJ();
                this->ShowGWnd(false);
            }
        }

    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_NOTICE"));
        return;
    }

}

void CIFSTReverseScrollPlus::OnUpdate() {

    if (g_pCICPlayer) {

        //printf(" g_pCICPlayer->Status : %d \n",g_pCICPlayer->Status);
        const SPartyData &partyData = g_CCharacterDependentData.GetPartyData();
        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->Clear();
        CIFSTReverseScrollPlus::ReverseScrollPlusList.clear();

        for (int i = 0; i < partyData.NumberOfMembers; ++i) {
            const SPartyMemberData &memberData = g_CCharacterDependentData.GetPartyMemberData(i);

            CIFSTReverseScrollPlus::ReverseScrollPlus UniqueHis = CIFSTReverseScrollPlus::ReverseScrollPlus();
            std::wstringstream Reg;
            Reg <<memberData.region.r;

            UniqueHis.LineNum = i;
            UniqueHis.CharName =memberData.m_charactername.c_str();
            UniqueHis.Location = g_CTextStringManager->GetString(Reg.str().c_str())->c_str();
            UniqueHis.Move = memberData.m_guildname.c_str();
            g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->ReverseScrollPlusList.push_back(UniqueHis);

            g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->UpdatePartyMemberList();

        }

    }
}
int CIFSTReverseScrollPlus::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFSTReverseScrollPlus::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);

}
void CIFSTReverseScrollPlus::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();
    m_slot8->ClearDDJ();

}
void CIFSTReverseScrollPlus::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            m_slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            m_slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            m_slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            m_slot4->ShowGWnd(true);
            break;
        case 5:
            HideLists();
            m_slot5->ShowGWnd(true);
            break;
        case 6:
            HideLists();
            m_slot6->ShowGWnd(true);
            break;
        case 7:
            HideLists();
            m_slot7->ShowGWnd(true);
            break;
        case 8:
            HideLists();
            m_slot8->ShowGWnd(true);
            break;

    }
}
void CIFSTReverseScrollPlus::UpdatePartyMemberList()
{

    for (std::vector<CIFSTReverseScrollPlus::ReverseScrollPlus>::iterator it = CIFSTReverseScrollPlus::ReverseScrollPlusList.begin(); it != CIFSTReverseScrollPlus::ReverseScrollPlusList.end(); ++it)
    {

        switch ((*it).LineNum)
        {
            case 0:
            {
                m_slot1->line1->WriteLine(L"1",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 1:
            {
                m_slot1->line2->WriteLine(L"2",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line3->WriteLine(L"3",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line4->WriteLine(L"4",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line5->WriteLine(L"5",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line6->WriteLine(L"6",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line7->WriteLine(L"7",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line8->WriteLine(L"8",(*it).CharName.c_str(), (*it).Location.c_str(), (*it).Move.c_str());
            }
                break;

        }
    }
}
void CIFSTReverseScrollPlus::Clear()
{
    m_slot1->line1->WriteLine(L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"", L"", L"", L"");


}
void CIFSTReverseScrollPlus::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}