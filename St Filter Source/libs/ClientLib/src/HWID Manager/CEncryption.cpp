#include "CEncryption.h"
BYTE* CEncryption::Encrypt(int key, BYTE* data, int dataLen)
{
    BYTE* enc = (BYTE *)malloc(dataLen);
    for (int i = 0; i < dataLen; i++)
    {
        enc[i] = (BYTE)(data[i] ^ key);
    }
    return enc;
}