#pragma once

#include <iostream>
#include <Windows.h>

//Remove on production
#define Z_DEBUG

#define SR_VT_V188
//#define SR_BR_100

#define ASM_NOP 0x90
#define ASM_JMP 0xE9
#define ASM_CALL 0xE8

#define HW_WNDPROC_TIMER_ID 0x1337

//===========================================
//Vietnam-v188 specific build defines
#ifdef SR_VT_V188
#define HW_SEND_HOOK		0x008416D2
#define HW_SEND_ECX			0x00EECBF4
#define HW_SEND_CALL		0x0081E750
#define HW_WNDPROC_HOOK		0x008311C4

#endif
//============================================
//Blackrogue-v100 specific build defines
#ifdef SR_BR_100
#define HW_SEND_HOOK		0x007EBA72
#define HW_SEND_ECX			0x00E507CC
#define HW_SEND_CALL		0x007CA080
#define HW_WNDPROC_HOOK		0x007DB894
#endif

#include "utility.h"
#include "CPacket.h"