
#include "BSLib/BSLib.h"
class CICCos
{
public:
    void OnRender();
    char pad_0000[248]; //0x0000
    unsigned int UniqueID; //0x00F8
    char pad_00FC[20]; //0x00FC
    std::wstring cosname;//0x0110
    char pad_012C[12]; //0x012C
    unsigned int cosnamebackgroundcolor; //0x0138
    unsigned int cosnameforegroundcolor; //0x013C
    char pad_0140[784]; //0x0140
    unsigned int CurrentHP; //0x0450
    //char pad_0454[4]; //0x0454
    unsigned int MaxHP; //0x0454

BEGIN_FIXTURE()
        ENSURE_OFFSET(UniqueID, 0x00F8)
        ENSURE_OFFSET(cosname, 0x0110)
        ENSURE_OFFSET(cosnamebackgroundcolor, 0x0138)
        ENSURE_OFFSET(cosnameforegroundcolor, 0x013C)
        ENSURE_OFFSET(CurrentHP, 0x0450)
        ENSURE_OFFSET(MaxHP, 0x0454)
    END_FIXTURE()

    RUN_FIXTURE(CICCos)
}; //size 0x838