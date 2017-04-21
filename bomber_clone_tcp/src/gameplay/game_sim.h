#ifndef GAME_SIM_H
#define GAME_SIM_H

#include "../gameplay/game_state.h"
#include "../gameplay/player.h"
#include "../gameplay/game_play.h"

class CGameSim
{
public:
    static CGameState UpdateWorld(
    const CGameState &State, const std::vector<PlayerControlType> &Action);

private:
    CGameSim();

    static std::vector<CPlayer> UpdatePlayers(
            const CGameState &State);

    static CLevelGrid UpdateGrid(
            const CGameState &State);

    static CUnitManager UpdateUnits(
            const CGameState &State,
            const std::vector<PlayerControlType> &Action);

    static void ExplosionBeam(
            CUnitManager &NewUnitManager,
            const CGameState &State,
            unsigned int iPlayer,
            unsigned int x, unsigned int y,
            int dx, int dy, unsigned int r);
};

#endif
