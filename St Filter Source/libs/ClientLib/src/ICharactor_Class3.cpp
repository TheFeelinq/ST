#include "ICharactor_Class3.h"


CICharactor_Class3::CICharactor_Class3(const D3DXVECTOR3 &vector, float divider) {
    float fVar1;

    if (0.001f <= divider) {
        field_0x38 = divider;
        fVar1 = 1.0f / divider;
    } else {
        field_0x38 = 0.0f;
        fVar1 = 1.0f;
    }
    field_0x3c = fVar1;

    v2_source = vector;

    FUN_009c8ac0(vector);

    field_0x34 = 1.0;
    field_0x30 = 1;
}

void CICharactor_Class3::FUN_009c8ac0(const D3DVECTOR &vec) {
    field_0x30 = 0;
    field_0x34 = 0.0;

    v1 = vec;
    v2 = v2_source;

    // TODO: Consider using D3DXVECTOR instead. It has an operator- for this.
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
}