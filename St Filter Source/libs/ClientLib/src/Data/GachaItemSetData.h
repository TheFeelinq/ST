//
// Created by Admin on 15/7/2022.
//

#include <BSLib/_internal/custom_stl.h>
#include "BSLib/multibyte.h"
class CGachaItemSetData {

public:
    bool m_bService; //0x0000
    BYTE m_byItemPack; //0x0001
    int m_dwRefItemId; //0x0004
    short m_wRatio; //0x0008
    int m_dwItemCount; //0x000C
    int m_dwGhachaId; //0x0010
    bool m_bVisible; //0x0014
    int m_dwParam1; //0x0018
    int m_dwParam2; //0x001c
    int m_dwParam3; //0x0020
    int m_dwParam4; //0x0024
    char pad_002C[0x002C-0x0028];
   // CGachaFreeParam *m_pFreeParam; //0x0028
    std::n_vector<std::n_wstring> m_vecParamsDesc; //0x002C

BEGIN_FIXTURE()
        ENSURE_OFFSET(m_byItemPack, 0x0001)
        ENSURE_OFFSET(m_dwRefItemId, 0x0004)
        ENSURE_OFFSET(m_dwParam4, 0x0024)
        ENSURE_OFFSET(m_vecParamsDesc, 0x002C)
    END_FIXTURE()
    RUN_FIXTURE(CGachaItemSetData)
};
