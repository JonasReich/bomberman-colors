#ifndef UNIT_H
#define UNIT_H

#include <queue>

typedef enum
{
    UNIT_TYPE_NONE,
    UNIT_TYPE_BOMB,
    UNIT_TYPE_FIRE,
    UNIT_TYPE_HERO,
    //UNIT_TYPE_ROCK,
    //UNIT_TYPE_SHOT,
    UNIT_TYPE_COUNT
}
UnitType;

class CUnit
{
public:
    CUnit();
    CUnit(unsigned int Owner, UnitType Type,
            int PosX, int PosY,
            unsigned int LifeTime);

    unsigned int m_Owner;
    UnitType m_Type;
    int m_PosX;
    int m_PosY;
    int m_DirX;
    int m_DirY;
    unsigned int m_LifeTime;
	std::pair<unsigned int, unsigned int> GetPosition();
};

#endif
