#include "ChatViewerItemAction.h"
#include <IFChatViewer.h>
#include <GlobalDataManager.h>
#include <Game.h>
#include <BSLib/multibyte.h>
#include "GameDataExt.h"
#include "Windows.h"
HookOnListChatThing hookOnListChatThing = NULL;
CIFSlotWithHelp* ChatViewerItemAction::Slot;
int ChatViewerItemAction::HookOnListChatThing(int a2, int a3) {

    CIFChatViewer* chatView = (CIFChatViewer*)g_pCGInterface->m_IRM.GetResObj(1, 1);
    int res = reinterpret_cast<int(__thiscall*)(CIFChatViewer*, int, int)>(hookOnListChatThing)(chatView, a2, a3);

    __asm {
            pushad
            pushfd
    }
    RECT rect = { 0,0, 0x28,0x28 };
    if (!Slot) {
        Slot = (CIFSlotWithHelp*)g_pCGInterface->CreateInstance(g_pCGInterface, GFX_RUNTIME_CLASS(CIFSlotWithHelp), rect, 5000, 0);
        Slot->ShowGWnd(false);
    }


    CIFListCtrl* pList = chatView->m_CurrentActiveChatlist;
    CIFListCtrl::SLineOfText* line;
    std::n_wstring str;
    int indexOffset = 0;
    int NameLine= *(int*)((int)pList + 0x374);
    std::n_wstring fullStr=L"";
    do
    {
        line = pList->GetTextByIndex(NameLine);
        printf("%p\r\n", line);
        if (!line)
            break;
        line->m_font->GetText(&str);
        if (str.empty())
            break;
        indexOffset++;
        NameLine = *(int*)((int)pList + 0x374) - indexOffset;

    } while (str.find(L":") == std::n_wstring::npos);

    NameLine += 1;
    line = pList->GetTextByIndex(NameLine);
    line->m_font->GetText(&str);
    std::string CharName = acp_encode(str.substr(0, str.find_first_of(L":")));
    indexOffset = 0;
    do
    {
        line = pList->GetTextByIndex(NameLine + indexOffset);
        if (!line)
            break;
        line->m_font->GetText(&str);
        if (str.empty())
            break;
        indexOffset++;
        fullStr = fullStr+str ;
    } while (str.find(L":") != std::n_wstring::npos);
    //printf("��ǰ��%d,��ʼ��%d\r\n", *(int*)((int)pList + 0x374), NameLine);
    std::string fullStrA=acp_encode(fullStr);
    int strViewLen = fullStrA.length();
   // printf("%s\r\n%d\r\n", fullStrA.c_str(), strViewLen);
    //printf("��ʾ���%dpx,�߶�5px,�ı�����:%d\r\n", strViewLen*6,strViewLen);
    RECT r1;
    GetWindowRect(theApp.GetHWnd(), &r1);
    POINT mMouse;
    GetCursorPos(&mMouse);
    int mStartX= mMouse.x - (r1.left + 29);
    int clickIndex= (mStartX + (*(int*)((int)pList + 0x374) - NameLine) * 350) / 6;
   // printf("����Ӧ�ַ��±�:%d\r\n", clickIndex);
    int startIndex=fullStrA.rfind("<", clickIndex);
    int endIndex = fullStrA.find_first_of(">", clickIndex);

    int errorStartIndex = fullStrA.rfind(">", clickIndex);
    int errorEndIndex = fullStrA.find_first_of("<", clickIndex);
    std::string ItemLinkName = fullStrA.substr(startIndex, endIndex - startIndex + 1);

    if (startIndex > errorStartIndex&& endIndex<errorEndIndex|| errorStartIndex== std::string::npos|| errorEndIndex==std::string::npos) {
        if (startIndex != std::string::npos && endIndex != std::string::npos) {
           // Slot->ItemInfo = &ChatItemInfoList[CharName + fullStrA.substr(startIndex, endIndex - startIndex + 1)];
            if (Slot->ItemInfo) {
                printf("%s,%d,%d,%p\r\n", (CharName + fullStrA.substr(startIndex, endIndex - startIndex + 1)).c_str(), startIndex, endIndex, Slot);

                int v2 = reinterpret_cast<DWORD(__stdcall*)()>(0x5CED70)();

                *((DWORD*)Slot->ItemInfo + 0x32) = v2;
                *(BYTE*)(v2 + 0x15) = 1;
                //*(DWORD*)(*((DWORD*)Slot->ItemInfo + 0x32) + 4) = *((DWORD*)Slot->ItemInfo + 0x32);
                **((DWORD**)Slot->ItemInfo + 0x32) = *((DWORD*)Slot->ItemInfo + 0x32);
                //*(DWORD*)(*((DWORD*)Slot->ItemInfo + 0x32) + 8) = *((DWORD*)Slot->ItemInfo + 0x32);
                //ItemInfo 0xA4
                //�㵽��Ʒ��Ϣ��
                POINT m_show_point;
                m_show_point.x = mMouse.x - (r1.left + 100);
                m_show_point.y = mMouse.y - r1.top;
                g_pCGInterface->m_helperWindow->ShowGWnd(true);
                (*(void(__thiscall**)(CIFTextBox*, int, int))(*(DWORD32*)(g_pCGInterface->m_helperWindow->m_textBox) + 0x54))(
                        g_pCGInterface->m_helperWindow->m_textBox,
                        0xC8,
                        1);

                g_pCGInterface->m_helperWindow->m_ownerWindow = Slot;

                g_pCGInterface->m_helperWindow->Reset();
                g_pCGInterface->N00002717->Reset();

                Slot->HelperBubbleInventoryAndEquipment(g_pCGInterface->m_helperWindow);
                //Slot->HelperBubbleInventoryAndEquipment(g_pCGInterface->m_helperWindow);

                g_pCGInterface->m_helperWindow->sub_777020();

                g_pCGInterface->m_helperWindow->MoveGWnd(m_show_point.x, m_show_point.y);
                g_pCGInterface->m_helperWindow->sub_776C00(&g_pCGInterface->m_helperWindow->GetBounds(), g_pCGInterface->m_helperWindow->N00000618);
                g_pCGInterface->m_helperWindow->BringToFront();

                g_pCGInterface->N00002717->sub_777020();
                g_pCGInterface->N00002717->MoveGWnd(m_show_point.x, m_show_point.y);
                g_pCGInterface->N00002717->sub_776C00(&g_pCGInterface->N00002717->GetBounds(), g_pCGInterface->N00002717->N00000618);
                g_pCGInterface->N00002717->BringToFront();
            }
        }
    }



/*        *(BYTE*)(Slot + 0x654) = 0;

        g_pCGInterface->N00002717->ShowGWnd(true);
        wchar_t* Dest = new wchar_t[100];
        wsprintfW(Dest, L"%s", g_pCICPlayer->GetCharName().c_str());
        std::n_wstring a = std::n_wstring(Dest);
        D3DCOLOR color = 0xFFFF00A0;
        g_pCGInterface->m_helperWindow->m_textBox->sub_64F8A0(a, g_pCGInterface->m_helperWindow->m_textBox->m_CurrentLines, color, color, -1, 0, 1);


        g_pCGInterface->N00002717->sub_776C00(&g_pCGInterface->N00002717->GetBounds(), g_pCGInterface->N00002717->N00000618);
        g_pCGInterface->N00002717->ShowGWnd(true);*/


    __asm {
            popfd
            popad
    }
    return res;
}