#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FLORIAN08 13385
class CIFSTStremSettingIcon : public CIFDecoratedStatic
{
    GFX_DECLARE_DYNCREATE(CIFSTStremSettingIcon)

public:
    bool OnCreate(long ln) override;

    int OnMouseLeftUp(int a1, int x, int y) override;

    void OnCIFReady() override;


};
