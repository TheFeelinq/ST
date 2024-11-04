#pragma once
#include <GInterface.h>

typedef HRESULT(APIENTRY* HookOnListChatThing)(int,int);
extern HookOnListChatThing hookOnListChatThing;
class ChatViewerItemAction {
public:
    /// \address 007A9970
    int HookOnListChatThing(int a2, int a3);
    static CIFSlotWithHelp* Slot;
};