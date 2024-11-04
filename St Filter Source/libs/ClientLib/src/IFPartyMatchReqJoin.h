//
// Created by Admin on 21/12/2021.
//

#ifndef SRO_DEVKIT_IFPARTYMATCHREQJOIN_H
#define SRO_DEVKIT_IFPARTYMATCHREQJOIN_H


#include "IFFrame.h"
#include "IFButton.h"

class CIFPartyMatchReqJoin: public CIFFrame {
    GFX_DECLARE_DYNAMIC_EXISTING(CIFPartyMatchReqJoin, 0x00EEB92C)

    bool OnCreateIMPL(long ln);
    void OnUpdateIMPL();
    CIFButton* m_BlockBtn;
};


#endif //SRO_DEVKIT_IFPARTYMATCHREQJOIN_H
