#pragma once

#include "ICharactor.h"

class CICNonuser : public CICharactor {
    friend CClassLink<CICNonuser>; // 00ec4d8c

GFX_DECLARE_DYNAMIC_EXISTING(CICNonuser, 0x00ef1aa4)

public:
    /// \address 009d4280
    CICNonuser();

    // Destructor is default
    // \address 009d4330
    // ~CICNonuser();
private:

    CClassLink<CICNonuser> m_classLink; // 0x078c

BEGIN_FIXTURE()
        ENSURE_SIZE(0x79c)
        ENSURE_OFFSET(m_classLink, 0x78c)
    END_FIXTURE()

    RUN_FIXTURE(CICNonuser)
};