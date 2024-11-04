#pragma once

union Region
{
    unsigned short raw;
    struct
    {
        unsigned char x;
        unsigned char y;
    };
};
