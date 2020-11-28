#include "game_sim.h"

CGameState CGameSim::UpdateWorld(
        const CGameState &State, const std::vector<PlayerControlType> &Action)
{
    return CGameState(
            UpdateGrid(State),
            UpdateUnits(State, Action),
            UpdatePlayers(State));

    /* // XXX upgrade-in-same-turn-hack
    const CLevelGrid UpdatedGrid = UpdateGrid(State);
    const CUnitManager UpdatedUnits = UpdateUnits(State, Action);
    const std::vector<CPlayer> UpdatedPlayers = UpdatePlayers(CGameState(UpdatedGrid, UpdatedUnits, State.m_Player));

    return CGameState(UpdatedGrid, UpdatedUnits, UpdatedPlayers);*/
}

std::vector<CPlayer> CGameSim::UpdatePlayers(
        const CGameState &State)
{
    std::vector<CPlayer> UpdatedPlayer;

    unsigned int PlayerCount = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits.size());
    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {
        const CPlayer CurrentPlayer = State.m_Player[iPlayer];
        CPlayer NewPlayer = CurrentPlayer;

        unsigned int UnitCount = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits[iPlayer].size());
        unsigned int iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            const CUnit UnitCurrent = State.m_UnitManager.m_PlayerUnits[iPlayer][iUnit];

            if(UnitCurrent.m_Type == EUnitType::Hero)
            {
                if(State.m_LevelGrid.Get(UnitCurrent.m_PosX, UnitCurrent.m_PosY) == ETileType::Upgrade_Size)
                    NewPlayer.m_ExplosionSize++;

                if(State.m_LevelGrid.Get(UnitCurrent.m_PosX, UnitCurrent.m_PosY) == ETileType::Upgrade_BombCount)
                    NewPlayer.m_BombNr++;
            }
        }

        UpdatedPlayer.push_back(NewPlayer);
    }

    return UpdatedPlayer;
}

CLevelGrid CGameSim::UpdateGrid(
        const CGameState &State)
{
    const unsigned int Width = State.m_LevelGrid.Width();
    const unsigned int Height = State.m_LevelGrid.Height();
    CLevelGrid UpdatedGrid(Width, Height);

    unsigned int v;
    for(v = 0; v < Height; v++)
    {
        unsigned int u;
        for(u = 0; u < Width; u++)
        {
            const ETileType CurrentTile = State.m_LevelGrid.Get(u, v);
            ETileType NewTile = CurrentTile;

            switch(CurrentTile)
            {
            case ETileType::Rock:
                if(State.m_UnitManager.TileContains(u, v, EUnitType::Fire))
                    NewTile = ETileType::Free;

                break;
            case ETileType::Upgrade_BombCount:
            {
                unsigned int Collect = 0;

                const unsigned int nPlayer = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits.size());
                unsigned int iPlayer;
                for(iPlayer = 0; iPlayer < nPlayer; iPlayer++)
                {
                    if(State.m_UnitManager.CountPlayerUnitsOnTile(iPlayer, EUnitType::Hero, u, v) > 0)
                        Collect++;
                }

                if(Collect > 0)
                    NewTile = ETileType::Free;

                break;
            }
            case ETileType::Upgrade_Size:
            {
                unsigned int Collect = 0;

                const unsigned int nPlayer = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits.size());
                unsigned int iPlayer;
                for(iPlayer = 0; iPlayer < nPlayer; iPlayer++)
                {
                    if(State.m_UnitManager.CountPlayerUnitsOnTile(iPlayer, EUnitType::Hero, u, v) > 0)
                        Collect++;
                }

                if(Collect > 0)
                    NewTile = ETileType::Free;

                break;
            }
            default:
                ;
            }

            UpdatedGrid.Set(u,v, NewTile);
        }
    }

    return UpdatedGrid;
}

CUnitManager CGameSim::UpdateUnits(
        const CGameState &State,
        const std::vector<PlayerControlType> &Action)
{
    CUnitManager UpdatedUnits;

    unsigned int PlayerCount = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits.size());
    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {
        UpdatedUnits.m_PlayerUnits.push_back(std::vector<CUnit>());

        unsigned int UnitCount = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits[iPlayer].size());
        unsigned int iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            const CUnit UnitCurrent = State.m_UnitManager.m_PlayerUnits[iPlayer][iUnit];

            CUnit UnitNew = UnitCurrent;

            switch(UnitCurrent.m_Type)
            {
            case EUnitType::Hero:
                //if(State.m_LevelGrid.Get(UnitCurrent.m_PosX, UnitCurrent.m_PosY) == 
                if(State.m_UnitManager.TileContains(UnitCurrent.m_PosX, UnitCurrent.m_PosY, EUnitType::Fire))
                {
                    // delete hero by not re-inserting in queue
                }
                else
                {
                    switch(Action[iPlayer])
                    {
                    case PLAYER_CONTROL_MOVE_UP:
                        UnitNew.m_PosY--;
                        break;
                    case PLAYER_CONTROL_MOVE_DOWN:
                        UnitNew.m_PosY++;
                        break;
                    case PLAYER_CONTROL_MOVE_LEFT:
                        UnitNew.m_PosX--;
                        break;
                    case PLAYER_CONTROL_MOVE_RIGHT:
                        UnitNew.m_PosX++;
                        break;
                    case PLAYER_CONTROL_BOMB:
                    {
                        const unsigned int BombsInUse = State.m_UnitManager.CountPlayerUnits(iPlayer, EUnitType::Bomb);
                        if(BombsInUse < State.m_Player[iPlayer].m_BombNr)
                        {
                            const CUnit Bomb(
                                    iPlayer, EUnitType::Bomb,
                                    UnitCurrent.m_PosX, UnitCurrent.m_PosY, 4);

                            UpdatedUnits.m_PlayerUnits[iPlayer].push_back(Bomb);
                        }

                        break;
                    }
                    case PLAYER_CONTROL_TRAP:
                    {
                        const unsigned int BombsInUse = State.m_UnitManager.CountPlayerUnits(iPlayer, EUnitType::Bomb);
                        if(BombsInUse + 1 < State.m_Player[iPlayer].m_BombNr) // make sure player has at least one bomb to use
                        {
                            const CUnit Bomb(
                                    iPlayer, EUnitType::Bomb,
                                    UnitCurrent.m_PosX, UnitCurrent.m_PosY, 0);

                            UpdatedUnits.m_PlayerUnits[iPlayer].push_back(Bomb);
                        }

                        break;
                    }
                    default:
                        ;
                    }

                    if(State.m_LevelGrid.Get(UnitNew.m_PosX, UnitNew.m_PosY) != ETileType::Wall
                            && State.m_LevelGrid.Get(UnitNew.m_PosX, UnitNew.m_PosY) != ETileType::Rock)
                    {
                        UpdatedUnits.m_PlayerUnits[iPlayer].push_back(UnitNew);
                    }
                    else
                    {
                        UpdatedUnits.m_PlayerUnits[iPlayer].push_back(UnitCurrent);
                    }
                }

                break;
            case EUnitType::Bomb:
                if(UnitCurrent.m_LifeTime != 1
                        && State.m_UnitManager.CountAllUnitsOnTile(EUnitType::Fire, UnitCurrent.m_PosX, UnitCurrent.m_PosY) <= 0)
                {
                    if(UnitNew.m_LifeTime > 1)
                        UnitNew.m_LifeTime--;

                    /*if(State.m_UnitManager.CountAllUnitsOnTile(EUnitType::Fire, UnitCurrent.m_PosX, UnitCurrent.m_PosY) > 0)
                    {
                        //if(UnitCurrent.m_LifeTime > 1)
                            UnitNew.m_LifeTime = 1; // explode in next frame
                    }*/

                    UpdatedUnits.m_PlayerUnits[iPlayer].push_back(UnitNew);
                }
                else
                {
                    if(UnitCurrent.m_Owner < State.m_UnitManager.m_PlayerUnits.size())
                    {
                        const int Range = State.m_Player[UnitCurrent.m_Owner].m_ExplosionSize;

                        UpdatedUnits.m_PlayerUnits[iPlayer].push_back(CUnit(UnitCurrent.m_Owner, EUnitType::Fire, UnitCurrent.m_PosX, UnitCurrent.m_PosY, 1));

                        ExplosionBeam(
                                UpdatedUnits, State, iPlayer,
                                UnitCurrent.m_PosX, UnitCurrent.m_PosY,
                                +1, 0, Range);

                        ExplosionBeam(
                                UpdatedUnits, State, iPlayer,
                                UnitCurrent.m_PosX, UnitCurrent.m_PosY,
                                -1, 0, Range);
                        
                        ExplosionBeam(
                                UpdatedUnits, State, iPlayer,
                                UnitCurrent.m_PosX, UnitCurrent.m_PosY,
                                0, +1, Range);

                        ExplosionBeam(
                                UpdatedUnits, State, iPlayer,
                                UnitCurrent.m_PosX, UnitCurrent.m_PosY,
                                0, -1, Range);
                    }
                }

                break;
            case EUnitType::Fire:
                if(UnitCurrent.m_LifeTime != 1)
                {
                    if(UnitNew.m_LifeTime > 1)
                        UnitNew.m_LifeTime--;

                    UnitNew.m_PosX += UnitCurrent.m_DirX;
                    UnitNew.m_PosY += UnitCurrent.m_DirY;

                    UpdatedUnits.m_PlayerUnits[iPlayer].push_back(UnitNew);
                }
                break;
            default:
                UpdatedUnits.m_PlayerUnits[iPlayer].push_back(UnitNew);
            }
        }
    }

    return UpdatedUnits;
}

void CGameSim::ExplosionBeam(
        CUnitManager &UpdatedUnits,
        const CGameState &State,
        unsigned int iPlayer,
        unsigned int x0, unsigned int y0,
        int dx, int dy, unsigned int r)
{
    unsigned int PlayerCount = static_cast<unsigned int>(State.m_UnitManager.m_PlayerUnits.size());
    if(iPlayer < PlayerCount)
    {
        unsigned int i;
        for(i = 1; i <= r; i++)
        {
            const unsigned int x = x0 + dx * i;
            const unsigned int y = y0 + dy * i;

            if(State.m_LevelGrid.Get(x, y) == ETileType::Wall)
                break;

            const CUnit Explosion(
                    iPlayer, EUnitType::Fire,
                    x, y, 1);

            UpdatedUnits.m_PlayerUnits[iPlayer].push_back(Explosion);

            if(State.m_LevelGrid.Get(x, y) == ETileType::Rock)
                break;
        }
    }
}
