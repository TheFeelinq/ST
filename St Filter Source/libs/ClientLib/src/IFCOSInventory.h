//
// Created by Admin on 5/4/2022.
//

#ifndef SRO_DEVKIT_IFCOSINVENTORY_H
#define SRO_DEVKIT_IFCOSINVENTORY_H


#include "IFFrame.h"
#include "IFSlotWithHelp.h"
#include "IFSpinButtonCtrl.h"

class CIFCOSInventory : public CIFFrame {
GFX_DECLARE_DYNAMIC_EXISTING(CIFCOSInventory, 0x00EEC0C8)


public:
    int m_TotalTab; //0x7b0
    int m_CurentSelectTab; //0x7b4
    int m_UniqueID; //0x7b8
    char pad_0x7bc[4] ; //0x7bc
    int m_TotalSlot; //0x7c0
    CIFSlotWithHelp *m_slots[28]; //0x7c4
    CIFStatic *m_NameOfTab; // 0x834
    char pad_0x838[0x34] ; //0x838
    CIFSpinButtonCtrl *m_SpinButton; //0x86c

BEGIN_FIXTURE()
        ENSURE_SIZE(0x870)
        ENSURE_OFFSET(m_TotalTab, 0x7b0)
        ENSURE_OFFSET(m_CurentSelectTab, 0x7b4)
        ENSURE_OFFSET(m_UniqueID, 0x7b8)
        ENSURE_OFFSET(m_TotalSlot, 0x7c0)
        ENSURE_OFFSET(m_slots, 0x7c4)
        ENSURE_OFFSET(m_NameOfTab, 0x834)
        ENSURE_OFFSET(m_SpinButton, 0x86c)
    END_FIXTURE()

    RUN_FIXTURE(CIFCOSInventory)
}; //size 0x870


#endif //SRO_DEVKIT_IFCOSINVENTORY_H
