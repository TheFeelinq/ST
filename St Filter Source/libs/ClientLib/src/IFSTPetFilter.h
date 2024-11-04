//
// Created by Admin on 14/11/2021.
//

#ifndef SRO_DEVKIT_IFSTPETFILTER_H
#define SRO_DEVKIT_IFSTPETFILTER_H
#include "BSLib/multibyte.h"
#include "BSLib/BSLib.h"
#include "IFMainFrame.h"
#include "IFSelectableArea.h"
#include "IFCheckBox.h"

class CIFSTPetFilter: public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSTPetFilter)
GFX_DECLARE_MESSAGE_MAP(CIFSTPetFilter)
public:
    CIFSTPetFilter(void);
    ~CIFSTPetFilter(void);
    int OnMouseMove(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
    void SwitchFilter();
    void Show(bool a);
    void ShowTab0(bool a);
    void ShowTab1(bool a);
    void ShowTab2(bool a);
    void ShowTab3(bool a);
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);
    static void Initialize();
    void loadconfig();

    bool IsEQDegree01Checked() const;
    bool IsEQDegree02Checked() const;
    bool IsEQDegree03Checked() const;
    bool IsEQDegree04Checked() const;
    bool IsEQDegree05Checked() const;
    bool IsEQDegree06Checked() const;
    bool IsEQDegree07Checked() const;
    bool IsEQDegree08Checked() const;
    bool IsEQDegree09Checked() const;
    bool IsEQDegree10Checked() const;
    bool IsEQDegree11Checked() const;
    bool IsEQDegree12Checked() const;
    bool IsEQDegree13Checked() const;
    bool IsEQDegree14Checked() const;
    bool IsEQDegree15Checked() const;

    bool IsALChemyDegree01Checked() const;
    bool IsALChemyDegree02Checked() const;
    bool IsALChemyDegree03Checked() const;
    bool IsALChemyDegree04Checked() const;
    bool IsALChemyDegree05Checked() const;
    bool IsALChemyDegree06Checked() const;
    bool IsALChemyDegree07Checked() const;
    bool IsALChemyDegree08Checked() const;
    bool IsALChemyDegree09Checked() const;
    bool IsALChemyDegree10Checked() const;
    bool IsALChemyDegree11Checked() const;
    bool IsALChemyDegree12Checked() const;
    bool IsALChemyDegree13Checked() const;
    bool IsALChemyDegree14Checked() const;
    bool IsALChemyDegree15Checked() const;

    bool IsEQWeaponChecked() const;
    bool IsEQHeavyChecked() const;
    bool IsEQLightChecked() const;
    bool IsEQClothesChecked() const;
    bool IsEQAccsessoryChecked() const;
    bool IsEQMaleChecked() const;
    bool IsEQFeMaleChecked() const;

    bool IsALChemyElixirWeaponChecked() const;
    bool IsALChemyElixirShieldChecked() const;
    bool IsALChemyElixirProtectorChecked() const;
    bool IsALChemyElixirAccessoryChecked() const;
    bool IsALChemyTabletBlueChecked() const;
    bool IsALChemyTabletRedChecked() const;
    bool IsALChemyStoneRedChecked() const;
    bool IsALChemyStoneBlueChecked() const;
    bool IsALChemyMaterialChecked() const;

    bool IsPotionHpChecked() const;
    bool IsPotionMpChecked() const;
    bool IsPotionVigorChecked() const;
    bool IsPotionVigorGrainChecked() const;
    bool IsPotionHpGrainChecked() const;
    bool IsPotionMpGrainChecked() const;
    bool IsPotionUniversalPillChecked() const;
    bool IsPotionReturnScrollChecked() const;
    bool IsPotionArrowsChecked() const;
    bool IsPotionBoltsChecked() const;
    bool IsPotionCoinChecked() const;
    bool IsGoldChecked() const;
public:
    static bool SwitchPetFilter;
    CIFButton *m_mybutton_switch;
    CIFStatic *m_lable_itemtype;
    CIFStatic *m_lable_tablets;
    CIFStatic *m_lable_stone;
    CIFStatic *m_lable_gender;
    CIFStatic *m_lable_itemtype_weapon;
    CIFStatic *m_lable_itemtype_accessory;
    CIFCheckBox *m_mybutton_itemtype_weapon;
    CIFCheckBox *m_mybutton_itemtype_accessory;
    CIFStatic *m_lable_tablet_blue;
    CIFStatic *m_lable_tablet_red;
    CIFStatic *m_lable_stone_blue;
    CIFStatic *m_lable_stone_red;
    CIFStatic *m_lable_itemtype_heavy;
    CIFStatic *m_lable_itemtype_light;
    CIFStatic *m_lable_itemtype_clothes;
    CIFCheckBox *m_mybutton_itemtype_heavy;
    CIFCheckBox *m_mybutton_itemtype_light;
    CIFCheckBox *m_mybutton_itemtype_clothes;

    CIFStatic *m_lable_itemtype_male;
    CIFStatic *m_lable_itemtype_female;
    CIFCheckBox *m_mybutton_itemtype_male;
    CIFCheckBox *m_mybutton_itemtype_female;

    CIFStatic *m_lable_degree;
    CIFStatic *m_lable_degree_01;
    CIFStatic *m_lable_degree_02;
    CIFStatic *m_lable_degree_03;
    CIFStatic *m_lable_degree_04;
    CIFStatic *m_lable_degree_05;
    CIFStatic *m_lable_degree_06;
    CIFStatic *m_lable_degree_07;
    CIFStatic *m_lable_degree_08;
    CIFStatic *m_lable_degree_09;
    CIFStatic *m_lable_degree_10;
    CIFStatic *m_lable_degree_11;
    CIFStatic *m_lable_degree_12;
    CIFStatic *m_lable_degree_13;
    CIFStatic *m_lable_degree_14;
    CIFStatic *m_lable_degree_15;

    CIFCheckBox *m_mybutton_degree01;
    CIFCheckBox *m_mybutton_degree02;
    CIFCheckBox *m_mybutton_degree03;
    CIFCheckBox *m_mybutton_degree04;
    CIFCheckBox *m_mybutton_degree05;
    CIFCheckBox *m_mybutton_degree06;
    CIFCheckBox *m_mybutton_degree07;
    CIFCheckBox *m_mybutton_degree08;
    CIFCheckBox *m_mybutton_degree09;
    CIFCheckBox *m_mybutton_degree10;
    CIFCheckBox *m_mybutton_degree11;
    CIFCheckBox *m_mybutton_degree12;
    CIFCheckBox *m_mybutton_degree13;
    CIFCheckBox *m_mybutton_degree14;
    CIFCheckBox *m_mybutton_degree15;

    CIFCheckBox *m_checkbox_degree01;
    CIFCheckBox *m_checkbox_degree02;
    CIFCheckBox *m_checkbox_degree03;
    CIFCheckBox *m_checkbox_degree04;
    CIFCheckBox *m_checkbox_degree05;
    CIFCheckBox *m_checkbox_degree06;
    CIFCheckBox *m_checkbox_degree07;
    CIFCheckBox *m_checkbox_degree08;
    CIFCheckBox *m_checkbox_degree09;
    CIFCheckBox *m_checkbox_degree10;
    CIFCheckBox *m_checkbox_degree11;
    CIFCheckBox *m_checkbox_degree12;
    CIFCheckBox *m_checkbox_degree13;
    CIFCheckBox *m_checkbox_degree14;
    CIFCheckBox *m_checkbox_degree15;

    CIFCheckBox *m_checkbox_elixir_weapon;
    CIFCheckBox *m_checkbox_elixir_shield;
    CIFCheckBox *m_checkbox_elixir_protector;
    CIFCheckBox *m_checkbox_elixir_accessory;
    CIFCheckBox *m_checkbox_tablet_blue;
    CIFCheckBox *m_checkbox_tablet_red;
    CIFCheckBox *m_checkbox_stone_blue;
    CIFCheckBox *m_checkbox_stone_red;
    CIFCheckBox *m_checkbox_materials;

    CIFCheckBox *m_checkbox_potion_hp;
    CIFCheckBox *m_checkbox_potion_mp;
    CIFCheckBox *m_checkbox_potion_vigor;
    CIFCheckBox *m_checkbox_grain_hp;
    CIFCheckBox *m_checkbox_grain_mp;
    CIFCheckBox *m_checkbox_grain_vigor;
    CIFCheckBox *m_checkbox_universal_pill;
    CIFCheckBox *m_checkbox_return_scroll;
    CIFCheckBox *m_checkbox_arrows;
    CIFCheckBox *m_checkbox_bolts;
    CIFCheckBox *m_checkbox_coin;

    CIFStatic *m_lable_potion_pill;
    CIFStatic *m_lable_expendables;

    CIFStatic *m_lable_potion_hp;
    CIFStatic *m_lable_potion_mp;
    CIFStatic *m_lable_potion_vigor;
    CIFStatic *m_lable_grain_hp;
    CIFStatic *m_lable_grain_mp;
    CIFStatic *m_lable_grain_vigor;
    CIFStatic *m_lable_universal_pill;
    CIFStatic *m_lable_return_scroll;
    CIFStatic *m_lable_arrows;
    CIFStatic *m_lable_bolts;
    CIFStatic *m_lable_coin;

    CIFCheckBox *m_checkbox_gold;
    CIFStatic *m_lable_gold;

    CIFFrame* Frame;
    CIFSelectableArea** m_pTabs;
    static const int numberOfTabs = 4;
    static const int tabWidth = 72;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 72;
    static const int tabFirstId = 300;

};


#endif //SRO_DEVKIT_IFSTPETFILTER_H
