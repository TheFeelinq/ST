// Credits: @florian0 https://www.elitepvpers.com/forum/sro-pserver-guides-releases/4256375-source-fix-old-exp-bar-writing-code.html

#include "NIFUnderMenuBar.h"

#include "ICPlayer.h"

#include <stdio.h>
#include "GlobalDataManager.h"
#include "Data\LevelData.h"
#include "memhelp.h"

#include <cmath>
void CNIFUnderMenuBar::SaveQuickslotData(int byIndexSot) {
    reinterpret_cast<void (__thiscall *)(CNIFUnderMenuBar *, int)>(0x0060bea0)(this, byIndexSot);
}

void CNIFUnderMenuBar::On_Cmd32869() {
    //reinterpret_cast<void (__thiscall *)(CNIFUnderMenuBar *)>(0x0060df30)(this);
    CIFSlotWithHelpEx * m_slotNew[11];
    RECT rect_m_0 = {368, 456, 32, 32};
    m_slotNew[0] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_0,300,1);
    RECT rect_m_1 = {405, 456, 32, 32};
    m_slotNew[1] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_1,301,1);
    RECT rect_m_2 = {440, 456, 32, 32};
    m_slotNew[2] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_2,302,1);
    RECT rect_m_3 = {476, 456, 32, 32};
    m_slotNew[3] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_3,303,1);
    RECT rect_m_4 = {512, 456, 32, 32};
    m_slotNew[4] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_4,304,1);
    RECT rect_m_5 = {548, 456, 32, 32};
    m_slotNew[5] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_5,305,1);
    RECT rect_m_6 = {584, 456, 32, 32};
    m_slotNew[6] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_6,306,1);
    RECT rect_m_7 = {620, 456, 32, 32};
    m_slotNew[7] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_7,307,1);
    RECT rect_m_8 = {656, 456, 32, 32};
    m_slotNew[8] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_8,308,1);
    RECT rect_m_9 = {692, 456, 32, 32};
    m_slotNew[9] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_9,309,1);
    RECT rect_m_10 = {318, 456, 32, 32};
    m_slotNew[10] = (CIFSlotWithHelpEx *) CGWnd::CreateInstance(this,GFX_RUNTIME_CLASS(CIFSlotWithHelpEx),rect_m_10,310,1);

}

const DWORD dwHookPrintHelpMsg = 0x0060e090; //friend list sc
const DWORD dwHookPrintHelpMsgCall = 0x006666f0; //friend list sc
const DWORD dwHookPrintHelpMsgJumpback = 0x0060e095;
//0060e138

__declspec(naked) void HookOn_Cmd32869()
{
    __asm
    {
    CALL dwHookPrintHelpMsgCall;
    pushad;
    call CNIFUnderMenuBar::On_Cmd32869;
    popad;
    jmp dwHookPrintHelpMsgJumpback;
    }
    }
void CNIFUnderMenuBar::Initialize()
{

    memhelp::RenderNop((void*)dwHookPrintHelpMsg, 5);
    memhelp::RenderDetour(ASM_JMP, (void*)dwHookPrintHelpMsg, HookOn_Cmd32869);

}

void CNIFUnderMenuBar::Update() {
    // Skip, if player object is not loaded yet (KEEP!)
    if (!g_pCICPlayer) {
        return;
    }

    // Some other call that is important (KEEP!)
    ((void (__thiscall *)(CNIFUnderMenuBar *)) 0x46CD80)(this);

    // Check if control is visible
    if (!((char (__thiscall *)(CNIFUnderMenuBar *)) 0x00B8F530)(this)) {
        return;
    }

    // Retrieve LevelData for current Level
    // (this is one line of Media\server_dep\silkroad\textdata\leveldata.txt)
    CLevelData *data = g_CGlobalDataManager->m_levelDataMap[g_pCICPlayer->m_level];

    // Don't continue if level-data is invalid
    if (data == NULL) {
        return;
    }

    // Calculate EXP as percentage value
    double exp_percentage = g_pCICPlayer->m_exp_current * 100.0 / data->data.m_expC;

    // Limit maximum percentage to 99.99%
    if (exp_percentage > 99.99) {
        exp_percentage = 99.99;
    }

    // Calculate the number of bars that are full
    int barnum = floor(exp_percentage / 10.0);


    for (int i = 0; i < 10; i++) {

        // Fill or empty bars
        if (barnum <= i) {
            gauges[i]->background_value = 0.0;
            gauges[i]->foreground_value = 0.0;
        } else {
            gauges[i]->background_value = 1.0;
            gauges[i]->foreground_value = 1.0;
        }
    }

    // Fill the bar that is neither full or empty with the remaining percentage
    double exp_remain = (exp_percentage - (barnum * 10.0)) / 10.0;

    gauges[barnum]->background_value = exp_remain;
    gauges[barnum]->foreground_value = exp_remain;

    // Assign more texts
    this->lbl_level->SetText(L"Level: %d", g_pCICPlayer->m_exp_current);
    this->lbl_percentage->SetText(L"%.2lf %%", exp_percentage);

    // Skillpoints
    this->lbl_spcount->SetText(L"%d", g_pCICPlayer->m_skillpoint);
    this->gauge_skillexp->background_value = g_pCICPlayer->m_skillpoint_progress / 400.0;
    this->gauge_skillexp->foreground_value = g_pCICPlayer->m_skillpoint_progress / 400.0;

    // You can also draw text directly at the gauge. It will be centered automatically
    // this->gauge_skillexp->SetText(L"%d", g_CICPlayer->skill_exp);


    this->lbl_exp_bar_scaler->SetText(L""); // Prescaler is disabled

    // This label is right in the middle of the EXP-Bar
    //this->lbl_360->SetText(L"lbl_360");
};
