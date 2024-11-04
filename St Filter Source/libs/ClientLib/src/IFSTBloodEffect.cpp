//
// Created by Admin on 11/8/2022.
//

#include "IFSTBloodEffect.h"
#include "Game.h"


GFX_IMPLEMENT_DYNCREATE(CIFSTBloodEffect, CIFWnd)

GFX_BEGIN_MESSAGE_MAP(CIFSTBloodEffect, CIFWnd)
                    ONG_VISIBLE_CHANGE()
GFX_END_MESSAGE_MAP()
CIFSTBloodEffect::CIFSTBloodEffect(void)
{

}

CIFSTBloodEffect::~CIFSTBloodEffect(void)
{

}
bool CIFSTBloodEffect::OnCreate(long ln)
{
    CIFWnd::OnCreate(ln);

    RECT rect_m_overlay = {0, 0, 0, 0};
    m_overlay = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_overlay,2236,1);
    m_overlay->TB_Func_13("interface\\orbit\\orbit_screenfade.ddj", 0, 0);
    DrawBloodEffect();
    this->ShowGWnd(false);
    return true;
}
void CIFSTBloodEffect::DrawBloodEffect()
{
    m_overlay->SetGWndSize(theApp.GetClientDimensionStuff().width, theApp.GetClientDimensionStuff().height);
    m_overlay->MoveGWnd(0,0);
}

int CIFSTBloodEffect::OnVisibleStateChange(int newstate, int a2)
{
    if(newstate == 1){
        DrawBloodEffect();
        m_overlay->sub_6526E0(0, 200, 0.4, 0.0, 1);
    }
    return 0;
}
