#pragma once

#include <vector>

#include "player.h"
#include "game_state.h"

class CGameLog
{
public:
    //CGameLog();
    void Save(const char *FileName) const;
    void Load(const char *FileName);

    std::vector<CPlayer> m_Frames;

    static const char *const s_Version;
};
