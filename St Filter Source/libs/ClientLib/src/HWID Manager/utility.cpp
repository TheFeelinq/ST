#include "utility.h"


void utility::PrintHexDump(const BYTE* bpBuffer, size_t len)
{
    int bytesPerLine = 16;

    for (int i = 0; i < len; i++)
    {
        printf("%02X ", bpBuffer[i]);
        if (i % 16 == 0 && i != 0)
            printf("\n");
    }


}