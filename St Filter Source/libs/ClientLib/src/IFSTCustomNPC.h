#pragma once
#include "IFMainFrame.h"
#include "IFSTCustomNPCList.h"
#include <IFSelectableArea.h>
#include <IFSpinControl.h>
#include <list>

class CIFSTCustomNPC : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTCustomNPC)
GFX_DECLARE_MESSAGE_MAP(CIFSTCustomNPC)

public:
    CIFSTCustomNPC(void);
    ~CIFSTCustomNPC(void);
    int OnMouseMove(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);
    void Clear();
    void ShowList(BYTE listid);
    void WriteLineOwn(const wchar_t* Num, const wchar_t* ItemName, const wchar_t* Count, const wchar_t* Price);
    void UpdateUniqueRank();
    void UpdateGoldRank();
    void ClearDDJ();

    bool IsPageFull(BYTE PageID, BYTE LineID);
    void OnUpdate() override;
    void ResetPosition();
    void HideLists();
    void OnBuyItem();
    void OnTestItem();
public:

    static struct RankStruct
    {
        int LineNum;
        std::wstring ItemName;
        std::wstring Count;
        std::wstring Price;
    };

    static std::vector<RankStruct> UniquesRankList;
    static std::vector<RankStruct> GoldRankList;


public:
    /// Internal constants
    static const int numberOfTabs = 2;
    static const int tabWidth = 55;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 55;
    static const int tabFirstId = 100;

    CIFStatic* m_time_label;
    CIFButton *m_mybutton;
    CIFButton *m_mybutton2;
    CIFButton *m_mybutton3;
    CIFButton *m_mybutton4;
    CIFButton *m_mybutton5;
    CIFButton *m_mybutton6;
    CIFButton *m_mybutton7;
    CIFButton *m_mybutton8;
    CIFButton *m_mybutton9;
    CIFButton *m_mybutton10;
    CIFButton *m_mybutton11;
    CIFButton *m_mybutton12;
    CIFButton *m_mybutton13;
    CIFButton *m_mybutton14;
    CIFButton *m_mybutton15;
    CIFButton *m_mybutton16;
    CIFButton *m_mybutton17;
    CIFButton *m_mybutton18;
    CIFButton *m_mybutton19;
    CIFButton *m_mybutton20;
    CIFStatic* m_custom_label;
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;
    CIFStatic* m_custom_label8;
    CIFStatic* m_custom_label9;
    CIFStatic* m_custom_label10;
    CIFStatic* m_custom_label11;
    CIFStatic* m_custom_label12;
    CIFStatic* m_custom_label13;
    CIFStatic* m_custom_label14;
    CIFStatic* m_custom_label15;
    CIFStatic* m_custom_label16;
    CIFStatic* m_custom_label17;
    CIFStatic* m_custom_label18;
    CIFStatic* m_custom_label19;
    CIFStatic* m_custom_label20;
    CIFStatic* m_custom_label21;
    CIFStatic* m_custom_label22;
    CIFStatic* m_custom_label23;
    CIFStatic* m_custom_label24;
    CIFStatic* m_custom_label25;
    CIFStatic* m_custom_label26;
    CIFStatic* m_custom_label27;
    CIFStatic* m_custom_label28;
    CIFStatic* m_custom_label29;
    CIFStatic* m_custom_label30;
    CIFStatic* m_custom_label31;
    CIFStatic* m_custom_label222;

    CIFSelectableArea** m_pTabs;

    CIFSTCustomNPCList* m_slot1;
    CIFSTCustomNPCList* m_slot2;
    CIFSTCustomNPCList* m_slot3;
    CIFSTCustomNPCList* m_slot4;
    CIFSTCustomNPCList* m_slot5;
    CIFSTCustomNPCList* m_slot6;
    CIFSTCustomNPCList* m_slot7;
    CIFSTCustomNPCList* m_slot8;
    CIFSTCustomNPCList* m_slot9;
    CIFSTCustomNPCList* m_slot10;

    CIFStatic* Rank;
    CIFStatic* Charname;
    CIFStatic* Points;
    CIFStatic* Guild;
    CIFSpinControl* m_spin;
    CIFFrame* Frame;
    std::n_wstring SelectedItemName;
};



