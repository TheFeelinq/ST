
#include "IFFrame.h"
#include "IFButton.h"
//0x5B9580
class CNIFGuildWnd : public CIFFrame {
GFX_DECLARE_DYNAMIC_EXISTING(CNIFGuildWnd, 0xEE8750)

    bool OnCreateIMPL(long ln);
    void OnUpdateIMPL();
};

