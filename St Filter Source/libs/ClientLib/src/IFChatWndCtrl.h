

#include "BSLib/BSLib.h"
#include "IFChatViewer.h"

class CIFChatWndCtrl
{
public:
    char pad_0000[56]; //0x0000
    UINT32 Instance; //0x0038
    char pad_003C[44]; //0x003C
    CIFChatViewer* pCIFChatViewer; //0x0068
    char pad_006C[980]; //0x006C
}; //Size: 0x0440