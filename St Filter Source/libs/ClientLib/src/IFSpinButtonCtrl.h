#pragma once

#include "IFWnd.h"
#include "IFStatic.h"
#include "IFButton.h"

class CIFSpinButtonCtrl : public CIFWnd
{
    public:
    /// \brief Get the minimum value for this control
    /// \address 00658040
    int GetMinValue() const;

    /// \brief Set the minimum value for this control
    /// \address 00658030
    void SetMinValue(int newValue);

    /// \brief Get the maximum value for this control
    /// \address 00658020
    int GetMaxValue() const;

    /// \brief Set the maximum value for this control
    /// \address 00658010
    void SetMaxValue(int newValue);

    /// \brief Get the current value for this control
    /// \address 00658060
    int GetCurrentValue() const;

    /// \brief Set the current value for this control
    /// \note Setting this value does not trigger any updates. Just setting the
    ///       value will likely not change anything.

    /// \address 00658050
    void SetCurrentValue(int newValue);



private:
    CIFButton *m_pButtonPrev;
    CIFButton *m_pButtonNext;
    CIFStatic *m_pText;

    int m_valueMax;
    int m_valueMin;
    int m_valueCurrent;

BEGIN_FIXTURE()
        ENSURE_SIZE(0x384)
        ENSURE_OFFSET(m_pButtonPrev, 0x36c)
        ENSURE_OFFSET(m_pButtonNext, 0x370)
        ENSURE_OFFSET(m_pText, 0x374)
        ENSURE_OFFSET(m_valueMax, 0x378)
        ENSURE_OFFSET(m_valueMin, 0x37c)
        ENSURE_OFFSET(m_valueCurrent, 0x380)
    END_FIXTURE()

    RUN_FIXTURE(CIFSpinButtonCtrl)

};
