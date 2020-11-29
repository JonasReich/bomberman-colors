#include "game_state.h"

CGameState::CGameState(
        const CLevelGrid &LevelGrid,
        const CUnitManager &Units,
        const std::vector<CPlayer> &Player)
: m_LevelGrid(LevelGrid), m_UnitManager(Units), m_Player(Player)
{
}
