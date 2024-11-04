//
// Created by Admin on 19/4/2022.
//

#ifndef SRO_DEVKIT_IFPETMINIINFO_H
#define SRO_DEVKIT_IFPETMINIINFO_H


#include "IFWnd.h"
#include "IFStatic.h"
#include "IFGauge.h"

class CIFPetMiniInfo  : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFPetMiniInfo, 0x00EEC228)


public:
    char pad_0x36c[0x0380-0x036c];
    int m_petUniqueID; // 0x0380
    char pad_0x384[0x4];
    CIFStatic *m_petName; //0x0388
    CIFStatic *m_petLevel; //0x038c
    CIFGauge *m_petHp; //0x0390
    CIFGauge *m_petHGP; //0x0394
    char pad_0x398[0x3a4-0x398];
BEGIN_FIXTURE()
        ENSURE_SIZE(0x3a4)
        ENSURE_OFFSET(m_petUniqueID, 0x0380)
        ENSURE_OFFSET(m_petName, 0x0388)
        ENSURE_OFFSET(m_petLevel, 0x038c)
        ENSURE_OFFSET(m_petHp, 0x0390)
        ENSURE_OFFSET(m_petHGP, 0x0394)
    END_FIXTURE()

    RUN_FIXTURE(CIFPetMiniInfo)

}; //0x3a4


#endif //SRO_DEVKIT_IFPETMINIINFO_H
