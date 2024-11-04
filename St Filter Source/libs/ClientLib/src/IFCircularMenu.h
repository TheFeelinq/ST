#pragma once
#include "IFMainFrame.h"
#include "IFDecoratedStatic.h"
#include "IFCircularMenuFrame.h"
#include "IFCircularMenuSlot.h"

#define PI 3.14159265

class CIFCircularMenu : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFCircularMenu)
GFX_DECLARE_MESSAGE_MAP(CIFCircularMenu)

public:
    CIFCircularMenu(void);
    ~CIFCircularMenu(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;

private:
    int OnKeyUp(UINT nChar, UINT a2, UINT a3);
    int OnVisibleStateChange(int a1, int a2);
    void UpdateSlopeAngle(int x, int y);
    void RegisterMenuSlot(std::n_string icon, std::n_wstring title, std::n_wstring description);
    void WrapSlots();
    void DrawCircularMenu();
    void SetFocusedSlot(int slotId);
    void SlotCallbackMethod(int slotId);

private:
    CIFStatic* m_overlay;
    CIFCircularMenuFrame* m_circularFrame;
    CIFStatic* m_circularArrow;
    CIFStatic* m_slotTitle;
    CIFStatic* m_slotDescription;
    CIFCircularMenuSlot** m_pSlots;

private:
    static const int maxSlots = 20;
    static const int slotFirstId = 100;

    POINT screenCenterPoint;
    int m_lastAngle;
    int m_selectedSlotId;
    int m_aSlotCount;
};


