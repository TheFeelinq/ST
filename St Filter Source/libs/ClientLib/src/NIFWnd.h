#pragma once
#include "GFXMainFrame/GWnd.h"
#include "NIFTextBoard.h"

class CNIFWnd : public CGWnd , public CNIFTextBoard { // also CNIFTextBoard...
    //todo : reverse me in the future ^^?
GFX_DECLARE_DYNAMIC_EXISTING(CNIFWnd, 0x115DEA0)
GFX_DECLARE_MESSAGE_MAP(CNIFWnd)
public:
    CNIFWnd(void);

    ~CNIFWnd(void);
public:
    /* CNIFTextBoard override funcs...
   void NIFTB_Func_4() override;

   void NIFTB_Func_7() override;

   char NIFTB_Func_8() override;

   void NIFTB_Func_11() override; */
    CNIFWnd *LoadResObj(int Id);
    template<typename T>
    T *LoadResObj(int id) {
        return reinterpret_cast<T *(__thiscall *)(CNIFWnd *, int)>(0x0046e060)(this, id);
    }
    bool OnCreate(long ln) override;

    void OnUpdate() override;

    bool OnRelease() override;

    void RenderMyself() override;

    void OnWndMessage(Event3D *a1) override;

    bool Func_18(Event3D *a1) override;

    bool On3DEvent_MAYBE(Event3D *a2) override;

    void BringToFront() override;

    void SetGWndSize(int width, int height) override;

    void Func_22(int x, int y) override;

    void ShowGWnd(bool bVisible) override;

    void Func_37() override;

    virtual void MoveGWnd(int x, int y);

    virtual void MoveGWnd2(wnd_pos pos);

    virtual void Func_40();

    virtual void OnCIFReady();

    virtual void Func_42();

    virtual void OnCloseWnd();

    virtual void Func_44();

    virtual void Func_45();

    virtual bool IsInside(int x, int y);

    virtual bool SetText(const wchar_t *src);

    virtual const wchar_t *GetText();

    virtual void Func_49();

    void SetSomeRect(const RECT &rect);
private:
    int On4001(int, int);
    int On4006(int, int);
private:
    int N000005A9; //0x0188
    int m_current_style; //0x018C
    RECT m_someRECT; //0x0190
    std::n_wstring m_innerText; //0x01A0
    char pad[0x348 - (0x01A0+0x1c)];


BEGIN_FIXTURE()
        ENSURE_SIZE(0x348)
        ENSURE_OFFSET(N000005A9, 0x188)
        ENSURE_OFFSET(m_current_style, 0x018C)
        ENSURE_OFFSET(m_someRECT, 0x0190)
        ENSURE_OFFSET(m_innerText, 0x01A0)
    END_FIXTURE()
    RUN_FIXTURE(CNIFWnd)
};