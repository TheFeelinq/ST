#include "BSLib/BSLib.h"
#include "IFButton.h"
#include "IFMainFrame.h"

//#define g_pCIFMessageBox (*(CIFMessageBox**)0x00ee95a0)
class CIFMessageBox : public CIFMainFrame
{



public:
    void SetGWndSizeIMPL(int width, int height);
    void CreateReverse(int wndID, int slot);
    void ShowGWndIMPL(bool bVisible);
public:
    char pad_0000[0x0804- sizeof(CIFMainFrame)]; //0x0000

    CIFButton* IFBtnCancel; //0x0804
    CIFButton* IFBtnDeath; //0x0808
    CIFButton* IFBtnReverse; //0x080C
    CIFButton* IFCustomButton; //0x0810

private:
BEGIN_FIXTURE()

        ENSURE_OFFSET(IFBtnCancel, 0x0804)
        ENSURE_OFFSET(IFBtnDeath, 0x0808)
        ENSURE_OFFSET(IFBtnReverse, 0x080C)
        ENSURE_OFFSET(IFCustomButton, 0x0810)
    END_FIXTURE()

    RUN_FIXTURE(CIFMessageBox)

}; //Size: 0x1438
extern CIFMessageBox* ReverseWindow;