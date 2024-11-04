#include "ifwnd.h"

class CIFSliderCtrl: public CIFWnd
{
GFX_DECLARE_DYNAMIC_EXISTING(CIFSliderCtrl, 0x00EE9948)
public:
    char pad_0x36c[0x388-0x36c];
    int m_SliderMaxVol; // 0x388
    int m_SliderCurrentVol; // 0x38c
    char pad_0x390[0x3cc-0x38c-4];

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x3cc)
        ENSURE_OFFSET(m_SliderMaxVol, 0x388)
        ENSURE_OFFSET(m_SliderCurrentVol, 0x38c)
    END_FIXTURE()
    RUN_FIXTURE(CIFSliderCtrl)
};

