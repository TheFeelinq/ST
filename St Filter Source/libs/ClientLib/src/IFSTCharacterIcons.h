#pragma once
#include "stdafx.h"
#include "ICPlayer.h"
#include "MemoryHelper.h"


class CharacterIcons
{
public:

    static void Initialize();
    static bool __stdcall OnCharacterIcon(CICPlayer* player);
private:

};