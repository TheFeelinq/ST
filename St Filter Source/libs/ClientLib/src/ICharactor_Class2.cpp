#include <cstddef>
#include "ICharactor_Class2.h"

CICharactor_Class2::CICharactor_Class2() {
    field_0x28 = 0.0;
    field_0x24 = 0.0;
    field_0x14 = 0;
    field_0x20 = 0.0;
    field_0x18 = 0;
    field_0x1c = 0;
    field_0x44 = 0.0;
    field_0x40 = 0.0;
    field_0x30 = 0;
    field_0x3c = 0.0;
    field_0x34 = 0;
    field_0x38 = 0;
    field_0x60 = 0.0;
    field_0x5c = 0.0;
    field_0x4c = 0;
    field_0x58 = 0.0;
    field_0x50 = 0;
    field_0x54 = 0;
    field_0x8c = 1.0;
    m_referencedObject = NULL;
    field_0x90 = 0;
    field_0xc = 0;
    field_0x94 = 0;
    field_0xb0 = 0.0;
    field_0x98 = 0;
    field_0xa8 = 0.0;
    field_0x9c = 0;
    field_0x64 = 0.0;
    field_0xa0 = 0;
    field_0xa4 = 0;
}

void CICharactor_Class2::SetReferencedObject_MAYBE(CICharactor *referencedObject) {
    m_referencedObject = referencedObject;
    field_0x10 = 0;
    field_0x80 = 0;
    field_0x88 = 0;
    field_0xac = 0;
    field_0x84 = 0;
}