#pragma once
#include "IFMainFrame.h"

class CIFCircularMenuSlot : public CIFWnd {

GFX_DECLARE_DYNCREATE(CIFCircularMenuSlot)
GFX_DECLARE_MESSAGE_MAP(CIFCircularMenuSlot)

public:
    CIFCircularMenuSlot(void);
    ~CIFCircularMenuSlot(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

private:
    int OnVisibleStateChange(int a1, int a2);

public:
    void SetIcon(std::n_string str);
    void SetPosition(int x, int y);
    void SetSlotId(int slotId);
    int GetSlotId();
    void SetTitle(std::n_wstring title);
    std::n_wstring GetTitle();
    void SetDescription(std::n_wstring description);
    std::n_wstring GetDescription();
    void SetFocus(bool shouldFocus);
    void SetFade(bool fadeIn);
    bool IsFocused();
    void OnSelect();

private:
    CIFStatic* m_slot;
    CIFStatic* m_icon;

private:
    int slotId;
    bool m_isFocused;
    std::n_wstring m_title;
    std::n_wstring m_description;
};
