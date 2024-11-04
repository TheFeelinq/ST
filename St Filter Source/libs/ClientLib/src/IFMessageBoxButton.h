#include "BSLib/BSLib.h"

class CIFMessageBoxButton
{
public:
    char pad_0000[52]; //0x0000
    UINT32 ID; //0x0034
    bool isVisible; //0x0038
    char pad_0039[7]; //0x0039
    UINT32 XSec; //0x0040
    UINT32 YSec; //0x0044
    UINT32 Width; //0x0048
    UINT32 Height; //0x004C
    void SetGWndSize(int width, int height);
    void MoveGWnd(int x, int y);
    bool SetText(const wchar_t* src);

}; //Size: 0x1430