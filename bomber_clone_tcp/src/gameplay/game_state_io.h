#ifndef GAME_STATE_IO_H
#define GAME_STATE_IO_H

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

    static unsigned int Export(
            const CGameState &State, const CLocalState &Local,
            const CGlobalState &Global, char *Buffer);

private:
    CGameStateIO();
};

#endif
