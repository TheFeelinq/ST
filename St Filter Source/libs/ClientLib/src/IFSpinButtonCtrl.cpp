#include "IFSpinButtonCtrl.h"

int CIFSpinButtonCtrl::GetMinValue() const {
    return m_valueMin;
}

void CIFSpinButtonCtrl::SetMinValue(int newValue) {
    m_valueMin = newValue;
}

int CIFSpinButtonCtrl::GetMaxValue() const {
    return m_valueMax;
}

void CIFSpinButtonCtrl::SetMaxValue(int newValue) {
    m_valueMax = newValue;
}

int CIFSpinButtonCtrl::GetCurrentValue() const {
    return m_valueCurrent;
}

void CIFSpinButtonCtrl::SetCurrentValue(int newValue) {
    m_valueCurrent = newValue;
}
