#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <iostream>
#include <vector>


//#include <stdint.h>
#include <assert.h>



#define X_DEBUG TRUE

//Assembly mnemonics
#define ASM_NOP 0x90
#define ASM_JMP 0xE9 //LONG
#define ASM_CALL 0xE8 //LONG