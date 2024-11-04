#pragma once
#include "SOItem.h"
#include "IFHelperBubbleWindow.h"
#include "IFDecoratedStatic.h"


class CIFSlotWithHelpForPackage {
    char pad_0000[912]; //0x0000
    CSOItem* _CSOItem; //0x0390
public:
    void ChangeColorPrice(class CIFHelperBubbleWindow* window);

};



