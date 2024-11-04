#pragma once

#include <IFMainFrame.h>

class CIFSTBattleRoyaleKillCount : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTBattleRoyaleKillCount)

GFX_DECLARE_MESSAGE_MAP(CIFSTBattleRoyaleKillCount)

public:

    bool OnCreate(long ln) override;

    void OnUpdate() override;
public:
    void ResetPosition();

public:
    CIFStatic *m_frame;
    CIFStatic *m_left_survivor_lable;
    CIFStatic *m_total_participants;
    CIFStatic *m_my_kill_lable;

    CIFStatic *m_left_survivor_value;
    CIFStatic *m_total_participants_value;
    CIFStatic *m_my_kill_value;

};
