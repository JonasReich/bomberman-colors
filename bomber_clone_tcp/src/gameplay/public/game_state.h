#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "level_grid.h"
#include "unit_manager.h"
#include "player.h"

class CGameState
{
public:
    CGameState();
    CGameState(
            const CLevelGrid &LevelGrid,
            const CUnitManager &Units,
            const std::vector<CPlayer> &Player);

    CLevelGrid m_LevelGrid;
    CUnitManager m_UnitManager;
    std::vector<CPlayer> m_Player;
};

#endif
