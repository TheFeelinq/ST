#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN05 13383
class CIFDailyLoginIcon : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFDailyLoginIcon)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
