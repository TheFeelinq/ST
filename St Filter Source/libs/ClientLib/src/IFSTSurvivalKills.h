#pragma once

#include <IFMainFrame.h>

class CIFSTSurvivalKills : public CIFMainFrame {
GFX_DECLARE_DYNCREATE(CIFSTSurvivalKills)

GFX_DECLARE_MESSAGE_MAP(CIFSTSurvivalKills)

public:
    CIFSTSurvivalKills();

    bool OnCreate(long ln) override;

    void OnUpdate() override;
public:
    void ResetPosition();
    void WriteLine(int Num, const wchar_t* Charname, const wchar_t* DMG) const;
    void Clear() const;
private:
    void On_BtnClick();


public:
    CIFStatic *m_frame_lable;
    CIFStatic *m_playername_lable;
    CIFStatic *m_damage_lable;
    CIFStatic *m_unique_icon;
    CIFStatic *m_unique_name;
    CIFStatic *m_damage_lable_slot1;
    CIFStatic *m_damage_lable_slot2;
    CIFStatic *m_damage_lable_slot3;
    CIFStatic *m_damage_lable_slot4;
    CIFStatic *m_damage_lable_slot5;
    CIFStatic *m_damage_lable_slot6;
    CIFStatic *m_damage_lable_slot7;
    CIFStatic *m_damage_lable_slot8;
    CIFStatic *m_playername_lable_slot1;
    CIFStatic *m_playername_lable_slot2;
    CIFStatic *m_playername_lable_slot3;
    CIFStatic *m_playername_lable_slot4;
    CIFStatic *m_playername_lable_slot5;
    CIFStatic *m_playername_lable_slot6;
    CIFStatic *m_playername_lable_slot7;
    CIFStatic *m_playername_lable_slot8;

    CIFStatic *m_rank_lable_slot1;
    CIFStatic *m_rank_lable_slot2;
    CIFStatic *m_rank_lable_slot3;
    CIFStatic *m_rank_lable_slot4;
    CIFStatic *m_rank_lable_slot5;
    CIFStatic *m_rank_lable_slot6;
    CIFStatic *m_rank_lable_slot7;
    CIFStatic *m_rank_lable_slot8;
};
