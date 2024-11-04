#include "IFSTReverseScrollPlusSlot.h"
#include "IFflorian0.h"
#include "GInterface.h"
#include "IFflorian0Guide.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include <ctime>

#define STFILTER_SLOT_PARTYMEMBER_NUM 1
#define STFILTER_SLOT_PARTYMEMBER_CHARNAME 2
#define STFILTER_SLOT_PARTYMEMBER_LOCATION 3
#define STFILTER_SLOT_PARTYMEMBER_MOVE 4
#define STFILTER_SLOT_PARTYMEMBER_TIME 5

GFX_IMPLEMENT_DYNCREATE(CIFSTReverseScrollPlusSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTReverseScrollPlusSlot, CIFWnd)
                    ONG_COMMAND(STFILTER_SLOT_PARTYMEMBER_MOVE, &OnButtonClick)
GFX_END_MESSAGE_MAP()

CIFSTReverseScrollPlusSlot::CIFSTReverseScrollPlusSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFSTReverseScrollPlusSlot::~CIFSTReverseScrollPlusSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTReverseScrollPlusSlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 18,5,50,13 };
    RECT rect2 = { 275,5,147,13 };
    RECT rect3 = { 330,5,124,13 };
    RECT rect4 = { 480,2,50,20 };

    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, STFILTER_SLOT_PARTYMEMBER_NUM, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, STFILTER_SLOT_PARTYMEMBER_CHARNAME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, STFILTER_SLOT_PARTYMEMBER_LOCATION, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, STFILTER_SLOT_PARTYMEMBER_MOVE, 0);
   // MoveTo = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), rect4, STFILTER_SLOT_PARTYMEMBER_MOVE, 0);

    m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 10, m_custom_label3->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 10, m_custom_label4->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width + 30, m_custom_label5->GetPos().y);


    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);
    m_custom_label5->m_FontTexture.SetColor(0xffffff);
    //MoveTo->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label4->BringToFront();
    m_custom_label5->BringToFront();
   // MoveTo->SetText(TSM_GETTEXTPTR("UIIT_ST_PARTY_MEMBER_TO"));
   // MoveTo->ShowGWnd(false);
    this->ShowGWnd(false);
    return true;
}

void CIFSTReverseScrollPlusSlot::WriteLine(const wchar_t* Num, const wchar_t* CharName, const wchar_t* Location, const wchar_t* Move)
{

    m_custom_label2->SetText(Num);
    m_custom_label3->SetText(CharName);
    m_custom_label4->SetText(Location);
    m_custom_label5->SetText(Move);

}

int CIFSTReverseScrollPlusSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label2->GetNText().empty())
    {
        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->ClearDDJ();
        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->SelectedCharName = m_custom_label3->GetNText();
        TB_Func_13("interface\\ifcommon\\com_bar01select_mid.ddj", 0, 0);
    }
    return 0;
}
void CIFSTReverseScrollPlusSlot::OnButtonClick() {

    printf("button click detected");
}