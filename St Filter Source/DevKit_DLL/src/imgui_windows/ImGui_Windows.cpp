#include "ImGui_Windows.h"
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_dx9.h"
#include "imgui/examples/imgui_impl_win32.h"
#include "ProcessViewer.h"
#include <GFX3DFunction/GFXVideo3d.h>
#include <GFX3DFunction/DrawingHelpers.h>

#include <GInterface.h>
#include "unsorted.h"

#include "../hooks/Hooks.h"
#include "../MathUtil.h"
#include "IFSystemMessage.h"
#include "InterfaceDebugger.h"
#include "NavMeshTool.h"
#include "EntityExplorer.h"
#include "SoundTool.h"
#include "NotificationTool.h"
#include "About.h"
#include "SystemMessage.h"
#include "ErrorMessageTool.h"
#include <BSLib/multibyte.h>
#include <BSLib/Debug.h>
#include <IFChatViewer.h>
#include "InterfaceTree.h"
#include "../MinHook/MinHook.h"
#include <TextStringManager.h>
#include <ctime>
#include <GlobalDataManager.h>
#include <Rebot.h>
#include <memory/hook.h>
#include <IFWholeChat.h>
#include <IFflorian0Guide.h>
#include <PartyData.h>
#include "ObjectData.h"
#include "IRMManager.h"
#include "PartyInfo.h"
#include <CharacterDependentData.h>
#include <CPSMission.h>
#include <IFMessageBox.h>
#include <PSCharacterSelect.h>
#include <algorithm>
#include <IFPartyMatch.h>
#include <GameDataExt.h>
#include <IFTargetWindow.h>
#include "BSLib/BSLib.h"
#include "CharacterData.h"
#include "Inventory.h"
#include "ColorPicker.h"
#include "ItemData.h"
#include "PetFilter.h"
#include "FPSViewer.h"
#include "../Util.h"
#include "CircleDrawTool.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



InterfaceDebugger interfaceDebugger;
NavMeshTool navmeshExplorer;
EntityExplorer entityExplorer;
SoundTool soundTool;
NotificationTool notificationTool;
About aboutWnd;
SystemMessage systemMessage;
ProcessViewer processViewer;
ErrorMessageTool errorMessageTool;
InterfaceTree interfaceTree;
PartyInfo partyInfo;
CharacterData characterData;
ItemData itemData;
Inventory inventory;
PetFilter petfilter;
Rebot rebot;
ColorSelect colorSelect;
CircleDrawTool circleDrawTool;
FPSViewer fpsViewer;
typedef HRESULT(APIENTRY* Reset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
Reset HookReset = NULL;

HRESULT APIENTRY MyReset(IDirect3DDevice9* pDevice,D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    //printf("%p\r\n", g_CD3DApplication->m_pd3dDevice);
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT ResetReturn = HookReset(pDevice, pPresentationParameters);
    ImGui_ImplDX9_CreateDeviceObjects();
    return ResetReturn;
}

void ImGui_OnCreate(HWND hWindow, void *msghandler, int a3) {

    DWORD32* g_methodsTable = (DWORD32*)::calloc(119, sizeof(DWORD32));
    ::memcpy(g_methodsTable, *(DWORD32**)g_CD3DApplication->m_pd3dDevice, 119 * sizeof(DWORD32));

    void* target = (void*)g_methodsTable[16];

    MH_Initialize();
    MH_CreateHook(target, MyReset, (void**)&HookReset);
    //MH_EnableHook(target);
    //MH_CreateHook((void*)0x009EC570, (PVOID)addr_from_this(&CNavigationDeadreckon::MoveToHook), (void**)&HookMoveTo);
    MH_EnableHook(MH_ALL_HOOKS);


    Rebot::GameHWND = hWindow;
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameBorderSize = 1;
    io.FontDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    ImGui_ImplWin32_Init(hWindow);
    ImGui_ImplDX9_Init(g_CD3DApplication->m_pd3dDevice);
}
std::string GetClipboardText()
{
    std::string text ="";
    std::string text1 =" ";
    if (OpenClipboard(NULL))
    {
        HANDLE clip;

        if(IsClipboardFormatAvailable(CF_TEXT))
        {
            clip = GetClipboardData(CF_TEXT);
            // lock and copy
            text = (LPSTR)GlobalLock(clip);
            // unlock
            GlobalUnlock(clip);
            CloseClipboard();
            return text;
        } else
        {
            CloseClipboard();
            return text1;
        }

    }

}

void ImGui_OnEndScene() {
    BS_DEBUG_LOW("ImGui_OnEndScene %d", g_CD3DApplication->IsLost());

    if (g_CD3DApplication->IsLost()) {
        return;
    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    if(g_CurrentNavMesh)
        Rebot::CRTNavMeshTerrainAll[g_CurrentNavMesh->m_Region] = g_CurrentNavMesh;
    // Menu




 /*        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::MenuItem("Debug Mode", NULL, reinterpret_cast<bool *>(0x00EED6A7));

                ImGui::Separator();

                if (ImGui::MenuItem("Restart"))
                    SendRestartRequest(2);

                if (ImGui::MenuItem("Exit"))
                    SendRestartRequest(1);

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit")) {
                ImGui::MenuItem("Cut", 0, false, false);
                ImGui::MenuItem("Copy", 0, false, false);
                ImGui::MenuItem("Paste", 0, false, false);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Options")) {
                ImGui::MenuItem("Fullscreen", 0, false, false);

                if (ImGui::BeginMenu("Resolution")) {
                    ImGui::MenuItem("640x480 (4:3)", 0, false, false);
                    ImGui::MenuItem("800x600 (4:3)", 0, false, false);
                    ImGui::Separator();
                    ImGui::MenuItem("Enter custom resolution", 0, false, false);

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Camera")) {
                    ImGui::MenuItem("Fixed behind character", 0, false, false);
                    ImGui::MenuItem("Fixed height", 0, false, false);
                    ImGui::MenuItem("Free visual point", 0, false, false);
                    ImGui::MenuItem("Free (Fly)", 0, false, false);

                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Tools")) {
                interfaceDebugger.MenuItem();
                interfaceTree.MenuItem();
                navmeshExplorer.MenuItem();
                entityExplorer.MenuItem();
                ImGui::MenuItem("Keyframe Editor", 0, false, false);
                ImGui::MenuItem("Script Editor", 0, false, false);
                soundTool.MenuItem();
                notificationTool.MenuItem();
                systemMessage.MenuItem();
                errorMessageTool.MenuItem();
                processViewer.MenuItem();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Data")) {
                partyInfo.MenuItem();
                characterData.MenuItem();
                inventory.MenuItem();
                itemData.MenuItem();
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows")) {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help")) {
                aboutWnd.MenuItem();
                if (ImGui::MenuItem("Online Help")) {
                    ShellExecute(NULL,
                                 TEXT("open"),
                                 TEXT("https://florian0.gitlab.io/sro_devkit/"),
                                 NULL, NULL, SW_SHOWNORMAL);
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }


    interfaceDebugger.Render();
    entityExplorer.Render();
    soundTool.Render();
    notificationTool.Render();
    navmeshExplorer.Render();
    //aboutWnd.Render();
    systemMessage.Render();
    errorMessageTool.Render();
    interfaceTree.Render();
    processViewer.Render();
    partyInfo.Render();
    characterData.Render();
    itemData.Render();
    inventory.Render();
    //petfilter.Render();
    rebot.Render();
*/

    circleDrawTool.Render();
    fpsViewer.Render();
    colorSelect.Render();
    ImGui::Render();

    ImGui::EndFrame();



    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

time_t lastClickTime7;
LRESULT CALLBACK ImGui_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    BS_DEBUG_LOW("ImGui_WndProc");

    // Check if context is already created
    if (!ImGui::GetCurrentContext())
        return RESULT_PASS;

    switch (message)
    {
       /* case WM_CLOSE:
            exit(EXIT_SUCCESS);
            break;*/

        case WM_KEYDOWN:
            if (*(DWORD**)0x0110F80C) // if cginterface is set
            {
                if (wParam == 'f' || wParam == 'F') {
                    if (g_pCICPlayer) {
                           if (g_CNIRMManager->GetWindowActive(0x96) == 0) {
                                g_pCGInterface->SwitchToStallNetwork(true);
                            } else {
                                g_pCGInterface->SwitchToStallNetwork(false);
                            }
                    }
                }
                if (wParam == 'v' || wParam == 'V') {
                    if (g_pCGInterface) {
                        short ALTState = GetKeyState(VK_CONTROL);
                        if ((ALTState == -127 || ALTState == -128))
                        {

                                CIFWnd *WholeChat = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(56, 1);
                                CIFChatViewer *chatView = (CIFChatViewer *) g_pCGInterface->m_IRM.GetResObj(1, 1);
                                CIFWholeChat *WholeChatText = (CIFWholeChat *) g_pCGInterface->m_IRM.GetResObj(56, 1);
                                if (WholeChat && WholeChat->IsVisible()) {
                                    std::wstring copy = TO_WSTRING(GetClipboardText()).c_str();
                                    std::wstring copy2 = WholeChatText->m_pEdit->GetNText().c_str();
                                    if (copy.length() + copy2.length() < 110) {
                                        copy2 += copy;
                                        WholeChatText->m_pEdit->SetText(copy2.c_str());
                                    }
                                } else {
                                    std::wstring copy = TO_WSTRING(GetClipboardText()).c_str();
                                    std::wstring copy2 = chatView->m_InputBox->GetText();
                                    if (copy.length() + copy2.length() < 110) {
                                        copy2 += copy;
                                        chatView->m_InputBox->SetText(copy2.c_str());
                                    }
                                }


                        }
                    }
                }
            }
            break;
        case WM_LBUTTONUP:
            if (g_pCGInterface) // if cginterface is set
            {
                if (g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFButton))) {
                    if(g_CurrentIfUnderCursor->UniqueID()==5555 && g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->GetBtnStatus())
                    {
                        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->ClearDDJ();
                        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->ShowGWnd(true);
                        g_pCGInterface->GetCIFSTReverseScrollPlusGUI()->ResetPosition();
                    }
                }
                if (g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFButton))) {
                    if(g_CurrentIfUnderCursor->UniqueID()==5588)
                    {
                        g_pCGInterface->GetPetFilterGUI()->ShowGWnd(true);

                    }
                }
                if (g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFButton))) {
                    if(g_CurrentIfUnderCursor->UniqueID()==5589)
                    {
                        if (Blocked_Party_CharNameRequest.find(CPSMission::CharNameRequest.c_str()) == Blocked_Party_CharNameRequest.end())
                        {
                            Blocked_Party_CharNameRequest.insert(CPSMission::CharNameRequest.c_str());
                            wchar_t buffer[255];
                            swprintf_s(buffer, L"Blocked %S",CPSMission::CharNameRequest.c_str());
                            g_pCGInterface->ShowMessage_Warning(buffer);
                            g_pCGInterface->m_IRM.GetResObj(131, 1)->ShowGWnd(false);
                        }

                    }
                }
                if (g_CurrentIfUnderCursor->IsSame(GFX_RUNTIME_CLASS(CIFButton))) {
                    if(g_CurrentIfUnderCursor->UniqueID()==5590)
                    {
                        g_pCGInterface->GetChangeGrantNameGUI()->m_edit->SetText(L"");
                        g_pCGInterface->GetChangeGrantNameGUI()->ShowGWnd(true);
                        g_pCGInterface->GetChangeGrantNameGUI()->m_edit->SetFocus_MAYBE();
                        g_pCGInterface->GetChangeGrantNameGUI()->ResetPosition();
                        g_pCGInterface->GetChangeGrantNameGUI()->BringToFront();
                    }
                }
                if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CNIFButton")) {
                    if(g_CurrentIfUnderCursor->UniqueID()==8888)
                    {
                        /*if (g_pCGInterface->Get_SelectedObjectId() != 0) {
                            CIObject *SelectdObject = Rebot::FindBaseByUID(g_pCGInterface->Get_SelectedObjectId());
                            if (!strcmp(SelectdObject->GetRuntimeClass()->m_lpszClassName, "CICUser")) {
                                CICUser *SelectdUser = (CICUser *) SelectdObject;
                                CPSMission::CharNameSelected=SelectdUser->GetName().c_str();

                            }
                        }*/
                        CIFTargetWindow *TargetWindow = reinterpret_cast<CIFTargetWindow *>(g_pCGInterface->m_IRM.GetResObj(16, 1));
                        if (TargetWindow && TargetWindow->IsVisible()) {
                            {
                                CIFTargetWindowPlayer *TargetWindowPlayer = TargetWindow->m_IRM.GetResObj<CIFTargetWindowPlayer>(0, 1);
                                CMsgStreamBuffer buf(0x1319);
                                buf << TO_NSTRING(CPSMission::CharNameSelected);
                                buf << std::n_string("!CHECKCHARINFO");
                                SendMsg(buf);
                                g_pCGInterface->GetCharInfoGUI()->m_slot->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot1->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot2->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot3->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot4->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot5->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot6->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot7->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot8->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot9->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot10->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot11->TB_Func_13("", 0, 0);
                                g_pCGInterface->GetCharInfoGUI()->m_slot12->TB_Func_13("", 0, 0);
                                SCharItemInfoList.clear();
                                g_pCGInterface->GetCharInfoGUI()->MoveGWnd(TargetWindowPlayer->GetPos().x+236,TargetWindowPlayer->GetPos().y);
                                g_pCGInterface->GetCharInfoGUI()->BringToFront();
                                g_pCGInterface->GetCharInfoGUI()->ShowGWnd(true);

                            }
                        }
                    }
                }
            }
            break;
        /*case WM_RBUTTONUP:
            if (g_pCGInterface && g_pCICPlayer) // if cginterface is set
            {
                printf("xxxxxxxxxxxxxxxsss");
                if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFEdit")) {
                    CIFEdit *CurEdit = (CIFEdit *) g_CurrentIfUnderCursor;
                    CIFWnd *WholeChat = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(56, 1);
                    if(WholeChat && WholeChat->IsVisible()){
                        std::wstring copy = ReadFromClipBoard().c_str();
                        std::wstring copy2 = CurEdit->GetNText().c_str();
                        if (copy.length() +copy2.length()  <110) {
                            copy2 += copy;
                            CurEdit->SetText(copy2.c_str());
                        }
                    }
                }
                else if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFEInputChatBox"))
                {
                    CIFEdit *CurEdit = (CIFEdit *) g_CurrentIfUnderCursor;
                    std::wstring copy = ReadFromClipBoard().c_str();
                    std::wstring copy2 = CurEdit->GetNText().c_str();
                    if (copy.length() +copy2.length()  <110) {
                        copy2 += copy;
                        CurEdit->SetText(copy2.c_str());
                    }
                }
            }
            break;*/
        case WM_USEITEM:
            return  RESULT_PASS; //0x199B;
            break;
        case WM_USESKILL:
            if(g_pCICPlayer && g_pCGInterface)
            {
                if (Rebot::SkillStatus[wParam]!=NULL&&time(NULL)- Rebot::SkillStatus[wParam]<1) {
                    return false;
                }

                if (Rebot::GetSkillCoolDown(wParam) > 0) {
                    return false;
                }
                Rebot::SkillStatus[wParam] = time(NULL);
                return Rebot::CastSpell(wParam, lParam);

            }
            break;
        case WM_MOVECHAR:
            if(g_pCICPlayer && g_pCGInterface)
            g_pCGInterface->m_Nav.MoveTo(*(uregion*)wParam, *(D3DVECTOR*)lParam);
            return RESULT_DISCARD; //0x199A;
            break;
        case WM_CHOOSEMONSTER:
            if(g_pCICPlayer && g_pCGInterface)
            Rebot::SelectObject(wParam);
            return true;
            break;
        case WM_REBOTSTATUS:
            if (wParam == 1) {
                Rebot::RebotStart = !Rebot::RebotStart;
                if (Rebot::RebotStart) {

                    g_pCGInterface->ShowMessage_Quest(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_STATUS_ON"));
                    D3DVECTOR CenterPos = g_pCICPlayer->GetLocation();
                    Rebot::Config.StartPos = CenterPos;
                    CenterLocations=CenterPos;
                    Rebot::Config.StartRegion = g_pCICPlayer->GetRegion();
                    PatrolRegions = g_pCICPlayer->GetRegion();
                    CGEffSoundBody::get()->PlaySound(L"snd_quest");
                    if(Rebot::Config.AutoBerserk)
                        Rebot::UseBerSerk();
                }
                else {
                    g_pCGInterface->ShowMessage_Quest(TSM_GETTEXTPTR("UIIT_ST_MACRO_AUTO_STATUS_OFF"));
                    CGEffSoundBody::get()->PlaySound(L"snd_quest");
                }
            }

            return true;
            break;

    }

    CPSCharacterSelect* pProcess = (CPSCharacterSelect*)theApp.GetCurrentProcess();
    if (message == WM_LBUTTONDBLCLK && !g_pCICPlayer)
    {
        //ptr CPSCharacterSelect::vftable
        if (*(DWORD*)pProcess == 0x00dd811c && CPSMission::Double_Click_ToLogin && CPSMission::m_CharSelectOn && strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFButton"))
        {
            if (pProcess->m_IRM.GetResObj<CIFStatic>(14, 1)->IsVisible())
            {
                CIFStatic* name = pProcess->m_IRM.GetResObj<CIFStatic>(31, 1);
                if((time(NULL) - lastClickTime7 > 2)) {

                    CMsgStreamBuffer buf(0x7001);
                    buf << std::string(TO_STRING(name->GetNText())); // Character Name
                    SendMsg(buf);
                    lastClickTime7 = time(NULL);
                }

            }
        }
    }

    ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
/*
    if(g_pCICPlayer)
    {

        if(g_pCGInterface->GetCustomTitleGUI()->IsVisible() || Rebot::RebotShow)
        {
            ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);

        }

    }
*/

    if (g_pCGInterface && message == WM_LBUTTONDOWN)
    {
        if(!CPSMission::Npc_Is_Opening && !strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp"))
        {
            CIFSlotWithHelp* CurSlot = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;
            short CTRLState = GetKeyState(VK_CONTROL);
            short MouseState = GetKeyState(VK_LBUTTON);
            short ALTState = GetKeyState(VK_MENU);
            if (CurSlot && (CTRLState == -127 || CTRLState == -128) && (MouseState == -127 || MouseState == -128))
            {
                CSOItem *myitem11 = CurSlot->ItemInfo;

                int GetParentWindow = CurSlot->GetParentWindowId();
                if (GetParentWindow == 70 && CurSlot->ItemInfo) {


                    CIFWnd *WholeChat = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(56, 1);
                    const wchar_t *ItemName = g_CTextStringManager->GetStringTextByCode(myitem11->GetObjectData()->ObjNameStrID.c_str())->c_str();
                    wchar_t* NewMsg = new wchar_t[1024];
                    int SlotID = CurSlot->GetSlotInInventory() + 0xD;
                    CSOItem *this_03 = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(CurSlot->GetSlotInInventory());
                    if(WholeChat && WholeChat->IsVisible())
                    {
                        CIFWholeChat* chatView = (CIFWholeChat*)g_pCGInterface->m_IRM.GetResObj(56, 1);
                        std::wstring copy2 = chatView->m_pEdit->GetText();
                        {
                            wsprintfW(NewMsg, L"%s<%s>", chatView->m_pEdit->GetText(), ItemName);

                            chatView->m_pEdit->SetText(NewMsg);
                            chatView->SetFocus_MAYBE();
                            chatView->m_pEdit->SetFocus_MAYBE();
                            chatView->SetIcon(this_03);
                            std::n_wstring ItemNameW = std::n_wstring(ItemName);
                            UINT16 Size = ItemNameW.length();

                            NEWMSG(0x170C)
                                pReq.Write(&Size, 2);
                                pReq.Write(ItemName, Size * 2);
                                pReq.Write(&SlotID, 1);
                            SENDMSG()
                        }
                    }
                    else
                    {

                        CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
                        std::wstring copy2 = chatView->m_InputBox->GetText();
                        {
                            wsprintfW(NewMsg, L"%s<%s>", chatView->m_InputBox->GetText(), ItemName);
                            chatView->m_InputBox->SetText(NewMsg);
                            chatView->SetFocus_MAYBE();
                            chatView->m_InputBox->SetFocus_MAYBE();
                            std::n_wstring ItemNameW = std::n_wstring(ItemName);
                            UINT16 Size = ItemNameW.length();
                            CIFInventory *inventory = g_pCGInterface->GetMainPopup()->GetInventory();
                            CSOItem *item = inventory->GetItemBySlot(SlotID-0xD);
                            NEWMSG(0x170C)
                                pReq.Write(&Size, 2);
                                pReq.Write(ItemName, Size * 2);
                                pReq.Write(&SlotID, 1);
                            SENDMSG()

                        }
                    }

                }

            }
            if (CurSlot && (ALTState == -127 || ALTState == -128) && (MouseState == -127 || MouseState == -128)) {

                CSOItem *myitem11 = CurSlot->ItemInfo;
                int GetParentWindow = CurSlot->GetParentWindowId();
                if (GetParentWindow == 70 && CurSlot->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->IsVisible())
                {
                    if (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 3768 && GetParentWindow == 70) {
                        g_pCGInterface->GetExtraFeatureGUI()-> m_dame_abs_slot = CurSlot->GetSlotInInventory();
                        //CurSlot->FUN_00666810(0);
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot1->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot1->FUN_006871d0(CurSlot->ItemInfo);
                    }
                    if (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 3767 && GetParentWindow == 70) {
                        g_pCGInterface->GetExtraFeatureGUI()->m_dame_inc_slot = CurSlot->GetSlotInInventory();
                        //CurSlot->FUN_00666810(0);
                        g_pCGInterface->GetExtraFeatureGUI()-> m_slot2->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()-> m_slot2->FUN_006871d0(CurSlot->ItemInfo);
                    }
                    if ((CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24394 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24390 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24386 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24402 && GetParentWindow == 70)) ///abs item
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->m_dame_absorbbubble_slot = CurSlot->GetSlotInInventory();
                        //CurSlot->FUN_00666810(0);
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot3->FUN_006871d0(g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo);
                    }
                    if ((CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24393 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24389 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24385 && GetParentWindow == 70)
                        || (CurSlot->ItemInfo && myitem11->GetObjectData()->ObjID == 24401 && GetParentWindow == 70)) ///inc item
                    {
                        g_pCGInterface->GetExtraFeatureGUI()->m_dame_Increasebubble_slot = CurSlot->GetSlotInInventory();
                        //CurSlot->FUN_00666810(0);
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot4->FUN_006871d0(g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo);
                    }
                    if ((CurSlot->ItemInfo->GetObjectData()->TID == 14061 || CurSlot->ItemInfo->GetObjectData()->TID == 14060) && GetParentWindow == 70) {
                        g_pCGInterface->GetExtraFeatureGUI()-> m_ressurect_slot = CurSlot->GetSlotInInventory();
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot5->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot5->FUN_006871d0(CurSlot->ItemInfo);
                    }
                    if (CurSlot->ItemInfo->GetObjectData()->TID == 16620  && GetParentWindow == 70) {
                        g_pCGInterface->GetExtraFeatureGUI()-> m_berserker_potion_slot = CurSlot->GetSlotInInventory();
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot6->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetExtraFeatureGUI()->m_slot6->FUN_006871d0(CurSlot->ItemInfo);
                    }
                }
                if (GetParentWindow == 70 && CurSlot->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->IsVisible())
                {
                    std::list<int>::iterator hp = std::find(Rebot::Potion_ObjID_HP_Potion_List.begin(), Rebot::Potion_ObjID_HP_Potion_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator mp = std::find(Rebot::Potion_ObjID_MP_Potion_List.begin(), Rebot::Potion_ObjID_MP_Potion_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator vigor = std::find(Rebot::Potion_ObjID_Vigor_Potion_List.begin(), Rebot::Potion_ObjID_Vigor_Potion_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator abnormal = std::find(Rebot::Potion_ObjID_Universal_Pill_List.begin(), Rebot::Potion_ObjID_Universal_Pill_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator speed = std::find(Rebot::Speed_Scroll_ItemID.begin(), Rebot::Speed_Scroll_ItemID.end(), CurSlot->ItemInfo->GetItemData()->m_id);
                    std::list<int>::iterator pet_hp = std::find(Rebot::Potion_Pet_HP_Tid_List.begin(), Rebot::Potion_Pet_HP_Tid_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator pet_hgp = std::find(Rebot::Potion_Pet_HGP_Tid_List.begin(), Rebot::Potion_Pet_HGP_Tid_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator pet_cure = std::find(Rebot::Potion_Pet_Cure_List.begin(), Rebot::Potion_Pet_Cure_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator pet_resurrect = std::find(Rebot::Potion_Pet_Resurrect_List.begin(), Rebot::Potion_Pet_Resurrect_List.end(), CurSlot->ItemInfo->GetItemData()->TID);
                    std::list<int>::iterator pet_trigger = std::find(Rebot::Potion_Pet_Summon_Trigger_List.begin(), Rebot::Potion_Pet_Summon_Trigger_List.end(), CurSlot->ItemInfo->GetItemData()->TID);

                    if(hp != Rebot::Potion_ObjID_HP_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->HP_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(mp != Rebot::Potion_ObjID_MP_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->MP_SLOT =  CurSlot->GetSlotInInventory();

                    }
                    if(vigor != Rebot::Potion_ObjID_Vigor_Potion_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->VIGOR_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(abnormal != Rebot::Potion_ObjID_Universal_Pill_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->ABNORMAL_SLOT =  CurSlot->GetSlotInInventory();

                    }
                    if(speed != Rebot::Speed_Scroll_ItemID.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SPEEDITEM_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->SPEED_SLOT =  CurSlot->GetSlotInInventory();

                    }

                    if(pet_hp != Rebot::Potion_Pet_HP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(pet_hp != Rebot::Potion_Pet_HP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_RIDDING_TRADE_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HP_RIDDING_TRADE_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(pet_hgp != Rebot::Potion_Pet_HGP_Tid_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HGP_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_HGP_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(pet_cure != Rebot::Potion_Pet_Cure_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_CURE_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_CURE_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(pet_resurrect != Rebot::Potion_Pet_Resurrect_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_RESURRECT_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_RESURRECT_SLOT =  CurSlot->GetSlotInInventory();
                    }
                    if(pet_trigger != Rebot::Potion_Pet_Summon_Trigger_List.end() && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->IsVisible())
                    {
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->ItemInfo = CurSlot->ItemInfo;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->FUN_006871d0(CurSlot->ItemInfo);
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_TRIGGER_ID=CurSlot->ItemInfo->GetItemData()->m_id;
                        g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->PET_TRIGGER_SLOT =  CurSlot->GetSlotInInventory();
                    }
                }
            }

        }
    }


    if(g_pCGInterface  && message == WM_RBUTTONDOWN)
    {
        if(!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp"))
        {
            if(g_CurrentIfUnderCursor->UniqueID()==6678)
            {

                if (g_pCGInterface->GetCharInfoGUI()->m_slot->ItemInfo && g_pCGInterface->GetCharInfoGUI()->m_slot->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCharInfoGUI()->m_slot->ItemInfo,g_pCGInterface->GetCharInfoGUI()->m_slot);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7777)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot1->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot1->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot1->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot1);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7778)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot2->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot2->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot2->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot2);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7779)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot3->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot3);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7780)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot4->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot4);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7880)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot5->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot5->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot5->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot5);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7881)
            {

                if (g_pCGInterface->GetExtraFeatureGUI()->m_slot6->ItemInfo && g_pCGInterface->GetExtraFeatureGUI()->m_slot6->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetExtraFeatureGUI()->m_slot6->ItemInfo,g_pCGInterface->GetExtraFeatureGUI()->m_slot6);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7781)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot1);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7782)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot2);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7783)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot3);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7784)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot4);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7785)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot5);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7786)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot6);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7787)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot7);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7788)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot8);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7789)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot9);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7790)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot10);
                }
            }
            if(g_CurrentIfUnderCursor->UniqueID()==7791)
            {

                if (g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->ItemInfo && g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->ItemInfo != NULL) {

                    g_pCGInterface->GetCharInfoGUI()->Showbuble(g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11->ItemInfo,g_pCGInterface->GetCIFSTMacroAutoHuntGUI()->m_slot11);
                }
            }
        }

    }

        /* if (GetActiveWindow() == Rebot::GameHWND) {


             if (KEY_DOWN(VK_RBUTTON) && (time(NULL) - lastClickTime > 1)) {
                 lastClickTime = time(NULL);
                 if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp")) {

                     CIFSlotWithHelp* CurSlot = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;


                     int GetParentWindow = CurSlot->GetParentWindowId();
                     if (GetParentWindow == 70)
                     {
                         CSOItem* myitem11=CurSlot->ItemInfo;;

                         printf("GetParentWindowId:%d\n", GetParentWindow ); /// 70 inventory - 71 equipment
                         if(CurSlot->ItemInfo) {

                             int SlotID = CurSlot->GetSlotInInventory() + 0xD;
                             NEWMSG(0x180B)
                                 pReq << SlotID << myitem11->GetObjectData()->ObjID;
                             SENDMSG()

                         }
                     }


                 }
             }

             if (KEY_DOWN(VK_LCONTROL)) {

                 if (KEY_DOWN(VK_LBUTTON)&&(time(NULL)- lastClickTime>0.7)) {
                     lastClickTime = time(NULL);
                     if (!strcmp(g_CurrentIfUnderCursor->GetRuntimeClass()->m_lpszClassName, "CIFSlotWithHelp")) {
                         CIFSlotWithHelp* CurSlot = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;

                         CSOItem *myitem11 = CurSlot->ItemInfo;

                         int GetParentWindow = CurSlot->GetParentWindowId();
                         if (GetParentWindow == 70 && CurSlot->ItemInfo) {
                             CIFWholeChat* chatView = (CIFWholeChat*)g_pCGInterface->m_IRM.GetResObj(56, 1);
                             CIFWnd *WholeChat = (CIFWnd *) g_pCGInterface->m_IRM.GetResObj(56, 1);
                             const wchar_t *ItemName = g_CTextStringManager->GetStringTextByCode(myitem11->GetObjectData()->ObjNameStrID.c_str())->c_str();
                             wchar_t* NewMsg = new wchar_t[1024];
                             int SlotID = CurSlot->GetSlotInInventory() + 0xD;

                             CSOItem *this_03 = g_pCGInterface->GetMainPopup()->GetInventory()->GetItemBySlot(CurSlot->GetSlotInInventory());

                             if(WholeChat && WholeChat->IsVisible())
                             {


     //                            RECT rect = { 0,0, 32,32 };
     //                            if (!chatView->m_slowithhelp) {
     //                                chatView->m_slowithhelp = (CIFSlotWithHelp*)g_pCGInterface->CreateInstance(g_pCGInterface, GFX_RUNTIME_CLASS(CIFSlotWithHelp), rect, 5000, 0);
     //                                chatView->m_slowithhelp->ShowGWnd(true);
     //                            }
     //                            chatView->m_slowithhelp->MoveGWnd(WholeChat->GetPos().x + 360, WholeChat->GetPos().y + 47);

                                 wsprintfW(NewMsg, L"%s<%s>", chatView->m_InputBox->GetText(), ItemName);
                                 chatView->m_InputBox->SetText(NewMsg);
                                 chatView->SetFocus_MAYBE();
                                 chatView->m_InputBox->SetFocus_MAYBE();
                                 std::n_wstring ItemNameW = std::n_wstring(ItemName);
                                 UINT16 Size = ItemNameW.length();
                                 //chatView->m_slowithhelp->FUN_006871d0(myitem11);
                                 NEWMSG(0x180C)
                                     pReq.Write(&Size, 2);
                                     pReq.Write(ItemName, Size * 2);
                                     pReq.Write(&SlotID, 1);
                                     pReq << *this_03;
                                 SENDMSG()
                             }
                             else
                             {

                                 CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
                                 wsprintfW(NewMsg, L"%s<%s>", chatView->m_InputBox->GetText(), ItemName);
                                 chatView->m_InputBox->SetText(NewMsg);
                                 chatView->SetFocus_MAYBE();
                                 chatView->m_InputBox->SetFocus_MAYBE();
                                 std::n_wstring ItemNameW = std::n_wstring(ItemName);
                                 UINT16 Size = ItemNameW.length();

                                 NEWMSG(0x180C)
                                     pReq.Write(&Size, 2);
                                     pReq.Write(ItemName, Size * 2);
                                     pReq.Write(&SlotID, 1);
                                     pReq <<*CurSlot->ItemInfo;
                                 SENDMSG()
                             }


                         }
                     }
                 }

        }*/



    // Only pass events if imgui wants it
    if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
        return RESULT_DISCARD; //0x199A

    return RESULT_PASS; //0x199B
}

void ImGui_OnPreSetSize(int width, int height) {
    BS_DEBUG_LOW("ImGui_OnPreSetSize");
    ImGui_ImplDX9_InvalidateDeviceObjects();
}

void ImGui_OnPostSetSize(int width, int height) {
    BS_DEBUG_LOW("ImGui_OnPostSetSize");
    //ImGui_ImplDX9_CreateDeviceObjects();
    ImGui_ImplDX9_Init(g_CD3DApplication->m_pd3dDevice);
}
