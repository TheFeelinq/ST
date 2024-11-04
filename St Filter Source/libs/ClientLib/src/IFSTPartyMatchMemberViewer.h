
#include <IFMainFrame.h>
#include "IFSTPartyMatchMemberViewerSlotList.h"


class CIFSTPartyMatchMemberViewer : public CIFMainFrame {
    GFX_DECLARE_DYNCREATE(CIFSTPartyMatchMemberViewer)

    GFX_DECLARE_MESSAGE_MAP(CIFSTPartyMatchMemberViewer)

public:
    CIFSTPartyMatchMemberViewer();

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdatePartyMemberList();
    void ClearDDJ();
    void ResetPosition();

    static struct PartyMatchMember
    {
        int LineNum;
        int Race;
        std::wstring CharName;
        std::wstring LevelText;
        std::wstring Level;

    };
    static std::vector<PartyMatchMember> PartyMatchMemberList;
public:
    CIFStatic *m_custom_label;
    CIFStatic *m_custom_label1;
    CIFStatic *m_custom_label2;
    CIFStatic *m_custom_label3;
    CIFStatic *m_custom_label4;
    CIFStatic *m_custom_label5;
    CIFStatic *m_custom_label6;
    CIFStatic *m_custom_label7;
    CIFStatic *m_custom_label8;
    CIFStatic *m_custom_label9;
    CIFStatic *m_custom_label10;

    CIFStatic *m_time_label;

    CIFSTPartyMatchMemberViewerSlotList* m_slot1;
    CIFSTPartyMatchMemberViewerSlotList* m_slot2;
    CIFSTPartyMatchMemberViewerSlotList* m_slot3;
    CIFSTPartyMatchMemberViewerSlotList* m_slot4;
    CIFSTPartyMatchMemberViewerSlotList* m_slot5;
    CIFSTPartyMatchMemberViewerSlotList* m_slot6;
    CIFSTPartyMatchMemberViewerSlotList* m_slot7;
    CIFSTPartyMatchMemberViewerSlotList* m_slot8;
};