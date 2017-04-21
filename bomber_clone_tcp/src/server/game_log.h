#ifndef GAME_LOG_H
#define GAME_LOG_H

#include <vector>

#include "../gameplay/player.h"
#include "../gameplay/game_state.h"

class CGameLog
{
public:
    //CGameLog();
    void Save(const char *FileName) const;
    void Load(const char *FileName);

    std::vector<CPlayer> m_Frames;

    static const char *const s_Version;
};

#endif
