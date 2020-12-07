#pragma once

#include "game_state.h"
#include "local_state.h"
#include "global_state.h"
#include "player.h"

class CGameStateIO
{
public:
    static void Import(
            CGameState &State, CLocalState &Local,
            CGlobalState &Global, const char *Buffer);

    static uint32_t Export(
            const CGameState &State, const CLocalState &Local,
            const CGlobalState &Global, char *Buffer);

private:
    CGameStateIO();
};
