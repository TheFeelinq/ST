//
// Created by Admin on 3/2/2022.
//

#ifndef SRO_DEVKIT_IFMAGICSTATEBOARD_H
#define SRO_DEVKIT_IFMAGICSTATEBOARD_H


#include "IFFrame.h"

class CIFMagicStateBoard: public CIFFrame {
    GFX_DECLARE_DYNAMIC_EXISTING(CIFMagicStateBoard, 0x00EEC928)

    bool OnCreateIMPL(long ln);
    void OnUpdateIMPL();
};

#endif //SRO_DEVKIT_IFMAGICSTATEBOARD_H
