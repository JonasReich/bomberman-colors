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
    uint32_t Width;
    uint32_t Height;
    memcpy((void *)(&Width), (void *)Buffer, sizeof(uint32_t));
    Buffer += sizeof(uint32_t);
    memcpy((void *)(&Height), (void *)Buffer, sizeof(uint32_t));
    Buffer += sizeof(uint32_t);

    State.m_LevelGrid.Resize(Width, Height);

    uint32_t y;
    for(y = 0; y < Height; y++)
    {
        uint32_t x;
        for(x = 0; x < Width; x++)
        {
            ETileType Tile;
            memcpy((void *)(&Tile), (void *)Buffer, sizeof(ETileType));
            Buffer += sizeof(ETileType);

            State.m_LevelGrid.Set(x, y, Tile);
        }
    }

    // Import units
    State.m_UnitManager.m_PlayerUnits.clear();
    State.m_Player.clear();
    uint32_t PlayerCount;
    memcpy((void *)(&PlayerCount), (void *)Buffer, sizeof(uint32_t));
    Buffer += sizeof(uint32_t);

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {        
        // Import player data
        CPlayer Player;
        memcpy((void *)(&Player), (void *)Buffer, sizeof(CPlayer));
        Buffer += sizeof(CPlayer);
        State.m_Player.push_back(Player);

        uint32_t UnitCount;
        memcpy((void *)(&UnitCount), (void *)Buffer, sizeof(uint32_t));
        Buffer += sizeof(uint32_t);

        State.m_UnitManager.m_PlayerUnits.push_back(std::vector<CUnit>());

        uint32_t iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            CUnit Unit;
            memcpy((void *)(&Unit), (void *)Buffer, sizeof(CUnit));
            Buffer += sizeof(CUnit);

            State.m_UnitManager.m_PlayerUnits[iPlayer].push_back(Unit);
        }
    }
}

uint32_t CGameStateIO::Export(
        const CGameState &State, const CLocalState &Local,
        const CGlobalState &Global, char *Buffer)
{
    uint32_t Size = 0;

    // Export global data
    memcpy((void *)(Buffer + Size), (void *)(&Global), sizeof(CGlobalState));
    Size += sizeof(CGlobalState);

    // Export local data
    memcpy((void *)(Buffer + Size), (void *)(&Local), sizeof(CLocalState));
    Size += sizeof(CLocalState);

    // Export terrain
    const uint32_t Width = State.m_LevelGrid.Width();
    const uint32_t Height = State.m_LevelGrid.Height();

    memcpy((void *)(Buffer + Size), (void *)(&Width), sizeof(uint32_t));
    Size += sizeof(uint32_t);
    memcpy((void *)(Buffer + Size), (void *)(&Height), sizeof(uint32_t));
    Size += sizeof(uint32_t);

    uint32_t y;
    for(y = 0; y < Height; y++)
    {
        uint32_t x;
        for(x = 0; x < Width; x++)
        {
            ETileType Tile = State.m_LevelGrid.Get(x, y);
            memcpy((void *)(Buffer + Size), (void *)(&Tile), sizeof(ETileType));
            Size += sizeof(ETileType);
        }
    }

    // Export units
    uint32_t PlayerCount = static_cast<uint32_t>(State.m_UnitManager.m_PlayerUnits.size());
    memcpy((void *)(Buffer + Size), (void *)(&PlayerCount), sizeof(uint32_t));
    Size += sizeof(uint32_t);

    uint32_t iPlayer;
    for(iPlayer = 0; iPlayer < PlayerCount; iPlayer++)
    {        
        // Export player data
        const CPlayer Player = State.m_Player[iPlayer];
        memcpy((void *)(Buffer + Size), (void *)(&Player), sizeof(CPlayer));
        Size += sizeof(CPlayer);

        uint32_t UnitCount = static_cast<uint32_t>(State.m_UnitManager.m_PlayerUnits[iPlayer].size());
        memcpy((void *)(Buffer + Size), (void *)(&UnitCount), sizeof(uint32_t));
        Size += sizeof(uint32_t);

        uint32_t iUnit;
        for(iUnit = 0; iUnit < UnitCount; iUnit++)
        {
            const CUnit Unit = State.m_UnitManager.m_PlayerUnits[iPlayer][iUnit];
            memcpy((void *)(Buffer + Size), (void *)(&Unit), sizeof(CUnit));
            Size += sizeof(CUnit);
        }
    }

    return Size;
}
