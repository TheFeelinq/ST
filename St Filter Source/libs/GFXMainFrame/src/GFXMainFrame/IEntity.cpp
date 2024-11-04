#include "IEntity.h"
#include <remodel/StaticAddressHook.h>

GFX_IMPLEMENT_RUNTIMECLASS_EXISTING(CIEntity, 0x0110f86c);

CLASSLINK_STATIC_IMPL(CIEntity)

#ifdef CIENTITY_CLASSLINK_HOOK
// CClassLink<class_CIEntity>::CClassLink
//00b9393d 39 15 10 7d ed 00      CMP        dword ptr [head.bLinkingEnabled],EDX             = null
HOOK_ORIGINAL_STATIC(0x00b9393f, &CClassLink<CIEntity>::head.doLink)
//00b9394d 01 0d 14 7d ed 00      ADD        dword ptr [head.count],this                      = null
HOOK_ORIGINAL_STATIC(0x00b9394f, &CClassLink<CIEntity>::head.count)
//00b93953 39 15 18 7d ed 00      CMP        dword ptr [head.begin],EDX                       = null
HOOK_ORIGINAL_STATIC(0x00b93955, &CClassLink<CIEntity>::head.begin)
//00b9395b a3 18 7d ed 00         MOV        [head.begin],EAX                                 = null
HOOK_ORIGINAL_STATIC(0x00b9395c, &CClassLink<CIEntity>::head.begin)
//00b93960 a3 1c 7d ed 00         MOV        [head.end],EAX                                   = null
HOOK_ORIGINAL_STATIC(0x00b93961, &CClassLink<CIEntity>::head.end)
//00b9396c 8b 0d 1c 7d ed 00      MOV        this,dword ptr [head.end]                        = null
HOOK_ORIGINAL_STATIC(0x00b9396e, &CClassLink<CIEntity>::head.end)
//00b93975 a3 1c 7d ed 00         MOV        [head.end],EAX                                   = null
HOOK_ORIGINAL_STATIC(0x00b93976, &CClassLink<CIEntity>::head.end)

//  CClassLink<class_CIEntity>::~CClassLink()
// 00b938ca 3b 0d 20 7d ed 00      CMP        ECX,dword ptr [head.cursor]                      = null
HOOK_ORIGINAL_STATIC(0x00b938cc, &CClassLink<CIEntity>::head.cursor)
// 00b938d9 09 05 24 7d ed 00      OR         dword ptr [head.cursorInvalidated],EAX           = null
HOOK_ORIGINAL_STATIC(0x00b938db, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00b938df 89 35 20 7d ed 00      MOV        dword ptr [head.cursor],ESI                      = null
HOOK_ORIGINAL_STATIC(0x00b938e1, &CClassLink<CIEntity>::head.cursor)
// 00b938e5 29 05 14 7d ed 00      SUB        dword ptr [head.count],EAX                       = null
HOOK_ORIGINAL_STATIC(0x00b938e7, &CClassLink<CIEntity>::head.count)
// 00b938fd a3 18 7d ed 00         MOV        [head.begin],EAX                                 = null
HOOK_ORIGINAL_STATIC(0x00b938fe, &CClassLink<CIEntity>::head.begin)
// 00b9391a a3 1c 7d ed 00         MOV        [head.end],EAX                                   = null
HOOK_ORIGINAL_STATIC(0x00b9391b, &CClassLink<CIEntity>::head.end)

// CEntityManager::Func_10()
// 00ba2570 a1 18 7d ed 00         MOV        EAX,[head.begin]
HOOK_ORIGINAL_STATIC(0x00ba2571, &CClassLink<CIEntity>::head.begin)
// 00ba2575 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe
//          fe
HOOK_ORIGINAL_STATIC(0x00ba2577, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba257e a3 20 7d ed 00         MOV        [head.cursor],EAX
HOOK_ORIGINAL_STATIC(0x00ba257f, &CClassLink<CIEntity>::head.cursor)
// 00ba259f a1 20 7d ed 00         MOV        EAX,[head.cursor]
HOOK_ORIGINAL_STATIC(0x00ba25a0, &CClassLink<CIEntity>::head.cursor)
// 00ba25a4 f6 05 24 7d ed 00      TEST       byte ptr [head.cursorInvalidated],0x1
HOOK_ORIGINAL_STATIC(0x00ba25a6, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba25ad 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe
HOOK_ORIGINAL_STATIC(0x00ba25af, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba25b9 a3 20 7d ed 00         MOV        [head.cursor],EAX
HOOK_ORIGINAL_STATIC(0x00ba25ba, &CClassLink<CIEntity>::head.cursor)

// CEntityManager::Func_11()
// 00ba24c0 a1 18 7d ed 00         MOV        EAX,[head.begin]                                 = null
HOOK_ORIGINAL_STATIC(0x00ba24c1, &CClassLink<CIEntity>::head.begin)
// 00ba24c5 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe    = null
HOOK_ORIGINAL_STATIC(0x00ba24c7, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba24d4 a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x00ba24d5, &CClassLink<CIEntity>::head.cursor)
// 00ba253c a1 20 7d ed 00         MOV        EAX,[head.cursor]                                = null
HOOK_ORIGINAL_STATIC(0x00ba253d, &CClassLink<CIEntity>::head.cursor)
// 00ba2544 f6 05 24 7d ed 00      TEST       byte ptr [head.cursorInvalidated],0x1            = null
HOOK_ORIGINAL_STATIC(0x00ba2546, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba254d 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe    = null
HOOK_ORIGINAL_STATIC(0x00ba254f, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba2559 a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x00ba2550, &CClassLink<CIEntity>::head.cursor)

// CEntityManager::Func_9()
// 00ba34f2 a1 18 7d ed 00         MOV        EAX,[head.begin]                                 = null
HOOK_ORIGINAL_STATIC(0x00ba34f3, &CClassLink<CIEntity>::head.begin)
// 00ba34fc 21 3d 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],EDI           = null
HOOK_ORIGINAL_STATIC(0x00ba34fe, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba3508 a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x00ba3509, &CClassLink<CIEntity>::head.cursor)
// 00ba351e a1 20 7d ed 00         MOV        EAX,[head.cursor]                                = null
HOOK_ORIGINAL_STATIC(0x00ba351f, &CClassLink<CIEntity>::head.cursor)
// 00ba3523 f6 05 24 7d ed 00      TEST       byte ptr [head.cursorInvalidated],0x1            = null
HOOK_ORIGINAL_STATIC(0x00ba3525, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba352c 21 3d 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],EDI           = null
HOOK_ORIGINAL_STATIC(0x00ba352e, &CClassLink<CIEntity>::head.cursorInvalidated)
// 00ba3537 a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x00ba3538, &CClassLink<CIEntity>::head.cursor)

// CEntityManagerClient::Func_11
// 009c4770 a1 18 7d ed 00         MOV        EAX,[head.begin]                                 = null
HOOK_ORIGINAL_STATIC(0x009c4771, &CClassLink<CIEntity>::head.begin)
// 009c4775 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe    = null
HOOK_ORIGINAL_STATIC(0x009c4777, &CClassLink<CIEntity>::head.cursorInvalidated)
// 009c4784 a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x009c4785, &CClassLink<CIEntity>::head.cursor)
// 009c4830 a1 20 7d ed 00         MOV        EAX,[head.cursor]                                = null
HOOK_ORIGINAL_STATIC(0x009c4831, &CClassLink<CIEntity>::head.cursor)
// 009c4835 f6 05 24 7d ed 00      TEST       byte ptr [head.cursorInvalidated],0x1            = null
HOOK_ORIGINAL_STATIC(0x009c4837, &CClassLink<CIEntity>::head.cursorInvalidated)
// 009c483e 83 25 24 7d ed 00      AND        dword ptr [head.cursorInvalidated],0xfffffffe    = null
HOOK_ORIGINAL_STATIC(0x009c4840, &CClassLink<CIEntity>::head.cursorInvalidated)
// 009c484a a3 20 7d ed 00         MOV        [head.cursor],EAX                                = null
HOOK_ORIGINAL_STATIC(0x009c484b, &CClassLink<CIEntity>::head.cursor)

#endif

CIEntity::CIEntity() {
    field_0x50 = 0;
    field_0x30 = DAT_0110f864;
    field_0x50 = DAT_0110f860;
    DAT_0110f864 = 0;
    DAT_0110f860 = 0;
    field_0x38 = 0;
    field_0x3c = 0;
    field_0x44 = 0;
    field_0x4c = 0;
    field_0x48 = 0;
    field_0x40 = 1;
}

CIEntity::~CIEntity() {
    /// \todo Delete some pointer here
}

void CIEntity::Func_7(undefined4 param1) {
    // empty
}

void CIEntity::OnRelease() {
    // empty
}

void CIEntity::Func_9() {
    // empty
}

void CIEntity::Func_10() {
    // empty
}

void CIEntity::Func_11() {
    /// \todo Reconstruct CIEntity::Func_11 from 00b946a0
    reinterpret_cast<void (__thiscall *)(CIEntity *)>(0x00b946a0)(this);
}

undefined1 CIEntity::Func_12(undefined4 param1) {
    return 1;
}

undefined4 CIEntity::Func_13(undefined4 param1, undefined4 param2) {
    return 0;
}