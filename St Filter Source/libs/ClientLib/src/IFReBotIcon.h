#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN07 13384
class CIFReBotIcon : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFReBotIcon)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
