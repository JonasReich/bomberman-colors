
#include <fstream>
#include <iostream>
#include <string>

#include "game_log.h"

#include "game_io.h"

const char *const CGameLog::s_Version = "BC_0.0.0";

void CGameLog::Save(const char *FileName) const
{
    std::ofstream ofs(FileName);

    ofs << s_Version << "\n";
}

void CGameLog::Load(const char *FileName)
{
    std::ifstream ifs(FileName);

    std::string Version;
    std::getline(ifs, Version);
    if(Version != s_Version)
    {
        std::cerr << "expected version " << s_Version << " ";
        std::cerr << "but found version " << Version << "\n";
        std::cerr << "failed to load " << FileName << "\n";
        return;
    }
}
