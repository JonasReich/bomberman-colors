#include "game_state_io.h"

void CGameStateIO::Import(
        CGameState &State, CLocalState &Local,
        CGlobalState &Global, const char *Buffer)
{
    // Import global data
    memcpy((void *)(&Global), (void *)Buffer, sizeof(CGlobalState));
    Buffer += sizeof(CGlobalState);

    // Import local data
    memcpy((void *)(&Local), (void *)Buffer, sizeof(CLocalState));
    Buffer += sizeof(CLocalState);

    // Import terrain
    unsigned int Width;
    unsigned int Height;
    memcpy((void *)(&Width), (void *)Buffer, sizeof(unsigned int));
    Buffer += sizeof(unsigned int);
    memcpy((void *)(&Height), (void *)Buffer, sizeof(unsigned int));
    Buffer += sizeof(unsigned int);

    State.m_LevelGrid.Resize(Width, Height);

    unsigned int y;
    for(y = 0; y < Height; y++)
    {
        unsigned int x;
        for(x = 0; x < Width; x++)
        {
            TileType Tile;
            memcpy((void *)(&Tile), (void *)Buffer, sizeof(TileType));
            Buffer += sizeof(TileType);

            State.m_LevelGrid.Set(x, y, Tile);
        }
    }

    // Import units
    State.m_UnitManager.m_PlayerUnits.clear();
    State.m_Player.clear();
    unsigned int PlayerCount;
    memcpy((void *)(&PlayerCount), (void *)Buffer, sizeof(unsigned int));
    Buffer += sizeof(unsigned int);

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {        
        // Import player data
        CPlayer Player;
        memcpy((void *)(&Player), (void *)Buffer, sizeof(CPlayer));
        Buffer += sizeof(CPlayer);
        State.m_Player.push_back(Player);

        unsigned int UnitCount;
        memcpy((void *)(&UnitCount), (void *)Buffer, sizeof(unsigned int));
        Buffer += sizeof(unsigned int);

        State.m_UnitManager.m_PlayerUnits.push_back(std::vector<CUnit>());

        unsigned int iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            CUnit Unit;
            memcpy((void *)(&Unit), (void *)Buffer, sizeof(CUnit));
            Buffer += sizeof(CUnit);

            State.m_UnitManager.m_PlayerUnits[iPlayer].push_back(Unit);
        }
    }
}

unsigned int CGameStateIO::Export(
        const CGameState &State, const CLocalState &Local,
        const CGlobalState &Global, char *Buffer)
{
    unsigned int Size = 0;

    // Export global data
    memcpy((void *)(Buffer + Size), (void *)(&Global), sizeof(CGlobalState));
    Size += sizeof(CGlobalState);

    // Export local data
    memcpy((void *)(Buffer + Size), (void *)(&Local), sizeof(CLocalState));
    Size += sizeof(CLocalState);

    // Export terrain
    const unsigned int Width = State.m_LevelGrid.Width();
    const unsigned int Height = State.m_LevelGrid.Height();

    memcpy((void *)(Buffer + Size), (void *)(&Width), sizeof(unsigned int));
    Size += sizeof(unsigned int);
    memcpy((void *)(Buffer + Size), (void *)(&Height), sizeof(unsigned int));
    Size += sizeof(unsigned int);

    unsigned int y;
    for(y = 0; y < Height; y++)
    {
        unsigned int x;
        for(x = 0; x < Width; x++)
        {
            TileType Tile = State.m_LevelGrid.Get(x, y);
            memcpy((void *)(Buffer + Size), (void *)(&Tile), sizeof(TileType));
            Size += sizeof(TileType);
        }
    }

    // Export units
    unsigned int PlayerCount = State.m_UnitManager.m_PlayerUnits.size();
    memcpy((void *)(Buffer + Size), (void *)(&PlayerCount), sizeof(unsigned int));
    Size += sizeof(unsigned int);

    unsigned int iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {        
        // Export player data
        const CPlayer Player = State.m_Player[iPlayer];
        memcpy((void *)(Buffer + Size), (void *)(&Player), sizeof(CPlayer));
        Size += sizeof(CPlayer);

        unsigned int UnitCount = State.m_UnitManager.m_PlayerUnits[iPlayer].size();
        memcpy((void *)(Buffer + Size), (void *)(&UnitCount), sizeof(unsigned int));
        Size += sizeof(unsigned int);

        unsigned int iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            const CUnit Unit = State.m_UnitManager.m_PlayerUnits[iPlayer][iUnit];
            memcpy((void *)(Buffer + Size), (void *)(&Unit), sizeof(CUnit));
            Size += sizeof(CUnit);
        }
    }

    return Size;
}
