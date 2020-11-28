#include "level_grid.h"

CLevelGrid::CLevelGrid()
{
}

CLevelGrid::CLevelGrid(uint32_t Width, uint32_t Height)
: TCArray2d<ETileType>(Width, Height)
{
}

bool CLevelGrid::TouchesType(uint32_t x, unsigned y, ETileType Type) const
{
    if(Get(x - 1, y) == Type)
        return true;

    if(Get(x + 1, y) == Type)
        return true;

    if(Get(x, y - 1) == Type)
        return true;

    if(Get(x, y + 1) == Type)
        return true;

    return false;
}
