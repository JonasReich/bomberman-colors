#pragma once

#include <cstdint>

#include "game_state.h"
#include "player.h"
#include "game_play.h"

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
            uint32_t iPlayer,
            uint32_t x, uint32_t y,
            int32_t dx, int32_t dy, uint32_t r);
};
