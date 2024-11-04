#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN06 13386
class CIFSTChestIcon : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFSTChestIcon)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
