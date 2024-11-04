#pragma once
#include "IFMainFrame.h"
#include "IFSTCustomRankList.h"
#include "IFNormalTile.h"
#include "IFCheckBox.h"
#include "IFSlotWithHelp.h"
#include "IFEdit.h"
#include "IFSliderCtrl.h"
#include "IFSTMacroAutoBuffSlotList.h"
#include "IFSTMacroAutoBuffSkillSlotList.h"
#include "IFSTMacroAutoBuffedSkillSlotList.h"
#include <IFSelectableArea.h>
#include <IFSpinControl.h>
#include <list>

class CIFSTMacroAutoHunt : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTMacroAutoHunt)
GFX_DECLARE_MESSAGE_MAP(CIFSTMacroAutoHunt)

public:
    CIFSTMacroAutoHunt(void);
    ~CIFSTMacroAutoHunt(void);
    int OnMouseMove(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    bool Func_28(int a1, int a2, int a3) override;
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void OnUpdate() override;
    void ResetPosition();
    void OnListChatThing(int, int);
    void OnListSelectRange();
    void OnSaveClick();
    void OnSave2Click();
    void OnSave3Click();
    void OnCancelClick();
    void OnListSelectRangeState(bool state);
    void OnListSelectTab(bool state);
    void OnListSelectTabPotion(bool state);
    void OnListSelectTabPet(bool state);
    void OnListSelectTabBuff(bool state);
    void OnLoadSkillTabBuff();
    int OnMouseLeftUp(int a1, int x, int y) override;
    bool IsAutoBerserkChecked() const;
    bool IsGoBackCenterChecked() const;
    bool IsAttackHostilityChecked() const;
    bool IsRequestJoinPartyChecked() const;
    bool IsAutoLureChecked() const;
    bool IsAutoAcceptResChecked() const;
    bool IsAutoResPartyMemberChecked() const ;
    bool IsAutoAttackOtherPlayerChecked() const;
    bool IsAutoHPChecked() const;
    bool IsAutoMPChecked() const;
    bool IsAutoAbnormalChecked() const;
    bool IsAutoVigorChecked() const;
    bool IsAutoSpeedScrollChecked() const;
    bool IsAutoPetHpChecked() const;
    bool IsAutoPetHgpChecked() const;
    bool IsAutoPetCureChecked() const;
    bool IsAutoPetResurrectChecked() const;
    bool IsAutoPetTriggerChecked() const;
    bool IsAutoPetTradeHPChecked() const;
    bool IsAutoPetRiddingHPChecked() const;
    bool IsAutoBuffModeChecked() const;
    bool IsAutoAttackSnowManAndPillarChecked() const;
    void Clear();
    void ClearDDJ();
    void Clear2();
    void ClearDDJ2();
    void Clear3();
    void ClearDDJ3();
    void UpdatePartyMemberList();
    void UpdateSkillBuffedList(std::n_wstring SelectedCharName);
    void UpdateSkilDataList();
    void HideLists();
    void On_Buff_AddSkill();
    void On_Buff_RemoveSkill();
public:
    /// Internal constants
    static const int numberOfTabs = 4;
    static const int tabWidth = 100;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 100;
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
    CIFNormalTile* m_custom_label;
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
    CIFStatic* m_custom_label_fellowpet;
    CIFStatic* m_custom_label_tradepet;
    CIFStatic* m_custom_label_partymemberlist;
    CIFStatic* m_custom_label_skilllist;
    CIFStatic* m_custom_label_skillbuffedlist;

    CIFSelectableArea** m_pTabs;
    CIFFrame* Frame;
    CIFFrame* Frame2;
    CIFNormalTile* m_custom_NormalTile;
    CIFTextBox* m_custom_textbox_range;
    CIFCheckBox *m_checkbox_berserk;
    CIFCheckBox *m_checkbox_goback_center;
    CIFCheckBox *m_checkbox_attack_hostility;
    CIFCheckBox *m_checkbox_accept_request_joinparty;
    CIFCheckBox *m_checkbox_luremode;
    CIFCheckBox *m_checkbox_accept_res;
    CIFCheckBox *m_checkbox_res_partymember;
    CIFCheckBox *m_checkbox_attack_other_player;
    CIFCheckBox *m_checkbox_buff_mode;
    CIFCheckBox *m_checkbox_attack_snowman_and_pillar;
    CIFStatic* m_custom_bg;
    CIFStatic* m_custom_bg2;
    CIFStatic* m_custom_bg3;
    CIFStatic* m_custom_bg4;
    CIFStatic* m_custom_bg5;
    CIFStatic* m_custom_bg6;
    CIFStatic* m_custom_bg7;
    CIFStatic* m_custom_bg8;
    CIFStatic* m_custom_bg9;
    CIFStatic* m_custom_bg10;
    CIFStatic* m_custom_bg11;

    CIFSlotWithHelp *m_slot1;
    CIFSlotWithHelp *m_slot2;
    CIFSlotWithHelp *m_slot3;
    CIFSlotWithHelp *m_slot4;
    CIFSlotWithHelp *m_slot5;

    CIFSlotWithHelp *m_slot6;
    CIFSlotWithHelp *m_slot7;
    CIFSlotWithHelp *m_slot8;
    CIFSlotWithHelp *m_slot9;
    CIFSlotWithHelp *m_slot10;
    CIFSlotWithHelp *m_slot11;
    CIFFrame *statics;
    CIFFrame *statics2;
    CIFFrame *statics3;
    CIFFrame *statics4;
    CIFFrame *statics5;
    CIFFrame *statics6;
    CIFFrame *statics7;
    CIFFrame *statics8;
    CIFFrame *statics9;
    CIFFrame *statics10;
    CIFFrame *statics11;
    CIFFrame *statics12;
    CIFFrame *statics13;
    CIFFrame *statics14;
    CIFFrame *statics15;
    CIFFrame *statics16;
    CIFCheckBox *m_checkbox_hp;
    CIFCheckBox *m_checkbox_mp;
    CIFCheckBox *m_checkbox_vigor;
    CIFCheckBox *m_checkbox_abnormal;
    CIFCheckBox *m_checkbox_speedscroll;
    CIFCheckBox *m_checkbox_pet_hp;
    CIFCheckBox *m_checkbox_pet_hgp;
    CIFCheckBox *m_checkbox_pet_cure;
    CIFCheckBox *m_checkbox_pet_resurrect;
    CIFCheckBox *m_checkbox_pet_trigger;
    CIFCheckBox *m_checkbox_pet_trade;
    CIFCheckBox *m_checkbox_pet_ridding;
    CIFStatic* m_text_hp;
    CIFStatic* m_text_mp;
    CIFStatic* m_text_pet_hp;
    CIFStatic* m_text_pet_hgp;
    CIFStatic* m_text_pet_cure;
    CIFStatic* m_text_pet_resurrect;
    CIFStatic* m_text_pet_trigger;
    CIFStatic* m_text_vigor;
    CIFStatic* m_text_abnormal;
    CIFStatic* m_text_speedscroll;
    CIFStatic* m_text_percent_hp;
    CIFStatic* m_text_percent_mp;
    CIFStatic* m_text_pet_percent_hp;
    CIFStatic* m_text_pet_percent_hgp;
    CIFStatic* m_text_percent_vigor;
    CIFStatic* m_text_pet_hp_trade;
    CIFStatic* m_text_pet_hp_ridding;
    CIFStatic* m_text_pet_percent_hp_2;

    CIFSliderCtrl* m_Hp_Slider;
    CIFSliderCtrl* m_Mp_Slider;
    CIFSliderCtrl* m_Vigor_Slider;
    CIFSliderCtrl* m_Pet_HP_Slider;
    CIFSliderCtrl* m_Pet_HGP_Slider;
    CIFSliderCtrl* m_Pet_Trade_And_Ridding_HP_Slider;
    CIFStatic* m_edit_hp;
    CIFStatic* m_edit_mp;
    CIFStatic* m_edit_vigor;
    CIFStatic* m_edit_pet_hp;
    CIFStatic* m_edit_pet_hgp;
    CIFStatic* m_edit_pet_trade_and_ridding;

    CIFSTMacroAutoBuffSlotList* m_partymember_slot1;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot1;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot2;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot3;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot4;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot5;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot6;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot7;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot8;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot9;
    CIFSTMacroAutoBuffSkillSlotList* m_mySkill_slot10;

    CIFSTMacroAutoBuffedSkillSlotList* m_SkillBuffed_slot1;
    CIFSTMacroAutoBuffedSkillSlotList* m_SkillBuffed_slot2;

    CIFSpinControl* m_spin;
    unsigned __int16 HP_ID;
    unsigned __int16 MP_ID;
    unsigned __int16 VIGOR_ID;
    unsigned __int16 ABNORMAL_ID;
    unsigned __int16 SPEEDITEM_ID;
    unsigned __int16 PET_HP_ID;
    unsigned __int16 PET_HGP_ID;
    unsigned __int16 PET_CURE_ID;
    unsigned __int16 PET_RESURRECT_ID;
    unsigned __int16 PET_TRIGGER_ID;
    unsigned __int16 PET_HP_RIDDING_TRADE_ID;
    byte HP_SLOT;
    byte MP_SLOT;
    byte VIGOR_SLOT;
    byte ABNORMAL_SLOT;
    byte SPEED_SLOT;
    byte PET_HP_SLOT;
    byte PET_HGP_SLOT;
    byte PET_CURE_SLOT;
    byte PET_RESURRECT_SLOT;
    byte PET_TRIGGER_SLOT;
    byte PET_HP_RIDDING_TRADE_SLOT;
    CIFStatic* m_custom_label_tooltip3;
    std::n_wstring SelectedCharName;
    std::n_wstring SelectedSkillName;
    std::n_wstring SelectedSkillNameRemove;
    int SkillIDSlelected;
    static struct PartyMatchMember
    {
        int LineNum;
        int Race;
        std::wstring CharName;
        std::wstring LevelText;
        std::wstring Level;

    };
    static std::vector<PartyMatchMember> PartyMatchMemberList;

    static struct CharSkillData
    {
        int LineNum;
        int SkillID;
        std::wstring SkillNames;
    };
    static std::vector<CharSkillData> CharSkillDataList;
};



