#include "unit.h"

CUnit::CUnit()
: m_Type(EUnitType::None), m_LifeTime(0)
{
}

CUnit::CUnit(
        uint32_t Owner,
        EUnitType Type,
        uint32_t PosX, uint32_t PosY,
        uint32_t LifeTime)
: m_Owner(Owner),  m_Type(Type),
  m_PosX(PosX), m_PosY(PosY),
  m_LifeTime(LifeTime)
{
}

std::pair<uint32_t, uint32_t> CUnit::GetPosition()
{
	return std::pair<uint32_t, uint32_t>((uint32_t)m_PosX, (uint32_t)m_PosY);
}
