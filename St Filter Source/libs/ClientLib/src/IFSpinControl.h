#pragma once

#include "IFWnd.h"
#include "IFButton.h"

class CIFSpinControl : public CIFWnd {

GFX_DECLARE_DYNCREATE(CIFSpinControl)
GFX_DECLARE_MESSAGE_MAP(CIFSpinControl)

public:
    CIFSpinControl(void);
    ~CIFSpinControl(void);

    /// \address 00658010
    void SetMaxValue(int value);

    /// \address 00658020
    int GetMaxValue() const;

    /// \address 00658030
    void SetMinValue(int value);

    /// \address 00658040
    int GetMinValue() const;

    /// \address 00658050
    void SetCurrentValue(int value);

    /// \address 00658060
    int GetCurrentValue() const;

    /// \address 006581a0
    bool OnCreate(long ln) override;

private:

    /// \address 00658120
    void OnPrev();

    /// \address 00658160
    void OnNext();

    /// \address 00657fb0
    void UpdateText();

private:
    CIFButton* m_buttonPrev;
    CIFButton* m_buttonNext;
    CIFStatic* m_text;

    int m_valueMax;
    int m_valueMin;
    int m_valueCurrent;
    int m_ChestPage;
    int m_uniquelogpage;
    int m_Ranklogpage;
    int m_EventPage;
    int m_PointPage;
    int m_XsmbLichSuPage;
    int m_CustomNpcPage;
    int m_SkillBuffPage;
};