#pragma once
#include <BSLib/BSLib.h>
#include "Test/Test.h"
#include <ghidra/undefined.h>
#include <ClassLink.h>

#define DAT_0110f860 (*(undefined4*)0x0110f860)
#define DAT_0110f864 (*(undefined4*)0x0110f864)
class CIEntity : public CObjChild {


private: /* members */
    CClassLink<CIEntity> m_classLink;
    undefined4 field_0x30;
    undefined field_0x34;
    undefined field_0x35;
    undefined field_0x36;
    undefined field_0x37;
    undefined4 field_0x38;
    undefined4 field_0x3c;
protected:
    undefined4 field_0x40;
private:
    undefined1 field_0x44;
    undefined field_0x45;
    undefined field_0x46;
    undefined field_0x47;
    undefined4 field_0x48;
    undefined4 field_0x4c;
    undefined4 field_0x50;

BEGIN_FIXTURE()
        ENSURE_SIZE(0x54)
    END_FIXTURE()

    RUN_FIXTURE(CIEntity)
};
