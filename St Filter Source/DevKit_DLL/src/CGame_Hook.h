#pragma once

#include <Game.h>

class CGame_Hook : public CGame {
public:
    void LoadGameOption();

    void addr_from_this(int (*pFunction)(CMsgStreamBuffer *));
};
