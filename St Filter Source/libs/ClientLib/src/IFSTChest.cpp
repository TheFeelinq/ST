#include "IFSTChest.h"
#include "ClientNet/MsgStreamBuffer.h"
#include <GInterface.h>
#include <sstream>
#include <BSLib/multibyte.h>
#include "IFNormalTile.h"
#include "GlobalDataManager.h"
#include "CPSMission.h"
#include "Game.h"
#include <ctime>

#define GDR_1_BTN 20
#define GDR_2_BTN 21
#define GDR_3_BTN 22
#define GDR_4_BTN 24
#define GDR_5_BTN 23
#define GDR_6_BTN 25
#define GDR_7_BTN 3
#define TIMER_CHATBLOCK 230
#define GDR_BFILTER_FRAME 31
#define GDR_BFILTER_TITLE 2
#define GDR_BFILTER_STREACH 1
#define TIMER_UPDATE_PER_SECOND 10
#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)


GFX_IMPLEMENT_DYNCREATE(CIFPlayerChest, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFPlayerChest, CIFMainFrame)
                    ONG_COMMAND(GDR_7_BTN, &CIFPlayerChest::On_BtnClick_1)
                    ONG_COMMAND(6, &CIFPlayerChest::On_BtnClick_2)
GFX_END_MESSAGE_MAP()


static int RefreshTimes = 0;

std::vector<CIFPlayerChest::Chest> CIFPlayerChest::ChestList;

CIFPlayerChest::CIFPlayerChest(void)
{

}

CIFPlayerChest::~CIFPlayerChest(void)
{

}

bool CIFPlayerChest::OnCreate(long ln)
{
    CIFMainFrame::OnCreate(ln);
    RECT rect_m_tile = {214, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIT_STT_CHEST_TILE"));

    RECT Framerect = { 17,45,180,185 };
    RECT Lablerect = { 16,308,480,62 };
    RECT Lable2rect = { 15,49,481,259 };

    RECT Butt1rect = { 68,51,224,24 };
    RECT Butt2rect = { 243,51,74,24 };
    RECT Butt3rect = { 319,51,169,24 };
    RECT Butt4rect = { 373,51,95,24 };

    RECT Spinect = { 270,320,50,16 };
    RECT Takerect = { 500,319,70,24 };
    RECT TakeAllrect = { 420,319,70,24 };

    RECT SlotCountrect = { 140,320,30,20 };
    RECT SlotCountTextrect = { 35,323,90,13 };

    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_BFILTER_FRAME, 0);

    m_custom_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect, GDR_BFILTER_TITLE, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable2rect, GDR_BFILTER_STREACH, 0);

    UniqueName = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect, GDR_3_BTN, 0);
    AliveState = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt2rect, GDR_4_BTN, 0);
    KilledBy = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt3rect, GDR_5_BTN, 0);
    SpwanTime = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt4rect, GDR_6_BTN, 0);
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);
    Take = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Takerect, GDR_7_BTN, 0);
    TakeAll = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), TakeAllrect, 6, 0);
    SlotCount = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), SlotCountrect, GDR_2_BTN, 0);
    SlotCountText = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), SlotCountTextrect, 5, 0);

    SpwanTime->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    UniqueName->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    AliveState->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    KilledBy->TB_Func_13("interface\\guild\\gil_subj_button16.ddj", 0, 0);
    m_custom_label->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 0, 0);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);
    Take->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    TakeAll->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);

    m_custom_label2->MoveGWnd(m_custom_label2->GetPos().x + 7, m_custom_label2->GetPos().y + 5);
    m_custom_label2->SetGWndSize(m_custom_label2->GetSize().width, m_custom_label2->GetSize().height - 2);

    UniqueName->MoveGWnd(m_custom_label2->GetPos().x + 2, UniqueName->GetPos().y + 5);
    AliveState->MoveGWnd(UniqueName->GetPos().x + UniqueName->GetSize().width - 9, AliveState->GetPos().y + 5);
    KilledBy->MoveGWnd(AliveState->GetPos().x + AliveState->GetSize().width - 4, KilledBy->GetPos().y + 5);
    SpwanTime->MoveGWnd(KilledBy->GetPos().x + KilledBy->GetSize().width - 7, SpwanTime->GetPos().y + 5);

    Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 50);
    Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 40);

    m_custom_label->SetGWndSize(Frame->GetBounds().size.width - 20, Frame->GetBounds().size.height - 20);
    m_custom_label->MoveGWnd(Frame->GetPos().x + 10, Frame->GetPos().y + 10);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 40, 0);
    m_slot2 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 41, 0);
    m_slot3 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 42, 0);
    m_slot4 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 43, 0);
    m_slot5 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 44, 0);
    m_slot6 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 45, 0);
    m_slot7 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 46, 0);
    m_slot8 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 47, 0);
    m_slot9 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 48, 0);
    m_slot10 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 49, 0);


    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 5);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 5);

    HideLists();
    m_slot1->ShowGWnd(true);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    //m_spin->MoveGWnd(m_spin->GetPos().x-30, m_spin->GetPos().y + 8);
    m_spin->ShowGWnd(true);

    //tests
    this->m_title->SetText(L"Chest");
    this->UniqueName->SetText(TSM_GETTEXTPTR("UIIT_CHEST_ITEMNAME"));
    this->AliveState->SetText(TSM_GETTEXTPTR("UIIT_CHEST_QUANTITY"));
    this->KilledBy->SetText(TSM_GETTEXTPTR("UIIT_CHEST_FROM"));
    this->SpwanTime->SetText(TSM_GETTEXTPTR("UIIT_CHEST_DATE"));
    this->Take->SetText(TSM_GETTEXTPTR("UIIT_CHEST_TAKE"));
    this->TakeAll->SetText(TSM_GETTEXTPTR("UIIT_CHEST_TAKE_ALL"));
    SlotCountText->SetText(L"Inventory Remaining");
    SlotCount->SetText(L"0");
    SlotCount->TB_Func_13("interface\\ifcommon\\com_bar01_mid.ddj", 0, 0);
    SlotCount->ShowGWnd(true);
    SlotCountText->ShowGWnd(true);
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    ResetPosition();
    this->ShowGWnd(false);

    //CreateThread(NULL, 0, UpdateSlotCount, NULL, 0, 0);
    return true;
}

void CIFPlayerChest::OnUpdate()
{
}
int CIFPlayerChest::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
void CIFPlayerChest::ResetPosition()
{
    const ClientRes &client = theApp.GetRes();
    wnd_size v109 = this->GetSize();
    this->MoveGWnd((client.res[0].width - v109.width) / 2, (client.res[0].height - v109.height) / 4);
}

void CIFPlayerChest::On_BtnClick_1()
{
    if (!SelectedItemName.empty())
    {
        BYTE v1 = 1;
        for (int i = 0; i < ChestList.size(); ++i)
        {
            if (wcscmp(ChestList[i].NameStrID128.c_str(), SelectedItemName.c_str()) == 0)
            {
                CMsgStreamBuffer buf(0x3505);
                buf << v1;
                buf << GET_OWN_GAME_ID();
                buf << TO_NSTRING(ChestList[i].CodeName128);
                SendMsg(buf);
                wchar_t buffer[255];
                swprintf_s(buffer,L"%d", g_CGlobalDataManager->GetEmptyInventorySlots());
                SlotCount->SetText(buffer);
                ClearDDJ();
                break;
            }
        }
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"please select item first");
        return;
    }
}

void CIFPlayerChest::On_BtnClick_2()
{
    BYTE v1 = 2;
    CMsgStreamBuffer buf(0x3505);
    buf << v1;
    buf << GET_OWN_GAME_ID();
    SendMsg(buf);
    wchar_t buffer[255];
    swprintf_s(buffer,L"%d", g_CGlobalDataManager->GetEmptyInventorySlots());
    SlotCount->SetText(buffer);
    ClearDDJ();

}

void CIFPlayerChest::OnClick_Exit()
{
    this->OnCloseWnd();
}

void CIFPlayerChest::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);
    m_slot9->ShowGWnd(false);
    m_slot10->ShowGWnd(false);
}
void CIFPlayerChest::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();
    m_slot8->ClearDDJ();
    m_slot9->ClearDDJ();
    m_slot10->ClearDDJ();
}
void CIFPlayerChest::ShowList(BYTE listid)
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
        case 9:
            HideLists();
            m_slot9->ShowGWnd(true);
            break;
        case 10:
            HideLists();
            m_slot10->ShowGWnd(true);
            break;
    }
}

bool CIFPlayerChest::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_slot6->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot6->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_slot7->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot7->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_slot8->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot8->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_slot9->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot9->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 10)
    {
        if (LineID == 30)
        {
            if (m_slot10->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot10->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }

    return full;
}

bool CIFPlayerChest::ChestContains(const wchar_t* ItemName)
{
    for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin(); it != CIFPlayerChest::ChestList.end(); ++it)
        if (wcscmp((*it).CodeName128.c_str(), ItemName) == 0)
            return true;
    return false;
}

void CIFPlayerChest::UpdateChest()
{
    wchar_t buffer[255];
    swprintf_s(buffer,L"%d", g_CGlobalDataManager->GetEmptyInventorySlots());
    SlotCount->SetText(buffer);
    int i = 0;
    for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin(); it != CIFPlayerChest::ChestList.end(); ++it)
    {
        ++i;
        // if(!(*it).NameStrID128.empty())
        //{
        (*it).LineNum = i;
        //}

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine((*it).ItemIconUrl.c_str(),(*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
        }
    }
}

void CIFPlayerChest::Clear()
{
    m_slot1->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot1->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot2->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot2->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot3->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot3->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot4->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot4->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot5->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot5->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot6->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot6->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot7->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot7->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot8->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot8->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot9->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot9->line10->WriteLine(L"", L"", L"", L"", L"");

    m_slot10->line1->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line2->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line3->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line4->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line5->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line6->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line7->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line8->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line9->WriteLine(L"", L"", L"", L"", L"");
    m_slot10->line10->WriteLine(L"", L"", L"", L"", L"");
}
