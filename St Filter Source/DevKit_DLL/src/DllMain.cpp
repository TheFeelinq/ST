#include <IFChatViewer.h>
#include "hooks/Hooks.h"
#include "Util.h"
#include "imgui_windows/ImGui_Windows.h"

#include "CPSMission.h"
#include <memory/hook.h>
#include <NIFUnderMenuBar.h>
#include <IFSlotWithHelp.h>
#include <IFMainPopup.h>
#include <NotificationHandler.h>
#include <NetProcessIn.h>
#include "CPSTitle.h"
#include <IFChatOptionBoard.h>
#include <IFWholeChat.h>
#include <IFSTOldLogin.h>
#include <IFMessageBox.h>
#include <OptimizeCloth.h>
#include <IFSTPetFilter.h>
#include <PSCharacterSelect.h>
#include <HWID Manager/LoadHWID.h>
#include <IFPartyMatch.h>
#include <IFTargetWindow.h>
#include "IFSlotWithHelpForPackage.h"
#include "ICCos.h"
#include "IFSTTaiXiu.h"
#include "IFSTDailyLogin.h"
#include "IFCircularMenu.h"
HMODULE sro_client = 0;
extern "C" _declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        sro_client = GetModuleHandle(NULL);
        Setup();
        AddRegion();
        LoadHWID::HWIDLoad();
        CPSTitle::Version();
        g_notificationhandler.Initialize();
       // RenderNop((void*)0x006EC77E , 2);
        IFSTOldLogin::Initialize();
        //CICCos::Initialize();
        //CharacterIcons::Initialize();
        CIFSTPetFilter::Initialize();
        CIFChatViewer::Initialize();
        //CNIFUnderMenuBar::Initialize();
       // g_NetCustoms->Initialize();
        ///show char icon
        //RenderNop((void*)0x009DED3D, 6);
        //RenderNop((void*)0x1D90BD58, 2);

        ///Client freeze
       // RenderNop((void*)0x00BA6FC8, 10);

        //RenderNop((void*)0x008AF854, 86);


        ///show alchemypara
        //RenderNop((void*)0x0088c4e9, 4);

        //LoadHW::HWIDLoad();
        //replaceOffset(0x0070BCF2, addr_from_this(&CInterfaceNetSender::DonateGuildPoints));
        // Inject all the new objects
        RegisterObject(&GFX_RUNTIME_CLASS(CIFSTTaiXiu));
        RegisterObject(&GFX_RUNTIME_CLASS(CIFDailyLogin));
        RegisterObject(&GFX_RUNTIME_CLASS(CIFCircularMenu));
       // RegisterObject(&GFX_RUNTIME_CLASS(CIFExtQuickSlotSecond));

        replaceOffset(0x00686ed0, addr_from_this(&CIFSlotWithHelp::HelperBubbleInventoryAndEquipment));
        replaceOffset(0x00687100, addr_from_this(&CIFSlotWithHelp::HelperBubbleInventoryAndEquipment));
        /////item compare
        replaceOffset(0x00682AFC, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
        replaceOffset(0x00682D6E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
        replaceOffset(0x00682FBE, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
        replaceOffset(0x0068320E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));

        //replaceOffset(0x00686BC2, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00685dce, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00685b05, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00683216, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00682fc6, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00682d76, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00682b04, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x0068273d, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));
        //replaceOffset(0x00682392, addr_from_this(&CIFSlotWithHelpForPackage::ChangeColorPrice));


        /////item comma - price color
        replaceOffset(0x00678e1f, addr_from_this(&CIFHelperBubbleWindow::WriteLineGold));
        replaceOffset(0x00678ee8, addr_from_this(&CIFHelperBubbleWindow::WriteLineSilk));
        replaceOffset(0x00678fb1, addr_from_this(&CIFHelperBubbleWindow::WriteLineGSilk));
        replaceOffset(0x00679143, addr_from_this(&CIFHelperBubbleWindow::WriteLinePSilk));
        replaceOffset(0x0067907a, addr_from_this(&CIFHelperBubbleWindow::WriteLineGP));
        replaceOffset(0x0067920c, addr_from_this(&CIFHelperBubbleWindow::WriteLineHonorPoint));
        replaceOffset(0x006792d5, addr_from_this(&CIFHelperBubbleWindow::WriteLineTokenSD1));
        replaceOffset(0x0067939d, addr_from_this(&CIFHelperBubbleWindow::WriteLineTokenSD2));
        replaceOffset(0x00679469, addr_from_this(&CIFHelperBubbleWindow::WriteLineTokenSD3));
        replaceOffset(0x00679535, addr_from_this(&CIFHelperBubbleWindow::WriteLineTokenSD4));
        replaceOffset(0x00679601, addr_from_this(&CIFHelperBubbleWindow::WriteLineArenaCoin));

        replaceOffset(0x007407eb, addr_from_this(&CIFHelperBubbleWindow::WriteLineParty));
        replaceOffset(0x0074081a, addr_from_this(&CIFHelperBubbleWindow::WriteLineParty));

        //replaceOffset(0x0064e32f, addr_from_this(&CIFMessageBox::SetGWndSizeIMPL));
        //replaceOffset(0x0081a920, addr_from_this(&CIFMessageBox::SetGWndSizeIMPL));
        replaceOffset(0x006ec77b, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x004f8e51, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x00676cc3, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x0086252a, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x0086c5a8, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x0087acdd, addr_from_this(&CIFMessageBox::CreateReverse));
        replaceOffset(0x00883af9, addr_from_this(&CIFMessageBox::CreateReverse));


        replaceOffset(0x00741239, addr_from_this(&CIFPartyMatch::FUN_00740910));
        //replaceOffset(0x0074122d, addr_from_this(&CIFPartyMatch::FUN_00740870));
        //replaceAddr(0x00db4394, addr_from_this(&CIFPartyMatch::FUN_00740750));

        replaceAddr(0x00DD440C, addr_from_this(&CPSMission::OnPacketRecv));
        replaceAddr(0x00DE2C4C, addr_from_this(&CICPlayer::OnRender));
        replaceAddr(0x00DE2144, addr_from_this(&CICCos::OnRender));
        replaceAddr(0x00D9841C, addr_from_this(&CNIFUnderMenuBar::Update));

        //OverrideObject<CIFExtQuickSlot, 0x00ee9a28>();
        //OverrideObject<CIFExtQuickSlotOption, 0x00ee9a48>();
        OverrideObject<CIFMainPopup, 0x00eea6dc>();
        OverrideObject<CIFChatViewer, 0x00EEC168>();
        OverrideObject<CIFChatOptionBoard, 0x00eec128>();
        OverrideObject<CIFWholeChat, 0x00eec7a8>();
        OverrideObject<CIFTargetWindow, 0x00eea57c>();
        OverrideObject<CIFTargetWindowCommonEnemy, 0x00eea59c>();
        //OverrideObject<CIFTargetWindowFortressStructure, 0x00ee7b00>();
        OverrideObject<CIFTargetWindowJobPlayer, 0x00eea5bc>();
        //OverrideObject<CIFTargetWindowSpecialMob, 0x00eea5fc>();
        OverrideObject<CIFTargetWindowPlayer, 0x00eea5dc>();

        //OverrideObject<CIFPlayerInfo, 0x00eea7e8>();
        CPSCharacterSelect::char_select_override();
        // Override existing objects

//FUN_00624380
#ifdef CONFIG_IMGUI
        OnCreate(ImGui_OnCreate);
        OnEndScene(ImGui_OnEndScene);
        OnWndProc(ImGui_WndProc);
        OnPreSetSize(ImGui_OnPreSetSize);
        OnPostSetSize(ImGui_OnPostSetSize);
#endif // CONFIG_IMGUI


        OnPreInitGameAssets(InstallRuntimeClasses);
    }

    return TRUE;
}
