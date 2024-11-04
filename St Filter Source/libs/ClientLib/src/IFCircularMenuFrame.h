#pragma once
#include "IFDecoratedStatic.h"

class CIFCircularMenuFrame : public CIFDecoratedStatic{
GFX_DECLARE_DYNCREATE(CIFCircularMenuFrame)

public:
    bool OnCreate(long ln) override;
    void OnCIFReady() override;
    void SetIcon(std::n_string str);
};
