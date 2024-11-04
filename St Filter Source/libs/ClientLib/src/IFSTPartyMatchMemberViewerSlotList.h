#pragma once
#include "IFMainFrame.h"
#include "IFSTPartyMatchMemberViewerSlot.h"


class CIFSTPartyMatchMemberViewerSlotList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFSTPartyMatchMemberViewerSlotList)
GFX_DECLARE_MESSAGE_MAP(CIFSTPartyMatchMemberViewerSlotList)

public:
    CIFSTPartyMatchMemberViewerSlotList(void);
    ~CIFSTPartyMatchMemberViewerSlotList(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFSTPartyMatchMemberViewerSlot* line1;
    CIFSTPartyMatchMemberViewerSlot* line2;
    CIFSTPartyMatchMemberViewerSlot* line3;
    CIFSTPartyMatchMemberViewerSlot* line4;
    CIFSTPartyMatchMemberViewerSlot* line5;
    CIFSTPartyMatchMemberViewerSlot* line6;
    CIFSTPartyMatchMemberViewerSlot* line7;
    CIFSTPartyMatchMemberViewerSlot* line8;


    void ClearDDJ();
};
