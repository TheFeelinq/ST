//
// Created by Admin on 14/11/2021.
//

#include <Data/ItemData.h>
#include "IFSTPetFilter.h"
#include "memhelp.h"
#include "IFflorian0Guide.h"
#include "GlobalDataManager.h"
#include "Rebot.h"
#include "Game.h"

#define GDR_GXVSRO_FRAME 1
#define GDR_BTN_EQ_DEGREE_01 200
#define GDR_BTN_EQ_DEGREE_02 201
#define GDR_BTN_EQ_DEGREE_03 202
#define GDR_BTN_EQ_DEGREE_04 203
#define GDR_BTN_EQ_DEGREE_05 204
#define GDR_BTN_EQ_DEGREE_06 205
#define GDR_BTN_EQ_DEGREE_07 206
#define GDR_BTN_EQ_DEGREE_08 207
#define GDR_BTN_EQ_DEGREE_09 208
#define GDR_BTN_EQ_DEGREE_10 209
#define GDR_BTN_EQ_DEGREE_11 210
#define GDR_BTN_EQ_DEGREE_12 211
#define GDR_BTN_EQ_DEGREE_13 212
#define GDR_BTN_EQ_DEGREE_14 213
#define GDR_BTN_EQ_DEGREE_15 214
#define GDR_BTN_EQ_ITEMTYPE_WEAPON 215
#define GDR_BTN_EQ_ITEMTYPE_ACCESSORY 216
#define GDR_BTN_EQ_ITEMTYPE_HEAVY 217
#define GDR_BTN_EQ_ITEMTYPE_LIGHT 218
#define GDR_BTN_EQ_ITEMTYPE_CLOTHES 219
#define GDR_BTN_EQ_ITEMTYPE_MALE 220
#define GDR_BTN_EQ_ITEMTYPE_FEMALE 221
#define GDR_BTN_ALCHEMY_DEGREE_01 222
#define GDR_BTN_ALCHEMY_DEGREE_02 223
#define GDR_BTN_ALCHEMY_DEGREE_03 224
#define GDR_BTN_ALCHEMY_DEGREE_04 225
#define GDR_BTN_ALCHEMY_DEGREE_05 226
#define GDR_BTN_ALCHEMY_DEGREE_06 227
#define GDR_BTN_ALCHEMY_DEGREE_07 228
#define GDR_BTN_ALCHEMY_DEGREE_08 229
#define GDR_BTN_ALCHEMY_DEGREE_09 230
#define GDR_BTN_ALCHEMY_DEGREE_10 231
#define GDR_BTN_ALCHEMY_DEGREE_11 232
#define GDR_BTN_ALCHEMY_DEGREE_12 233
#define GDR_BTN_ALCHEMY_DEGREE_13 234
#define GDR_BTN_ALCHEMY_DEGREE_14 235
#define GDR_BTN_ALCHEMY_DEGREE_15 236

#define GDR_BTN_ALCHEMY_ELIXIR_WEAPON 237
#define GDR_BTN_ALCHEMY_ELIXIR_SHIELD 238
#define GDR_BTN_ALCHEMY_ELIXIR_PROTECTOR 239
#define GDR_BTN_ALCHEMY_ELIXIR_ACCESSORY 240
#define GDR_BTN_ALCHEMY_TABLET_BLUE 241
#define GDR_BTN_ALCHEMY_TABLET_RED 242
#define GDR_BTN_ALCHEMY_STONE_BLUE 243
#define GDR_BTN_ALCHEMY_STONE_RED 244
#define GDR_BTN_ALCHEMY_MATERIALS 245

#define GDR_BTN_POTION_HP 246
#define GDR_BTN_POTION_MP 247
#define GDR_BTN_POTION_VIGOR 248
#define GDR_BTN_GRAIN_HP 249
#define GDR_BTN_GRAIN_MP 250
#define GDR_BTN_GRAIN_VIGOR 251
#define GDR_BTN_UNIVERSAL_PILL 252
#define GDR_BTN_RETURN_SCROLL 253
#define GDR_BTN_ARROWS 254
#define GDR_BTN_BOTLS 255
#define GDR_BTN_COIN 256
#define GDR_BTN_GOLD 257
#define GDR_BTN_SWITCH 502
GFX_IMPLEMENT_DYNCREATE(CIFSTPetFilter, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFSTPetFilter, CIFMainFrame)
                    ONG_COMMAND(GDR_BTN_SWITCH, &SwitchFilter)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_01, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_02, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_03, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_04, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_05, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_06, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_07, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_08, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_09, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_10, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_11, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_12, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_13, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_14, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_DEGREE_15, &loadconfig)

                    ONG_COMMAND(GDR_BTN_POTION_HP, &loadconfig)
                    ONG_COMMAND(GDR_BTN_POTION_MP, &loadconfig)
                    ONG_COMMAND(GDR_BTN_POTION_VIGOR, &loadconfig)
                    ONG_COMMAND(GDR_BTN_GRAIN_HP, &loadconfig)
                    ONG_COMMAND(GDR_BTN_GRAIN_MP, &loadconfig)
                    ONG_COMMAND(GDR_BTN_GRAIN_VIGOR, &loadconfig)
                    ONG_COMMAND(GDR_BTN_UNIVERSAL_PILL, &loadconfig)
                    ONG_COMMAND(GDR_BTN_RETURN_SCROLL, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ARROWS, &loadconfig)
                    ONG_COMMAND(GDR_BTN_BOTLS, &loadconfig)
                    ONG_COMMAND(GDR_BTN_COIN, &loadconfig)
                    ONG_COMMAND(300, &CIFSTPetFilter::OnUnknownStuff)
                    ONG_COMMAND(301, &CIFSTPetFilter::OnUnknownStuff)
                    ONG_COMMAND(302, &CIFSTPetFilter::OnUnknownStuff)
                    ONG_COMMAND(303, &CIFSTPetFilter::OnUnknownStuff)

                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_WEAPON, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_ACCESSORY, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_HEAVY, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_LIGHT, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_CLOTHES, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_MALE, &loadconfig)
                    ONG_COMMAND(GDR_BTN_EQ_ITEMTYPE_FEMALE, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_01, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_02, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_03, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_04, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_05, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_06, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_07, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_08, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_09, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_10, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_11, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_12, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_13, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_14, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_DEGREE_15, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_ELIXIR_WEAPON, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_ELIXIR_SHIELD, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_ELIXIR_PROTECTOR, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_ELIXIR_ACCESSORY, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_TABLET_BLUE, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_TABLET_RED, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_STONE_BLUE, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_STONE_RED, &loadconfig)
                    ONG_COMMAND(GDR_BTN_ALCHEMY_MATERIALS, &loadconfig)
GFX_END_MESSAGE_MAP()


bool CIFSTPetFilter::SwitchPetFilter;
CIFSTPetFilter::CIFSTPetFilter(void)
{
    //  printf("> " __FUNCTION__ "\n");
}


CIFSTPetFilter::~CIFSTPetFilter(void)
{
    //  printf("> " __FUNCTION__ "\n");
}
int CIFSTPetFilter::OnMouseMove(int a1, int x, int y) {
    this->BringToFront();
    return 0;
}
bool CIFSTPetFilter::IsALChemyDegree01Checked() const {
    return m_checkbox_degree01->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsALChemyDegree02Checked() const {
    return m_checkbox_degree02->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree03Checked() const {
    return m_checkbox_degree03->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree04Checked() const {
    return m_checkbox_degree04->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree05Checked() const {
    return m_checkbox_degree05->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree06Checked() const {
    return m_checkbox_degree06->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree07Checked() const {
    return m_checkbox_degree07->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree08Checked() const {
    return m_checkbox_degree08->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree09Checked() const {
    return m_checkbox_degree09->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree10Checked() const {
    return m_checkbox_degree10->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree11Checked() const {
    return m_checkbox_degree11->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree12Checked() const {
    return m_checkbox_degree12->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree13Checked() const {
    return m_checkbox_degree13->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree14Checked() const {
    return m_checkbox_degree14->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyDegree15Checked() const {
    return m_checkbox_degree15->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree01Checked() const {
    return m_mybutton_degree01->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsEQDegree02Checked() const {
    return m_mybutton_degree02->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree03Checked() const {
    return m_mybutton_degree03->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree04Checked() const {
    return m_mybutton_degree04->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree05Checked() const {
    return m_mybutton_degree05->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree06Checked() const {
    return m_mybutton_degree06->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree07Checked() const {
    return m_mybutton_degree07->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree08Checked() const {
    return m_mybutton_degree08->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree09Checked() const {
    return m_mybutton_degree09->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree10Checked() const {
    return m_mybutton_degree10->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree11Checked() const {
    return m_mybutton_degree11->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree12Checked() const {
    return m_mybutton_degree12->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree13Checked() const {
    return m_mybutton_degree13->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree14Checked() const {
    return m_mybutton_degree14->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQDegree15Checked() const {
    return m_mybutton_degree15->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQWeaponChecked() const {
    return m_mybutton_itemtype_weapon->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsEQHeavyChecked() const {
    return m_mybutton_itemtype_heavy->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsEQLightChecked() const {
    return m_mybutton_itemtype_light->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsEQClothesChecked() const {
    return m_mybutton_itemtype_clothes->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQAccsessoryChecked() const {
    return m_mybutton_itemtype_accessory->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsEQMaleChecked() const {
    return m_mybutton_itemtype_male->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsEQFeMaleChecked() const {
    return m_mybutton_itemtype_female->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyElixirWeaponChecked() const {
    return m_checkbox_elixir_weapon->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyElixirShieldChecked() const {
    return m_checkbox_elixir_shield->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyElixirProtectorChecked() const {
    return m_checkbox_elixir_protector->GetCheckedState_MAYBE();
}

bool CIFSTPetFilter::IsALChemyElixirAccessoryChecked() const {
    return m_checkbox_elixir_accessory->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyTabletBlueChecked() const {
    return m_checkbox_tablet_blue->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyTabletRedChecked() const {
    return m_checkbox_tablet_red->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyStoneBlueChecked() const {
    return m_checkbox_stone_blue->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyStoneRedChecked() const {
    return m_checkbox_stone_red->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsALChemyMaterialChecked() const {
    return m_checkbox_materials->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionHpChecked() const {
    return m_checkbox_potion_hp->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionMpChecked() const {
    return m_checkbox_potion_mp->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionVigorChecked() const {
    return m_checkbox_potion_vigor->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionVigorGrainChecked() const {
    return m_checkbox_grain_vigor->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionHpGrainChecked() const {
    return m_checkbox_grain_hp->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionMpGrainChecked() const {
    return m_checkbox_grain_mp->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionUniversalPillChecked() const {
    return m_checkbox_universal_pill->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionReturnScrollChecked() const {
    return m_checkbox_return_scroll->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionArrowsChecked() const {
    return m_checkbox_arrows->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionBoltsChecked() const {
    return m_checkbox_bolts->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsPotionCoinChecked() const {
    return m_checkbox_coin->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::IsGoldChecked() const {
    return m_checkbox_gold->GetCheckedState_MAYBE();
}
bool CIFSTPetFilter::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);

    RECT rect_m_tile = {116, 9, 186, 13};
    CIFStatic * m_tile = (CIFStatic *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFStatic),rect_m_tile,111,1);
    m_tile->SetText(TSM_GETTEXTPTR("UIIS_CTL_PET_FILTER"));

    RECT Framerect = { 10,65,387,340 };
    Frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), Framerect, GDR_GXVSRO_FRAME, 0);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);

    //Frame->SetGWndSize(this->GetSize().width - 20, this->GetSize().height - 75);
    //Frame->MoveGWnd(this->GetPos().x + 10, this->GetPos().y + 65);
    RECT rect_background = {Framerect.left + 10,
                            Framerect.top + 10,
                            Framerect.right - 20,
                            Framerect.bottom - 20};

    CIFNormalTile *tile = (CIFNormalTile *) CreateInstance(this,
                                                           GFX_RUNTIME_CLASS(CIFNormalTile),
                                                           rect_background,
                                                           GDR_GXVSRO_FRAME,
                                                           1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_f.ddj", 1, 0);

    RECT Lable_degree_rect = { 36,80,75,18 };


    m_lable_degree = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_degree_rect, 101, 0);
    m_lable_degree->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_DEGREE"));
    m_lable_degree->TB_Func_5(0); //can le
    m_lable_degree->TB_Func_6(2); // co chu

    RECT Butt01rect = { 36,115,16,16 };
    RECT Lablerect_degree_01 = { Butt01rect.left + 18,Butt01rect.top,16,16 };
    m_lable_degree_01 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_01, 102, 0);
    m_lable_degree_01->SetText(L"01");
    m_mybutton_degree01 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt01rect, GDR_BTN_EQ_DEGREE_01, 0);
    m_checkbox_degree01 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt01rect, GDR_BTN_ALCHEMY_DEGREE_01, 0);

    RECT Butt02rect = { Butt01rect.left+40,115,16,16 };
    RECT Lablerect_degree_02 = { Butt02rect.left + 18,Butt02rect.top,16,16 };
    m_lable_degree_02 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_02, 112, 0);
    m_lable_degree_02->SetText(L"02");
    m_mybutton_degree02 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt02rect, GDR_BTN_EQ_DEGREE_02, 0);
    m_checkbox_degree02 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt02rect, GDR_BTN_ALCHEMY_DEGREE_02, 0);

    RECT Butt03rect = { Butt02rect.left+40,115,16,16 };
    RECT Lablerect_degree_03 = { Butt03rect.left + 18,Butt03rect.top,16,16 };
    m_lable_degree_03 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_03, 113, 0);
    m_lable_degree_03->SetText(L"03");
    m_mybutton_degree03 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt03rect, GDR_BTN_EQ_DEGREE_03, 0);
    m_checkbox_degree03 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt03rect, GDR_BTN_ALCHEMY_DEGREE_03, 0);

    RECT Butt04rect = { Butt03rect.left+40,115,16,16 };
    RECT Lablerect_degree_04 = { Butt04rect.left + 18,Butt04rect.top,16,16 };
    m_lable_degree_04 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_04, 114, 0);
    m_lable_degree_04->SetText(L"04");
    m_mybutton_degree04 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt04rect, GDR_BTN_EQ_DEGREE_04, 0);
    m_checkbox_degree04 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt04rect, GDR_BTN_ALCHEMY_DEGREE_04, 0);

    RECT Butt05rect = { Butt04rect.left+40,115,16,16 };
    RECT Lablerect_degree_05 = { Butt05rect.left + 18,Butt05rect.top,16,16 };
    m_lable_degree_05 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_05, 115, 0);
    m_lable_degree_05->SetText(L"05");
    m_mybutton_degree05 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt05rect, GDR_BTN_EQ_DEGREE_05, 0);
    m_checkbox_degree05 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt05rect, GDR_BTN_ALCHEMY_DEGREE_05, 0);

    RECT Butt06rect = { Butt05rect.left+40,115,16,16 };
    RECT Lablerect_degree_06 = { Butt06rect.left + 18,Butt06rect.top,16,16 };
    m_lable_degree_06 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_06, 116, 0);
    m_lable_degree_06->SetText(L"06");
    m_mybutton_degree06 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt06rect, GDR_BTN_EQ_DEGREE_06, 0);
    m_checkbox_degree06 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt06rect, GDR_BTN_ALCHEMY_DEGREE_06, 0);

    RECT Butt07rect = { Butt06rect.left+40,115,16,16 };
    RECT Lablerect_degree_07 = { Butt07rect.left + 18,Butt07rect.top,16,16 };
    m_lable_degree_07 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_07, 117, 0);
    m_lable_degree_07->SetText(L"07");
    m_mybutton_degree07 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt07rect, GDR_BTN_EQ_DEGREE_07, 0);
    m_checkbox_degree07 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt07rect, GDR_BTN_ALCHEMY_DEGREE_07, 0);

    RECT Butt08rect = { Butt07rect.left+40,115,16,16 };
    RECT Lablerect_degree_08 = { Butt08rect.left + 18,Butt08rect.top,16,16 };
    m_lable_degree_08 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_08, 118, 0);
    m_lable_degree_08->SetText(L"08");
    m_mybutton_degree08 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt08rect, GDR_BTN_EQ_DEGREE_08, 0);
    m_checkbox_degree08 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt08rect, GDR_BTN_ALCHEMY_DEGREE_08, 0);

    RECT Butt09rect = { 36,145,16,16 };
    RECT Lablerect_degree_09 = { Butt09rect.left + 18,Butt09rect.top,16,16 };
    m_lable_degree_09 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_09, 119, 0);
    m_lable_degree_09->SetText(L"09");
    m_mybutton_degree09 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt09rect, GDR_BTN_EQ_DEGREE_09, 0);
    m_checkbox_degree09 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt09rect, GDR_BTN_ALCHEMY_DEGREE_09, 0);

    RECT Butt10rect = { Butt01rect.left+40,145,16,16 };
    RECT Lablerect_degree_10 = { Butt10rect.left + 18,Butt10rect.top,16,16 };
    m_lable_degree_10 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_10, 120, 0);
    m_lable_degree_10->SetText(L"10");
    m_mybutton_degree10 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt10rect, GDR_BTN_EQ_DEGREE_10, 0);
    m_checkbox_degree10 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt10rect, GDR_BTN_ALCHEMY_DEGREE_10, 0);

    RECT Butt11rect = { Butt02rect.left+40,145,16,16 };
    RECT Lablerect_degree_11 = { Butt11rect.left + 18,Butt11rect.top,16,16 };
    m_lable_degree_11 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_11, 121, 0);
    m_lable_degree_11->SetText(L"11");
    m_mybutton_degree11 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt11rect, GDR_BTN_EQ_DEGREE_11, 0);
    m_checkbox_degree11 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt11rect, GDR_BTN_ALCHEMY_DEGREE_11, 0);

    RECT Butt12rect = { Butt03rect.left+40,145,16,16 };
    RECT Lablerect_degree_12 = { Butt12rect.left + 18,Butt12rect.top,16,16 };
    m_lable_degree_12 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_12, 122, 0);
    m_lable_degree_12->SetText(L"12");
    m_mybutton_degree12 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt12rect, GDR_BTN_EQ_DEGREE_12, 0);
    m_checkbox_degree12 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt12rect, GDR_BTN_ALCHEMY_DEGREE_12, 0);

    RECT Butt13rect = { Butt04rect.left+40,145,16,16 };
    RECT Lablerect_degree_13 = { Butt13rect.left + 18,Butt13rect.top,16,16 };
    m_lable_degree_13 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_13, 123, 0);
    m_lable_degree_13->SetText(L"13");
    m_mybutton_degree13 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt13rect, GDR_BTN_EQ_DEGREE_13, 0);
    m_checkbox_degree13 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt13rect, GDR_BTN_ALCHEMY_DEGREE_13, 0);

    RECT Butt14rect = { Butt05rect.left+40,145,16,16 };
    RECT Lablerect_degree_14 = { Butt14rect.left + 18,Butt14rect.top,16,16 };
    m_lable_degree_14 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_14, 124, 0);
    m_lable_degree_14->SetText(L"14");
    m_mybutton_degree14 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt14rect, GDR_BTN_EQ_DEGREE_14, 0);
    m_checkbox_degree14 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt14rect, GDR_BTN_ALCHEMY_DEGREE_14, 0);

    RECT Butt15rect = { Butt06rect.left+40,145,16,16 };
    RECT Lablerect_degree_15 = { Butt15rect.left + 18,Butt15rect.top,16,16 };
    m_lable_degree_15 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_degree_15, 125, 0);
    m_lable_degree_15->SetText(L"15");
    m_mybutton_degree15 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt15rect, GDR_BTN_EQ_DEGREE_15, 0);
    m_checkbox_degree15 = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt15rect, GDR_BTN_ALCHEMY_DEGREE_15, 0);

    RECT Lable_itemtype_rect = { 36,170,75,18 };
    m_lable_itemtype = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_itemtype_rect, 103, 0);
    m_lable_itemtype->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ITEMTYPE"));
    m_lable_itemtype->TB_Func_5(0); //can le
    m_lable_itemtype->TB_Func_6(2); // co chu
    RECT Lable_tablets_rect = { Lable_itemtype_rect.left+200,170,75,18 };
    m_lable_tablets = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_tablets_rect, 400, 0);
    m_lable_tablets->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_TABLET"));
    m_lable_tablets->TB_Func_5(0); //can le
    m_lable_tablets->TB_Func_6(2); // co chu
    RECT Lable_stone_rect = { Lable_itemtype_rect.left+200,250,75,18 };
    m_lable_stone = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_stone_rect, 403, 0);
    m_lable_stone->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_STONE"));
    m_lable_stone->TB_Func_5(0); //can le
    m_lable_stone->TB_Func_6(2); // co chu

    RECT Butt_stone_blue_rect = { 236,280,16,16 };
    RECT Butt_stone_red_rect = { 236,300,16,16 };
    RECT lable_stone_blue_rect = { Butt_stone_blue_rect.left + 25,Butt_stone_blue_rect.top,16,16 };
    RECT lable_stone_red_rect = { Butt_stone_red_rect.left + 25,Butt_stone_red_rect.top,16,16 };
    m_lable_stone_blue = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable_stone_blue_rect, 404, 0);
    m_lable_stone_blue->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_BLUE_STONE"));
    m_lable_stone_blue->TB_Func_5(0); //can le
    m_lable_stone_red = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), lable_stone_red_rect, 405, 0);
    m_lable_stone_red->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_RED_STONE"));
    m_lable_stone_red->TB_Func_5(0); //can le
    m_checkbox_stone_blue = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_stone_blue_rect, GDR_BTN_ALCHEMY_STONE_BLUE, 0);
    m_checkbox_stone_red = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_stone_red_rect, GDR_BTN_ALCHEMY_STONE_RED, 0);

    RECT Butt_itemtype_weapon_rect = { 36,205,16,16 };
    RECT Butt_tablets_blue_rect = { Butt_itemtype_weapon_rect.left + 200,205,16,16 };
    RECT Lablerect_weapon = { Butt_itemtype_weapon_rect.left + 25,Butt_itemtype_weapon_rect.top,16,16 };
    RECT Lablerect_tabletblue = { Butt_tablets_blue_rect.left + 25,Butt_itemtype_weapon_rect.top,16,16 };
    m_lable_itemtype_weapon = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_weapon, 104, 0);
    m_lable_itemtype_weapon->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_WEAPON"));
    m_lable_itemtype_weapon->TB_Func_5(0); //can le
    m_lable_tablet_blue = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_tabletblue, 401, 0);
    m_lable_tablet_blue->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_BLUE_TABLET"));
    m_lable_tablet_blue->TB_Func_5(0); //can le
    m_mybutton_itemtype_weapon = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_weapon_rect, GDR_BTN_EQ_ITEMTYPE_WEAPON, 0);
    m_checkbox_elixir_weapon = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_weapon_rect, GDR_BTN_ALCHEMY_ELIXIR_WEAPON, 0);
    m_checkbox_tablet_blue = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_tablets_blue_rect, GDR_BTN_ALCHEMY_TABLET_BLUE, 0);
    //m_mybutton_itemtype_weapon ->TB_Func_13("interface\\ifcommon\\thaidu0ngpr0\\checkbutton_off.ddj", 0, 0);


    RECT Butt_itemtype_accessory_rect = { 36,225,16,16 };
    RECT Butt_tablets_red_rect = { Butt_itemtype_accessory_rect.left + 200,225,16,16 };
    RECT Lablerect_accessory = { Butt_itemtype_accessory_rect.left + 25,Butt_itemtype_accessory_rect.top,16,16 };
    RECT Lablerect_tabletred = { Butt_tablets_red_rect.left + 25,Butt_itemtype_accessory_rect.top,16,16 };
    m_lable_itemtype_accessory = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_accessory, 105, 0);
    m_lable_itemtype_accessory->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ACCESSORY"));
    m_lable_itemtype_accessory->TB_Func_5(0); //can le
    m_lable_tablet_red = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_tabletred, 402, 0);
    m_lable_tablet_red->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_RED_TABLET"));
    m_lable_tablet_red->TB_Func_5(0); //can le

    m_mybutton_itemtype_accessory = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_accessory_rect, GDR_BTN_EQ_ITEMTYPE_ACCESSORY, 0);
    m_checkbox_elixir_shield = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_accessory_rect, GDR_BTN_ALCHEMY_ELIXIR_SHIELD, 0);
    m_checkbox_tablet_red = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_tablets_red_rect, GDR_BTN_ALCHEMY_TABLET_RED, 0);

    RECT Butt_itemtype_heavy_rect = { 36,245,16,16 };
    RECT Lablerect_heavy = { Butt_itemtype_heavy_rect.left + 25,Butt_itemtype_heavy_rect.top,16,16 };
    m_lable_itemtype_heavy = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_heavy, 106, 0);
    m_lable_itemtype_heavy->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_HEAVY"));
    m_lable_itemtype_heavy->TB_Func_5(0); //can le
    m_mybutton_itemtype_heavy = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_heavy_rect, GDR_BTN_EQ_ITEMTYPE_HEAVY, 0);
    m_checkbox_elixir_protector = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_heavy_rect, GDR_BTN_ALCHEMY_ELIXIR_PROTECTOR, 0);

    RECT Butt_itemtype_light_rect = { 36,265,16,16 };
    RECT Lablerect_light = { Butt_itemtype_light_rect.left + 25,Butt_itemtype_light_rect.top,16,16 };
    m_lable_itemtype_light = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_light, 107, 0);
    m_lable_itemtype_light->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_LIGHT"));
    m_lable_itemtype_light->TB_Func_5(0); //can le
    m_mybutton_itemtype_light = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_light_rect, GDR_BTN_EQ_ITEMTYPE_LIGHT, 0);
    m_checkbox_elixir_accessory = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_light_rect, GDR_BTN_ALCHEMY_ELIXIR_ACCESSORY, 0);


    RECT Butt_itemtype_clothes_rect = { 36,285,16,16 };
    RECT Lablerect_clothes = { Butt_itemtype_clothes_rect.left + 25,Butt_itemtype_clothes_rect.top,16,16 };
    m_lable_itemtype_clothes = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_clothes, 108, 0);
    m_lable_itemtype_clothes->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_CLOTHES"));
    m_lable_itemtype_clothes->TB_Func_5(0); //can le
    m_mybutton_itemtype_clothes = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_clothes_rect, GDR_BTN_EQ_ITEMTYPE_CLOTHES, 0);

    RECT Butt_itemtype_gender_rect = { 36,310,16,16 };
    m_lable_gender = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt_itemtype_gender_rect, 109, 0);
    m_lable_gender->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GENDER"));
    m_lable_gender->TB_Func_5(0); //can le
    m_lable_gender->TB_Func_6(2); // co chu

    RECT Butt_itemtype_male_rect = { 36,340,16,16 };
    RECT Lablerect_male = { Butt_itemtype_male_rect.left + 25,Butt_itemtype_male_rect.top,16,16 };
    m_lable_itemtype_male = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_male, 110, 0);
    m_lable_itemtype_male->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GENDER_M"));
    m_lable_itemtype_male->TB_Func_5(0); //can le
    m_mybutton_itemtype_male = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_male_rect, GDR_BTN_EQ_ITEMTYPE_MALE, 0);
    m_checkbox_materials = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_male_rect, GDR_BTN_ALCHEMY_MATERIALS, 0);

    RECT Butt_itemtype_female_rect = { 110,340,16,16 };
    RECT Lablerect_female = { Butt_itemtype_female_rect.left + 25,Butt_itemtype_female_rect.top,16,16 };
    m_lable_itemtype_female = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_female, 111, 0);
    m_lable_itemtype_female->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GENDER_F"));
    m_lable_itemtype_female->TB_Func_5(0); //can le
    m_mybutton_itemtype_female = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), Butt_itemtype_female_rect, GDR_BTN_EQ_ITEMTYPE_FEMALE, 0);


    RECT Butt_switch_rect = { 269,344,80,24 };
    m_mybutton_switch = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt_switch_rect, GDR_BTN_SWITCH, 0);
    m_mybutton_switch->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_OFF"));
    m_mybutton_switch->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    RECT Lable_potion_pill_rect = { 36,80,75,18 };
    m_lable_potion_pill = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_potion_pill_rect, 406, 0);
    m_lable_potion_pill->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_PILL_POTION"));
    m_lable_potion_pill->TB_Func_5(0); //can le
    m_lable_potion_pill->TB_Func_6(2); // co chu
    RECT Lable_expendables_rect = { Lable_potion_pill_rect.left+200,80,75,18 };
    m_lable_expendables = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lable_expendables_rect, 407, 0);
    m_lable_expendables->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_EXPENDABLES"));
    m_lable_expendables->TB_Func_5(0); //can le
    m_lable_expendables->TB_Func_6(2); // co chu

    RECT potion_hp_rect = { 36,115,16,16 };
    RECT Lablerect_potion_hp = { potion_hp_rect.left + 18,potion_hp_rect.top,16,16 };
    m_lable_potion_hp = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_potion_hp, 408, 0);
    m_lable_potion_hp->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_HP_POTION"));
    m_lable_potion_hp->TB_Func_5(0); //can le
    m_checkbox_potion_hp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), potion_hp_rect, GDR_BTN_POTION_HP, 0);
    RECT potion_mp_rect = { 36,135,16,16 };
    RECT Lablerect_potion_mp = { potion_mp_rect.left + 18,potion_mp_rect.top,16,16 };
    m_lable_potion_mp = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_potion_mp, 409, 0);
    m_lable_potion_mp->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_MP_POTION"));
    m_lable_potion_mp->TB_Func_5(0); //can le
    m_checkbox_potion_mp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), potion_mp_rect, GDR_BTN_POTION_MP, 0);
    RECT potion_vigor_rect = { 36,155,16,16 };
    RECT Lablerect_potion_vigor = { potion_vigor_rect.left + 18,potion_vigor_rect.top,16,16 };
    m_lable_potion_vigor = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_potion_vigor, 410, 0);
    m_lable_potion_vigor->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_VIGOR_POTION"));
    m_lable_potion_vigor->TB_Func_5(0); //can le
    m_checkbox_potion_vigor = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), potion_vigor_rect, GDR_BTN_POTION_VIGOR, 0);
    RECT grain_hp_rect = { 36,175,16,16 };
    RECT Lablerect_grain_hp = { grain_hp_rect.left + 18,grain_hp_rect.top,16,16 };
    m_lable_grain_hp = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_grain_hp, 411, 0);
    m_lable_grain_hp->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_HP_GRAINS"));
    m_lable_grain_hp->TB_Func_5(0); //can le
    m_checkbox_grain_hp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), grain_hp_rect, GDR_BTN_GRAIN_HP, 0);
    RECT grain_mp_rect = { 36,195,16,16 };
    RECT Lablerect_grain_mp = { grain_mp_rect.left + 18,grain_mp_rect.top,16,16 };
    m_lable_grain_mp = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_grain_mp, 411, 0);
    m_lable_grain_mp->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_MP_GRAINS"));
    m_lable_grain_mp->TB_Func_5(0); //can le
    m_checkbox_grain_mp = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), grain_mp_rect, GDR_BTN_GRAIN_MP, 0);
    RECT grain_vigor_rect = { 36,215,16,16 };
    RECT Lablerect_grain_vigor = { grain_vigor_rect.left + 18,grain_vigor_rect.top,16,16 };
    m_lable_grain_vigor = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_grain_vigor, 412, 0);
    m_lable_grain_vigor->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_VIGOR_GRAINS"));
    m_lable_grain_vigor->TB_Func_5(0); //can le
    m_checkbox_grain_vigor = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), grain_vigor_rect, GDR_BTN_GRAIN_VIGOR, 0);
    m_pTabs = new CIFSelectableArea * [numberOfTabs];
    RECT universal_pill_rect = { 36,235,16,16 };
    RECT Lablerect_universal_pill = { universal_pill_rect.left + 18,universal_pill_rect.top,16,16 };
    m_lable_universal_pill = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_universal_pill, 413, 0);
    m_lable_universal_pill->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_UNIVERSAL_PILLS"));
    m_lable_universal_pill->TB_Func_5(0); //can le
    m_checkbox_universal_pill = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), universal_pill_rect, GDR_BTN_UNIVERSAL_PILL, 0);

    RECT return_scroll_rect = { potion_hp_rect.left+200,potion_hp_rect.top,16,16 };
    RECT Lablerect_return_scroll = { return_scroll_rect.left + 18,return_scroll_rect.top,16,16 };
    m_lable_return_scroll = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_return_scroll, 414, 0);
    m_lable_return_scroll->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_RETURN_SCROLL"));
    m_lable_return_scroll->TB_Func_5(0); //can le
    m_checkbox_return_scroll = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), return_scroll_rect, GDR_BTN_RETURN_SCROLL, 0);

    RECT arrows_rect = { return_scroll_rect.left,return_scroll_rect.top+20,16,16 };
    RECT Lablerect_arrows = { arrows_rect.left + 18,arrows_rect.top,16,16 };
    m_lable_arrows = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_arrows, 415, 0);
    m_lable_arrows->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ARROWS"));
    m_lable_arrows->TB_Func_5(0); //can le
    m_checkbox_arrows = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), arrows_rect, GDR_BTN_ARROWS, 0);

    RECT bolts_rect = { arrows_rect.left,arrows_rect.top+20,16,16 };
    RECT Lablerect_bolts = { bolts_rect.left + 18,bolts_rect.top,16,16 };
    m_lable_bolts = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_bolts, 416, 0);
    m_lable_bolts->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_BOTLS"));
    m_lable_bolts->TB_Func_5(0); //can le
    m_checkbox_bolts = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), bolts_rect, GDR_BTN_BOTLS, 0);

    RECT coin_rect = { bolts_rect.left,bolts_rect.top+20,16,16 };
    RECT Lablerect_coin = { coin_rect.left + 18,coin_rect.top,16,16 };
    m_lable_coin = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_coin, 417, 0);
    m_lable_coin->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_COIN"));
    m_lable_coin->TB_Func_5(0); //can le
    m_checkbox_coin = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), coin_rect, GDR_BTN_COIN, 0);

    RECT gold_rect = { 36,115,16,16 };
    RECT Lablerect_gold = { gold_rect.left + 18,gold_rect.top,16,16 };
    m_lable_gold = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Lablerect_gold, 417, 0);
    m_lable_gold->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GOLD"));
    m_lable_gold->TB_Func_5(0); //can le
    m_checkbox_gold = (CIFCheckBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), gold_rect, GDR_BTN_GOLD, 0);

    m_pTabs = new CIFSelectableArea * [numberOfTabs];
    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 0;
        selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
                                                               selectable_area_size, tabFirstId + i, 0);
        m_pTabs[i]->SetFont(this->N00009C2F);

        m_pTabs[i]->sub_64CE30("interface\\ifcommon\\com_tab_on.ddj",
                               "interface\\ifcommon\\com_tab_off.ddj", "interface\\ifcommon\\com_tab_disable.ddj");

        switch (i) {
            case 0:
                m_pTabs[0]->MoveGWnd(Frame->GetPos().x + 10, GetPos().y + 41);
                m_pTabs[0]->sub_64CC30(1);
                break;
            case 1:
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[1]->sub_64CC30(0);
                break;
            case 2:
                m_pTabs[2]->MoveGWnd(m_pTabs[1]->GetPos().x + m_pTabs[1]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[2]->sub_64CC30(0);
                break;
            case 3:
                m_pTabs[3]->MoveGWnd(m_pTabs[2]->GetPos().x + m_pTabs[2]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[3]->sub_64CC30(0);
                break;

        }
    }

    m_pTabs[0]->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_EQUIPMENT"));//--
    m_pTabs[1]->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ALCHEMY"));
    m_pTabs[2]->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_OTHERS"));//--
    m_pTabs[3]->SetText(L"Gold");//--
    ActivateTabPage(0);
    ResetPosition();
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    char buffer[0x200];
    sprintf_s(buffer, "%s\\Setting\\chops.dat", theApp.GetWorkingDir());

    FILE *file = fopen(buffer, "rb+");
    if (file == NULL) {
        m_mybutton_itemtype_weapon->FUN_00656d50(false);
        return true;
    }

    char config[58];
    fread_s(&config[0], sizeof(config), 1, 58, file);

    m_mybutton_degree01->FUN_00656d50(config[0] != 0);
    m_mybutton_degree02->FUN_00656d50(config[1] != 0);
    m_mybutton_degree03->FUN_00656d50(config[2] != 0);
    m_mybutton_degree04->FUN_00656d50(config[3] != 0);
    m_mybutton_degree05->FUN_00656d50(config[4] != 0);
    m_mybutton_degree06->FUN_00656d50(config[5] != 0);
    m_mybutton_degree07->FUN_00656d50(config[6] != 0);
    m_mybutton_degree08->FUN_00656d50(config[7] != 0);
    m_mybutton_degree09->FUN_00656d50(config[8] != 0);
    m_mybutton_degree10->FUN_00656d50(config[9] != 0);
    m_mybutton_degree11->FUN_00656d50(config[10] != 0);
    m_mybutton_degree12->FUN_00656d50(config[11] != 0);
    m_mybutton_degree13->FUN_00656d50(config[12] != 0);
    m_mybutton_degree14->FUN_00656d50(config[13] != 0);
    m_mybutton_degree15->FUN_00656d50(config[14] != 0);
    m_mybutton_itemtype_weapon->FUN_00656d50(config[15] != 0);
    m_mybutton_itemtype_accessory->FUN_00656d50(config[16] != 0);
    m_mybutton_itemtype_heavy->FUN_00656d50(config[17] != 0);
    m_mybutton_itemtype_light->FUN_00656d50(config[18] != 0);
    m_mybutton_itemtype_clothes->FUN_00656d50(config[19] != 0);
    m_mybutton_itemtype_male->FUN_00656d50(config[20] != 0);
    m_mybutton_itemtype_female->FUN_00656d50(config[21] != 0);

    m_checkbox_degree01->FUN_00656d50(config[22] != 0);
    m_checkbox_degree02->FUN_00656d50(config[23] != 0);
    m_checkbox_degree03->FUN_00656d50(config[24] != 0);
    m_checkbox_degree04->FUN_00656d50(config[25] != 0);
    m_checkbox_degree05->FUN_00656d50(config[26] != 0);
    m_checkbox_degree06->FUN_00656d50(config[27] != 0);
    m_checkbox_degree07->FUN_00656d50(config[28] != 0);
    m_checkbox_degree08->FUN_00656d50(config[29] != 0);
    m_checkbox_degree09->FUN_00656d50(config[30] != 0);
    m_checkbox_degree10->FUN_00656d50(config[31] != 0);
    m_checkbox_degree11->FUN_00656d50(config[32] != 0);
    m_checkbox_degree12->FUN_00656d50(config[33] != 0);
    m_checkbox_degree13->FUN_00656d50(config[34] != 0);
    m_checkbox_degree14->FUN_00656d50(config[35] != 0);
    m_checkbox_degree15->FUN_00656d50(config[36] != 0);
    m_checkbox_elixir_weapon->FUN_00656d50(config[37] != 0);
    m_checkbox_elixir_shield->FUN_00656d50(config[38] != 0);
    m_checkbox_elixir_protector->FUN_00656d50(config[39] != 0);
    m_checkbox_elixir_accessory->FUN_00656d50(config[40] != 0);
    m_checkbox_tablet_blue->FUN_00656d50(config[41] != 0);
    m_checkbox_tablet_red->FUN_00656d50(config[42] != 0);
    m_checkbox_stone_blue->FUN_00656d50(config[43] != 0);
    m_checkbox_stone_red->FUN_00656d50(config[44] != 0);
    m_checkbox_materials->FUN_00656d50(config[45] != 0);

    m_checkbox_potion_hp->FUN_00656d50(config[46] != 0);
    m_checkbox_potion_mp->FUN_00656d50(config[47] != 0);
    m_checkbox_potion_vigor->FUN_00656d50(config[48] != 0);
    m_checkbox_grain_hp->FUN_00656d50(config[49] != 0);
    m_checkbox_grain_mp->FUN_00656d50(config[50] != 0);
    m_checkbox_grain_vigor->FUN_00656d50(config[51] != 0);
    m_checkbox_universal_pill->FUN_00656d50(config[52] != 0);
    m_checkbox_return_scroll->FUN_00656d50(config[53] != 0);
    m_checkbox_arrows->FUN_00656d50(config[54] != 0);
    m_checkbox_bolts->FUN_00656d50(config[55] != 0);
    m_checkbox_coin->FUN_00656d50(config[56] != 0);
    m_checkbox_gold->FUN_00656d50(config[57] != 0);
    fclose(file);

    SwitchPetFilter= false;
    this->ShowGWnd(false);



    return true;
}
void CIFSTPetFilter::ResetPosition()
{
    USHORT PosX = 0, PosY = 165;
    PosX = CLIENT_SCREEN_WIDTH - 750;
    this->MoveGWnd(PosX, PosY);
}
void CIFSTPetFilter::SwitchFilter()
{
   if(SwitchPetFilter)
   {
       m_mybutton_switch->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_OFF"));
       SwitchPetFilter=false;
   }
   else
    {
        m_mybutton_switch->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ON"));
        SwitchPetFilter=true;
    }
}
void CIFSTPetFilter::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}
void CIFSTPetFilter::OnUpdate() {

    if(g_pCICPlayer)
    {

        CIFWnd *CIFCOS = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(120, 1);
        if(CIFCOS && CIFCOS->IsVisible())
        {

        }
        else{
            g_pCGInterface->GetPetFilterGUI()->ShowGWnd(false);
        }

    }
}
void CIFSTPetFilter::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);

    switch (page) {
        case 0:
            this-> m_lable_itemtype->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ITEMTYPE"));
            this-> m_lable_gender->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GENDER"));
            this-> m_lable_itemtype_weapon->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_WEAPON"));
            this-> m_lable_itemtype_accessory->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ACCESSORY"));
            this-> m_lable_itemtype_heavy->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_HEAVY"));
            this-> m_lable_itemtype_light->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_LIGHT"));
            this-> m_lable_itemtype_male->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_GENDER_M"));
            Show(true);
            ShowTab1(false);
            ShowTab2(false);
            ShowTab0(true);
            ShowTab3(false);
            break;
        case 1:
            this-> m_lable_itemtype->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_ELIXIR"));
            this-> m_lable_gender->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_MATERIAL"));
            this-> m_lable_itemtype_weapon->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_WEAPON"));
            this-> m_lable_itemtype_accessory->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_SHIELD"));
            this-> m_lable_itemtype_heavy->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_PROTECTOR"));
            this-> m_lable_itemtype_light->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_ACCESSORY"));
            this-> m_lable_itemtype_male->SetText(TSM_GETTEXTPTR("UIIT_CTL_PET_FILTER_AL_MATERIAL"));
            Show(true);
            ShowTab0(false);
            ShowTab2(false);
            ShowTab1(true);
            ShowTab3(false);
            break;
        case 2:
            ShowTab0(false);
            ShowTab1(false);
            Show(false);
            ShowTab2(true);
            ShowTab3(false);
            break;
        case 3:
            ShowTab0(false);
            ShowTab1(false);
            ShowTab2(false);
            Show(false);
            ShowTab3(true);
            break;
    }

}
void CIFSTPetFilter::ShowTab2(bool a)
{

    m_checkbox_potion_hp->ShowGWnd(a);
    m_checkbox_potion_mp->ShowGWnd(a);
    m_checkbox_potion_vigor->ShowGWnd(a);
    m_checkbox_grain_hp->ShowGWnd(a);
    m_checkbox_grain_mp->ShowGWnd(a);
    m_checkbox_grain_vigor->ShowGWnd(a);
    m_checkbox_universal_pill->ShowGWnd(a);
    m_checkbox_return_scroll->ShowGWnd(a);
    m_checkbox_arrows->ShowGWnd(a);
    m_checkbox_bolts->ShowGWnd(a);
    m_checkbox_coin->ShowGWnd(a);
    m_lable_potion_pill->ShowGWnd(a);
    m_lable_expendables->ShowGWnd(a);
    m_lable_potion_hp->ShowGWnd(a);
    m_lable_potion_mp->ShowGWnd(a);
    m_lable_potion_vigor->ShowGWnd(a);
    m_lable_grain_hp->ShowGWnd(a);
    m_lable_grain_mp->ShowGWnd(a);
    m_lable_grain_vigor->ShowGWnd(a);
    m_lable_universal_pill->ShowGWnd(a);
    m_lable_return_scroll->ShowGWnd(a);
    m_lable_arrows->ShowGWnd(a);
    m_lable_bolts->ShowGWnd(a);
    m_lable_coin->ShowGWnd(a);

}
void CIFSTPetFilter::ShowTab3(bool a)
{
    m_checkbox_gold->ShowGWnd(a);
    m_lable_gold->ShowGWnd(a);
}

void CIFSTPetFilter::Show(bool a)
{

    m_lable_itemtype->ShowGWnd(a);
    m_lable_tablets->ShowGWnd(a);
    m_lable_stone->ShowGWnd(a);
    m_lable_gender->ShowGWnd(a);
    m_lable_itemtype_weapon->ShowGWnd(a);
    m_lable_itemtype_accessory->ShowGWnd(a);
    m_mybutton_itemtype_weapon->ShowGWnd(a);
    m_mybutton_itemtype_accessory->ShowGWnd(a);
    m_lable_tablet_blue->ShowGWnd(a);
    m_lable_tablet_red->ShowGWnd(a);
    m_lable_stone_blue->ShowGWnd(a);
    m_lable_stone_red->ShowGWnd(a);
    m_lable_itemtype_heavy->ShowGWnd(a);
    m_lable_itemtype_light->ShowGWnd(a);
    m_lable_itemtype_clothes->ShowGWnd(a);
    m_mybutton_itemtype_heavy->ShowGWnd(a);
    m_mybutton_itemtype_light->ShowGWnd(a);
    m_mybutton_itemtype_clothes->ShowGWnd(a);
    m_lable_itemtype_male->ShowGWnd(a);
    m_lable_itemtype_female->ShowGWnd(a);
    m_mybutton_itemtype_male->ShowGWnd(a);
    m_mybutton_itemtype_female->ShowGWnd(a);
    m_lable_degree->ShowGWnd(a);
    m_lable_degree_01->ShowGWnd(a);
    m_lable_degree_02->ShowGWnd(a);
    m_lable_degree_03->ShowGWnd(a);
    m_lable_degree_04->ShowGWnd(a);
    m_lable_degree_05->ShowGWnd(a);
    m_lable_degree_06->ShowGWnd(a);
    m_lable_degree_07->ShowGWnd(a);
    m_lable_degree_08->ShowGWnd(a);
    m_lable_degree_09->ShowGWnd(a);
    m_lable_degree_10->ShowGWnd(a);
    m_lable_degree_11->ShowGWnd(a);
    m_lable_degree_12->ShowGWnd(a);
    m_lable_degree_13->ShowGWnd(a);
    m_lable_degree_14->ShowGWnd(a);
    m_lable_degree_15->ShowGWnd(a);

}

void CIFSTPetFilter::ShowTab0(bool a) {
    this->m_mybutton_degree01->ShowGWnd(a);
    this->m_mybutton_degree02->ShowGWnd(a);
    this->m_mybutton_degree03->ShowGWnd(a);
    this-> m_mybutton_degree04->ShowGWnd(a);
    this->m_mybutton_degree05->ShowGWnd(a);
    this-> m_mybutton_degree06->ShowGWnd(a);
    this-> m_mybutton_degree07->ShowGWnd(a);
    this-> m_mybutton_degree08->ShowGWnd(a);
    this->m_mybutton_degree09->ShowGWnd(a);
    this->m_mybutton_degree10->ShowGWnd(a);
    this-> m_mybutton_degree11->ShowGWnd(a);
    this-> m_mybutton_degree12->ShowGWnd(a);
    this-> m_mybutton_degree13->ShowGWnd(a);
    this-> m_mybutton_degree14->ShowGWnd(a);
    this->  m_mybutton_degree15->ShowGWnd(a);
    this-> m_lable_itemtype->ShowGWnd(a);
    this-> m_lable_gender->ShowGWnd(a);
    this-> m_lable_itemtype_weapon->ShowGWnd(a);
    this-> m_lable_itemtype_accessory->ShowGWnd(a);
    this-> m_mybutton_itemtype_weapon->ShowGWnd(a);
    this-> m_mybutton_itemtype_accessory->ShowGWnd(a);

    this-> m_lable_itemtype_heavy->ShowGWnd(a);
    this-> m_lable_itemtype_light->ShowGWnd(a);
    this-> m_lable_itemtype_clothes->ShowGWnd(a);
    this-> m_mybutton_itemtype_heavy->ShowGWnd(a);
    this-> m_mybutton_itemtype_light->ShowGWnd(a);
    this-> m_mybutton_itemtype_clothes->ShowGWnd(a);

    this-> m_lable_itemtype_male->ShowGWnd(a);
    this-> m_lable_itemtype_female->ShowGWnd(a);
    this-> m_mybutton_itemtype_male->ShowGWnd(a);
    this-> m_mybutton_itemtype_female->ShowGWnd(a);
}
void CIFSTPetFilter::ShowTab1(bool a) {
    this->m_checkbox_degree01->ShowGWnd(a);
    this->m_checkbox_degree02->ShowGWnd(a);
    this->m_checkbox_degree03->ShowGWnd(a);
    this-> m_checkbox_degree04->ShowGWnd(a);
    this->m_checkbox_degree05->ShowGWnd(a);
    this-> m_checkbox_degree06->ShowGWnd(a);
    this-> m_checkbox_degree07->ShowGWnd(a);
    this-> m_checkbox_degree08->ShowGWnd(a);
    this->m_checkbox_degree09->ShowGWnd(a);
    this->m_checkbox_degree10->ShowGWnd(a);
    this-> m_checkbox_degree11->ShowGWnd(a);
    this-> m_checkbox_degree12->ShowGWnd(a);
    this-> m_checkbox_degree13->ShowGWnd(a);
    this-> m_checkbox_degree14->ShowGWnd(a);
    this->  m_checkbox_degree15->ShowGWnd(a);
    this->m_checkbox_elixir_weapon->ShowGWnd(a);
    this->m_checkbox_elixir_shield->ShowGWnd(a);
    this->m_checkbox_elixir_protector->ShowGWnd(a);
    this->m_checkbox_elixir_accessory->ShowGWnd(a);
    this->m_checkbox_tablet_blue->ShowGWnd(a);
    this->m_checkbox_tablet_red->ShowGWnd(a);
    this->m_checkbox_stone_blue->ShowGWnd(a);
    this->m_checkbox_stone_red->ShowGWnd(a);
    this->m_checkbox_materials->ShowGWnd(a);
    this->m_lable_tablets->ShowGWnd(a);
    this->m_lable_tablet_blue->ShowGWnd(a);
    this->m_lable_tablet_red->ShowGWnd(a);
    this->m_lable_stone->ShowGWnd(a);
    this->m_lable_stone_blue->ShowGWnd(a);
    this->m_lable_stone_red->ShowGWnd(a);

    this-> m_lable_itemtype->ShowGWnd(a);
    this-> m_lable_gender->ShowGWnd(a);
    this-> m_lable_itemtype_weapon->ShowGWnd(a);
    this-> m_lable_itemtype_accessory->ShowGWnd(a);
    this-> m_lable_itemtype_heavy->ShowGWnd(a);
    this-> m_lable_itemtype_light->ShowGWnd(a);
    this-> m_lable_itemtype_male->ShowGWnd(a);
}
void CIFSTPetFilter::loadconfig() {
        char buffer[0x200];
        sprintf_s(buffer, "%s\\Setting\\chops.dat", theApp.GetWorkingDir());

        FILE *file = fopen(buffer, "wb+");
        if (file != NULL) {
            bool data[58];
            data[0] = m_mybutton_degree01->GetCheckedState_MAYBE();
            data[1] = m_mybutton_degree02->GetCheckedState_MAYBE();
            data[2] = m_mybutton_degree03->GetCheckedState_MAYBE();
            data[3] = m_mybutton_degree04->GetCheckedState_MAYBE();
            data[4] = m_mybutton_degree05->GetCheckedState_MAYBE();
            data[5] = m_mybutton_degree06->GetCheckedState_MAYBE();
            data[6] = m_mybutton_degree07->GetCheckedState_MAYBE();
            data[7] = m_mybutton_degree08->GetCheckedState_MAYBE();
            data[8] = m_mybutton_degree09->GetCheckedState_MAYBE();
            data[9] = m_mybutton_degree10->GetCheckedState_MAYBE();
            data[10] = m_mybutton_degree11->GetCheckedState_MAYBE();
            data[11] = m_mybutton_degree12->GetCheckedState_MAYBE();
            data[12] = m_mybutton_degree13->GetCheckedState_MAYBE();
            data[13] = m_mybutton_degree14->GetCheckedState_MAYBE();
            data[14] = m_mybutton_degree15->GetCheckedState_MAYBE();

            data[15] = m_mybutton_itemtype_weapon->GetCheckedState_MAYBE();
            data[16] = m_mybutton_itemtype_accessory->GetCheckedState_MAYBE();
            data[17] = m_mybutton_itemtype_heavy->GetCheckedState_MAYBE();
            data[18] = m_mybutton_itemtype_light->GetCheckedState_MAYBE();
            data[19] = m_mybutton_itemtype_clothes->GetCheckedState_MAYBE();
            data[20] = m_mybutton_itemtype_male->GetCheckedState_MAYBE();
            data[21] = m_mybutton_itemtype_female->GetCheckedState_MAYBE();

            data[22] = m_checkbox_degree01->GetCheckedState_MAYBE();
            data[23] = m_checkbox_degree02->GetCheckedState_MAYBE();
            data[24] = m_checkbox_degree03->GetCheckedState_MAYBE();
            data[25] = m_checkbox_degree04->GetCheckedState_MAYBE();
            data[26] = m_checkbox_degree05->GetCheckedState_MAYBE();
            data[27] = m_checkbox_degree06->GetCheckedState_MAYBE();
            data[28] = m_checkbox_degree07->GetCheckedState_MAYBE();
            data[29] = m_checkbox_degree08->GetCheckedState_MAYBE();
            data[30] = m_checkbox_degree09->GetCheckedState_MAYBE();
            data[31] = m_checkbox_degree10->GetCheckedState_MAYBE();
            data[32] = m_checkbox_degree11->GetCheckedState_MAYBE();
            data[33] = m_checkbox_degree12->GetCheckedState_MAYBE();
            data[34] = m_checkbox_degree13->GetCheckedState_MAYBE();
            data[35] = m_checkbox_degree14->GetCheckedState_MAYBE();
            data[36] = m_checkbox_degree15->GetCheckedState_MAYBE();
            data[37] = m_checkbox_elixir_weapon->GetCheckedState_MAYBE();
            data[38] = m_checkbox_elixir_shield->GetCheckedState_MAYBE();
            data[39] = m_checkbox_elixir_protector->GetCheckedState_MAYBE();
            data[40] = m_checkbox_elixir_accessory->GetCheckedState_MAYBE();
            data[41] = m_checkbox_tablet_blue->GetCheckedState_MAYBE();
            data[42] = m_checkbox_tablet_red->GetCheckedState_MAYBE();
            data[43] = m_checkbox_stone_blue->GetCheckedState_MAYBE();
            data[44] = m_checkbox_stone_red->GetCheckedState_MAYBE();
            data[45] = m_checkbox_materials->GetCheckedState_MAYBE();

            data[46] =m_checkbox_potion_hp->GetCheckedState_MAYBE();
            data[47] =m_checkbox_potion_mp->GetCheckedState_MAYBE();
            data[48] =m_checkbox_potion_vigor->GetCheckedState_MAYBE();
            data[49] =m_checkbox_grain_hp->GetCheckedState_MAYBE();
            data[50] =m_checkbox_grain_mp->GetCheckedState_MAYBE();
            data[51] =m_checkbox_grain_vigor->GetCheckedState_MAYBE();
            data[52] =m_checkbox_universal_pill->GetCheckedState_MAYBE();
            data[53] =m_checkbox_return_scroll->GetCheckedState_MAYBE();
            data[54] =m_checkbox_arrows->GetCheckedState_MAYBE();
            data[55] =m_checkbox_bolts->GetCheckedState_MAYBE();
            data[56] =m_checkbox_coin->GetCheckedState_MAYBE();
            data[57] =m_checkbox_gold->GetCheckedState_MAYBE();
            fwrite(&data[0], 1, 58, file);
            fclose(file);
        }
}

void CIFSTPetFilter::Initialize()
{
    Rebot::Equipment_TID_List.push_back(0x132C);
    Rebot::Equipment_TID_List.push_back(0x1B2C);
    Rebot::Equipment_TID_List.push_back(0x232C);
    Rebot::Equipment_TID_List.push_back(0x2B2C);
    Rebot::Equipment_TID_List.push_back(0x332C);
    Rebot::Equipment_TID_List.push_back(0x6B2C);
    Rebot::Equipment_TID_List.push_back(0x3B2C);
    Rebot::Equipment_TID_List.push_back(0x432C);
    Rebot::Equipment_TID_List.push_back(0x4B2C);
    Rebot::Equipment_TID_List.push_back(0x632C);
    Rebot::Equipment_TID_List.push_back(0x532C);
    Rebot::Equipment_TID_List.push_back(0x5B2C);
    Rebot::Equipment_TID_List.push_back(0x732C);
    Rebot::Equipment_TID_List.push_back(0x7B2C);
    Rebot::Equipment_TID_List.push_back(0x0A2C);
    Rebot::Equipment_TID_List.push_back(0x122C);
    Rebot::Equipment_TID_List.push_back(0x0AAC);
    Rebot::Equipment_TID_List.push_back(0x0E2C);
    Rebot::Equipment_TID_List.push_back(0x12AC);
    Rebot::Equipment_TID_List.push_back(0x162C);
    Rebot::Equipment_TID_List.push_back(0x1AAC);
    Rebot::Equipment_TID_List.push_back(0x1E2C);
    Rebot::Equipment_TID_List.push_back(0x0D2C);
    Rebot::Equipment_TID_List.push_back(0x092C);
    Rebot::Equipment_TID_List.push_back(0x0CAC);
    Rebot::Equipment_TID_List.push_back(0x0DAC);
    Rebot::Equipment_TID_List.push_back(0x08AC);
    Rebot::Equipment_TID_List.push_back(0x09AC);
    Rebot::Equipment_TID_List.push_back(0x15AC);
    Rebot::Equipment_TID_List.push_back(0x10AC);
    Rebot::Equipment_TID_List.push_back(0x152C);
    Rebot::Equipment_TID_List.push_back(0x11AC);
    Rebot::Equipment_TID_List.push_back(0x112C);
    Rebot::Equipment_TID_List.push_back(0x14AC);
    Rebot::Equipment_TID_List.push_back(0x1CAC);
    Rebot::Equipment_TID_List.push_back(0x192C);
    Rebot::Equipment_TID_List.push_back(0x18AC);
    Rebot::Equipment_TID_List.push_back(0x1DAC);
    Rebot::Equipment_TID_List.push_back(0x19AC);
    Rebot::Equipment_TID_List.push_back(0x1D2C);
    Rebot::Equipment_TID_List.push_back(0x25AC);
    Rebot::Equipment_TID_List.push_back(0x21AC);
    Rebot::Equipment_TID_List.push_back(0x252C);
    Rebot::Equipment_TID_List.push_back(0x212C);
    Rebot::Equipment_TID_List.push_back(0x24AC);
    Rebot::Equipment_TID_List.push_back(0x20AC);
    Rebot::Equipment_TID_List.push_back(0x2CAC);
    Rebot::Equipment_TID_List.push_back(0x292C);
    Rebot::Equipment_TID_List.push_back(0x28AC);
    Rebot::Equipment_TID_List.push_back(0x2DAC);
    Rebot::Equipment_TID_List.push_back(0x2D2C);
    Rebot::Equipment_TID_List.push_back(0x29AC);
    Rebot::Equipment_TID_List.push_back(0x30AC);
    Rebot::Equipment_TID_List.push_back(0x312C);
    Rebot::Equipment_TID_List.push_back(0x31AC);
    Rebot::Equipment_TID_List.push_back(0x34AC);
    Rebot::Equipment_TID_List.push_back(0x352C);
    Rebot::Equipment_TID_List.push_back(0x35AC);
    //weapon
    Rebot::Equipment_TID_Weapon_List.push_back(0x132C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x1B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x232C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x2B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x332C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x6B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x3B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x432C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x4B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x632C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x532C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x5B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x732C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x7B2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x0A2C);
    Rebot::Equipment_TID_Weapon_List.push_back(0x122C);
    //accsessory
    Rebot::Equipment_TID_Accsessory_List.push_back(0x0AAC);
    Rebot::Equipment_TID_Accsessory_List.push_back(0x0E2C);
    Rebot::Equipment_TID_Accsessory_List.push_back(0x12AC);
    Rebot::Equipment_TID_Accsessory_List.push_back(0x162C);
    Rebot::Equipment_TID_Accsessory_List.push_back(0x1AAC);
    Rebot::Equipment_TID_Accsessory_List.push_back(0x1E2C);

    //heavy
    Rebot::Equipment_TID_Heavy_List.push_back(0x0DAC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x09AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x15AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x11AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x1DAC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x19AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x25AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x21AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x2DAC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x29AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x31AC);
    Rebot::Equipment_TID_Heavy_List.push_back(0x35AC);
    //light
    Rebot::Equipment_TID_Light_List.push_back(0x352C);
    Rebot::Equipment_TID_Light_List.push_back(0x312C);
    Rebot::Equipment_TID_Light_List.push_back(0x2D2C);
    Rebot::Equipment_TID_Light_List.push_back(0x292C);
    Rebot::Equipment_TID_Light_List.push_back(0x252C);
    Rebot::Equipment_TID_Light_List.push_back(0x212C);
    Rebot::Equipment_TID_Light_List.push_back(0x192C);
    Rebot::Equipment_TID_Light_List.push_back(0x1D2C);
    Rebot::Equipment_TID_Light_List.push_back(0x112C);
    Rebot::Equipment_TID_Light_List.push_back(0x152C);
    Rebot::Equipment_TID_Light_List.push_back(0x0D2C);
    Rebot::Equipment_TID_Light_List.push_back(0x092C);
    //clothes
    Rebot::Equipment_TID_Clothes_List.push_back(0x0CAC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x08AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x10AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x14AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x1CAC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x18AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x24AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x20AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x2CAC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x28AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x30AC);
    Rebot::Equipment_TID_Clothes_List.push_back(0x34AC);
    //potion
    Rebot::Potion_ObjID_HP_Potion_List.push_back(2284);
    Rebot::Potion_ObjID_HP_Potion_List.push_back(2285);
    Rebot::Potion_ObjID_MP_Potion_List.push_back(4332);
    Rebot::Potion_ObjID_MP_Potion_List.push_back(4333);
    Rebot::Potion_ObjID_Vigor_Potion_List.push_back(6380);
    Rebot::Potion_ObjID_Universal_Pill_List.push_back(12652);
    //pet potion
    Rebot::Potion_Pet_HP_Tid_List.push_back(8428);
    Rebot::Potion_Pet_HGP_Tid_List.push_back(18668);
    Rebot::Potion_Pet_Cure_List.push_back(14700);
    Rebot::Potion_Pet_Resurrect_List.push_back(12524);
    Rebot::Potion_Pet_Resurrect_List.push_back(12525);
    Rebot::Potion_Pet_Summon_Trigger_List.push_back(2253);
    //expendable
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(61);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(2198);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(2199);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(10382);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(2128);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(3769);
    Rebot::Potion_ObjID_Return_Scroll_List.push_back(3795);
    Rebot::Potion_ObjID_Coin_List.push_back(24667);
    Rebot::Potion_ObjID_Coin_List.push_back(24668);
    Rebot::Potion_ObjID_Coin_List.push_back(24669);
    Rebot::Potion_ObjID_Coin_List.push_back(24670);
    Rebot::Potion_ObjID_Coin_List.push_back(25834);

}