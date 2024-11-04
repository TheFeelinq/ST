#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN01 13379
class CIFTaiXiu : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFTaiXiu)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
