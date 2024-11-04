#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <ghidra/undefined.h>


class CICharactor_Class3 {
public:
    /// \address 009c96c0
    CICharactor_Class3(const D3DXVECTOR3 &vector, float divider);

    /// \address 009c8ac0
    void FUN_009c8ac0(const D3DVECTOR &vec);

private:
    D3DVECTOR v2_source;
    D3DVECTOR v2;
    D3DVECTOR v1;
    D3DVECTOR result;
    undefined4 field_0x30;
    float field_0x34;
    float field_0x38;
    float field_0x3c;
};