#pragma once
#include "IFMainFrame.h"

class CIFSTPartyMatchMemberViewerSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTPartyMatchMemberViewerSlot)
GFX_DECLARE_MESSAGE_MAP(CIFSTPartyMatchMemberViewerSlot)

public:
    CIFSTPartyMatchMemberViewerSlot(void);
    ~CIFSTPartyMatchMemberViewerSlot(void);
    bool OnCreate(long ln) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;

    void WriteLine(int Race, const wchar_t* CharName, const wchar_t* LevelText, const wchar_t* Level);
};
