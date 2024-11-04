#include <Windows.h>
#include <iostream>
#include "IFSTCharacterIcons.h"
#include "PSilkroad.h"

class CPSTitle : public CPSilkroad {
public:
    bool OnServerPacketRecv(class CMsgStreamBuffer* MsgBuffer);
    wchar_t* Convert(std::n_string name);
    bool OnCreateTMEP(long ln);
    static void Version();

};
