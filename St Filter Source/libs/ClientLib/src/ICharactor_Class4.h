#pragma once

#include <ghidra/undefined.h>

struct CICharactor_Class4_ctor_param {
    CICharactor_Class4_ctor_param(float f1, float f2) {
        field_0 = f1;
        field_4 = f2;
    }

    float field_0;
    float field_4;
};

class CICharactor_Class4 {
public:
    explicit CICharactor_Class4(const CICharactor_Class4_ctor_param &values);

private:
    float field_0x0;
    float field_0x4;
    float field_0x8;
    float field_0xc;
    float field_0x10;
    float field_0x14;
    float field_0x18;
    float field_0x1c;
    undefined4 field_0x20;
    float field_0x24;
};