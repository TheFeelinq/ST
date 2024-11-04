#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN04 13382
class CIFDANGKYEVENT : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFDANGKYEVENT)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
