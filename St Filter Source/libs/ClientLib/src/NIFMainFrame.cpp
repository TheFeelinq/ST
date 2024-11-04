//
// Created by Admin on 22/3/2022.
//

#include "NIFMainFrame.h"
#include "Game.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CNIFMainFrame, 0x115DFA8)

GFX_BEGIN_MESSAGE_MAP(CNIFMainFrame, CNIFWnd)
                    ONG_COMMAND(2, &OnClick_Exit)
GFX_END_MESSAGE_MAP()

#define GDR_STA_TITLE 0
#define GDR_STA_DRAG 1
#define GDR_BTN_CLOSE 2

CNIFMainFrame::CNIFMainFrame()
        : m_title(NULL), m_handleBar(NULL), m_close(NULL) {
}

bool CNIFMainFrame::OnCreate(long ln) {
    BS_DEBUG_LOW("%s", __FUNCTION__);
    return reinterpret_cast<bool(__thiscall*)(CNIFMainFrame*, long)>(0x00479a50)(this, ln);


    CNIFFrame::OnCreate(ln);

    wnd_rect local_10 = GetBounds();

    wnd_rect sz;
    sz.pos.x = 10;
    sz.pos.y = 12;
    sz.size.height = 12;
    sz.size.width = local_10.size.width - 21;

    m_title = (CNIFStatic*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_STA_TITLE, 0);
    BS_DEBUG("Created title at %d|%d [%d|%d]", sz.pos.x, sz.pos.y, sz.size.width, sz.size.height);

    sz.pos.y = 0;
    sz.size.height = 34;

    m_handleBar = (CNIFDragableArea*)CreateInstance(this, GFX_RUNTIME_CLASS(CNIFDragableArea), sz, GDR_STA_DRAG, 0);
    BS_DEBUG("Created handlebar at %d|%d [%d|%d]", sz.pos.x, sz.pos.y, sz.size.width, sz.size.height);

    sz.size.height = 16;
    sz.size.width = 16;
    sz.pos.x = local_10.size.width - 26;
    sz.pos.y = 10;

    m_close = (CIFCloseButton*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCloseButton), sz, GDR_BTN_CLOSE, 0);
    BS_DEBUG("Created close btn at %d|%d [%d|%d]", sz.pos.x, sz.pos.y, sz.size.width, sz.size.height);

    RECT rect;
    m_title->SetSomeRect(rect);
    //m_title->SetFont(theApp.GetFont(0));
    m_title->TB_Func_5(1);
    m_title->TB_Func_6(0);


    m_handleBar->SetSomeRect(rect);
    //m_handleBar->SetFont(theApp.GetFont(0));
    m_handleBar->TB_Func_5(1);
    m_handleBar->TB_Func_6(0);


    m_close->SetSomeRect(rect);
    m_close->SetFont(theApp.GetFont(0));
    m_close->TB_Func_5(1);
    m_close->TB_Func_6(0);


    return true;
}

void CNIFMainFrame::SetGWndSize(int width, int height) {
    assert(FALSE);
}

bool CNIFMainFrame::SetText(const wchar_t *Src) {
    return reinterpret_cast<bool (__thiscall *)(CNIFMainFrame *, const wchar_t *)>(0x0046c2f0)(this, Src);
}

void CNIFMainFrame::OnClick_Exit() {
    this->OnCloseWnd();
}