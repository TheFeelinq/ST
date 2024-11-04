#include "IFSTEventXoSoMienBacLichSuSlot.h"
#include "ICPlayer.h"


GFX_IMPLEMENT_DYNCREATE(CIFSTEventXoSoMienBacLichSuSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSTEventXoSoMienBacLichSuSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFSTEventXoSoMienBacLichSuSlot::CIFSTEventXoSoMienBacLichSuSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}


CIFSTEventXoSoMienBacLichSuSlot::~CIFSTEventXoSoMienBacLichSuSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFSTEventXoSoMienBacLichSuSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect0 = { 10,5,30,13 };
    RECT rect1 = { 68,5,30,13 };
    RECT rect2 = { 110,5,105,13 };
    RECT rect3 = { 320,5,70,13 };
    RECT rect4 = { 363,5,47,13 };
    RECT rect5=  { 420,5,47,13 };
    RECT rect6 = { 450,5,105,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect0, 1, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, 2, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, 3, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, 4, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, 5, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect5, 6, 0);
    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect6, 7, 0);


    m_custom_label2->MoveGWnd(m_custom_label1->GetPos().x + m_custom_label1->GetSize().width+5, m_custom_label1->GetPos().y);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width+5, m_custom_label1->GetPos().y);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width+5, m_custom_label1->GetPos().y);
    m_custom_label5->MoveGWnd(m_custom_label4->GetPos().x + m_custom_label4->GetSize().width+5, m_custom_label1->GetPos().y);
    m_custom_label6->MoveGWnd(m_custom_label5->GetPos().x + m_custom_label5->GetSize().width+5, m_custom_label1->GetPos().y);
    m_custom_label7->MoveGWnd(m_custom_label6->GetPos().x + m_custom_label6->GetSize().width+5, m_custom_label1->GetPos().y);

    m_custom_label1->SetTextColor(0xffffff);
    m_custom_label2->SetTextColor(0xffffff);
    m_custom_label3->SetTextColor(0xffffff);
    m_custom_label4->SetTextColor(0xffffff);
    m_custom_label5->SetTextColor(0xffffff);
    m_custom_label6->SetTextColor(0xffffff);
    m_custom_label7->SetTextColor(0xffffff);

    ShowGWnd(true);
    return true;
}

void CIFSTEventXoSoMienBacLichSuSlot::OnUpdate()
{
}

void CIFSTEventXoSoMienBacLichSuSlot::WriteLine(const wchar_t* num, const wchar_t* so, const wchar_t* tiencuoc, const wchar_t* trangthai,const wchar_t* loaitiente,const wchar_t* theloai,const wchar_t* ngay)
{
    if (wcscmp(trangthai, L"1") == 0)
    {
        m_custom_label4->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 255, 0, 255));
        m_custom_label4->SetText(L"Updating");
    }
    if (wcscmp(trangthai, L"2") == 0)
    {
        m_custom_label4->m_FontTexture.SetColor(D3DCOLOR_RGBA(0, 255, 0, 255));
        m_custom_label4->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_TRUNG"));
    }
    if (wcscmp(trangthai, L"3") == 0)
    {
        m_custom_label4->m_FontTexture.SetColor(D3DCOLOR_RGBA(255, 0, 0, 255));
        m_custom_label4->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_TRUOT"));
    }
    if (wcscmp(loaitiente, L"1") == 0)
    {
        m_custom_label5->SetText(L"Gold");
    }
    if (wcscmp(loaitiente, L"2") == 0)
    {
        m_custom_label5->SetText(L"Silk");
    }
    if (wcscmp(loaitiente, L"3") == 0)
    {
        m_custom_label5->SetText(L"GiftSilk");
    }
    if (wcscmp(theloai, L"1") == 0)
    {
        m_custom_label6->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_LO"));
    }
    if (wcscmp(theloai, L"2") == 0)
    {
        m_custom_label6->SetText(TSM_GETTEXTPTR("UIIT_STT_XSMB_DE"));
    }
    m_custom_label1->SetText(num);
    m_custom_label2->SetText(so);
    m_custom_label3->SetText(tiencuoc);
   // m_custom_label4->SetText(trangthai);
   // m_custom_label5->SetText(loaitiente);
   // m_custom_label6->SetText(theloai);
    m_custom_label7->SetText(ngay);

}
