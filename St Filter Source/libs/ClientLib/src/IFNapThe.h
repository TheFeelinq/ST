#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN03 13381
class CIFNapThe : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFNapThe)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
