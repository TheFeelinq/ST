#pragma once
#include "IFMainFrame.h"
#include "IFSlotWithHelp.h"

class CIFSTEffect : public CIFWnd {

GFX_DECLARE_DYNCREATE(CIFSTEffect)
GFX_DECLARE_MESSAGE_MAP(CIFSTEffect)

public:
    CIFSTEffect(void);
    ~CIFSTEffect(void);

    bool OnCreate(long ln) override;
    void OnTimer(int) override;

private:
    int OnVisibleStateChange(int a1, int a2);
public:
    void SetIgnoreDamageTime(int timeoutSeconds);
    void SetPickupTime(int timeoutSeconds);

    void SetDPSTime(int timeoutSeconds);
    void SetHWIDTime();
    void SetABSTime(int timeoutSeconds);
    void SetINCTime(int timeoutSeconds);
    void SetABSBUBBLETime(int timeoutSeconds);
    void SetINCBUBBLETime(int timeoutSeconds);
    void SetRessuretTime(int timeoutSeconds);
    void SetBattleRoyaleRegionStartTime();
    void SetBattleRoyaleRegionKillTime();
    void SetBattleRoyaleStage_1_Time(int timeoutSeconds);
    void SetBattleRoyaleStage_2_Time(int timeoutSeconds);
    void SetBattleRoyaleStage_3_Time(int timeoutSeconds);
    void SetBattleRoyaleStage_4_Time(int timeoutSeconds);
    void SetBattleRoyaleStage_5_Time(int timeoutSeconds);
public:

    CIFStatic* IgnoreDamageEffect;
    int m_IgnoreDamage_SecondsLeft;
    CIFStatic* PickupEffect;
    CIFSlotWithHelp *m_ChatLinking;
    int m_PickUp_SecondsLeft;
    int m_Dps_SecondsLeft;
    int m_ABS_SecondsLeft;
    int m_INC_SecondsLeft;
    int m_ABSBUBBLE_SecondsLeft;
    int m_INCBUBBLE_SecondsLeft;
    int m_Ressurect_SecondsLeft;
    int m_battleroyale_stage1_SecondsLeft;
    int m_battleroyale_stage2_SecondsLeft;
    int m_battleroyale_stage3_SecondsLeft;
    int m_battleroyale_stage4_SecondsLeft;
    int m_battleroyale_stage5_SecondsLeft;
};
