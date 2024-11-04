#pragma once
#ifndef HG_CENCRYPTION
#define HG_CENCRYPTION
#include "common.h"

class CEncryption
{
public:
    static BYTE* Encrypt(int, BYTE* data, int dataLen);
};

#endif