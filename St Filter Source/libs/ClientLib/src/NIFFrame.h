

#include "NIFTileWnd.h"

class CNIFFrame : public CNIFTileWnd{

    GFX_DECLARE_DYNAMIC_EXISTING(CNIFFrame, 0x115DF28)

public:


    /// \address 00473670
    bool OnCreate(long ln) override;

    /// \address 004736a0
    void RenderMyself() override;

    /// \address 0046c330
   // void Func_49(std::n_string str) override;

BEGIN_FIXTURE()
        ENSURE_SIZE(0x78c)
    END_FIXTURE()
    RUN_FIXTURE(CNIFFrame)
};
