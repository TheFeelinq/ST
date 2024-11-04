

#include <ghidra/undefined.h>
#include "NIFWnd.h"

class CNIFDragableArea : public CNIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CNIFDragableArea, 0x115E0B0)
    GFX_DECLARE_DYNCREATE_FN(CNIFDragableArea)

private: /* members */
    undefined pad[16];

private: /* test fixture */
BEGIN_FIXTURE()
        ENSURE_SIZE(0x358)
    END_FIXTURE()

    RUN_FIXTURE(CNIFDragableArea)
};

