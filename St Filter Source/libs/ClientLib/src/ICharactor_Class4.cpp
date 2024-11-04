
#include "ICharactor_Class4.h"

CICharactor_Class4::CICharactor_Class4(const CICharactor_Class4_ctor_param &values) {
    field_0x0 = values.field_0;
    field_0x4 = values.field_4;
    field_0x20 = 0;
    field_0x10 = values.field_0;
    field_0x14 = values.field_4;
    field_0x24 = 0.0f;
    field_0x8 = field_0x0;
    field_0xc = field_0x4;
    field_0x18 = field_0x10 - field_0x8;
    field_0x1c = field_0x14 - field_0xc;
    field_0x24 = 1.0f;
    field_0x20 = 1;
}