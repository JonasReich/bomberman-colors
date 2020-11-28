#pragma once

#include "array2d.h"
#include "tile.h"

class CLevelGrid : public TCArray2d<TileType>
{
public:
    CLevelGrid();
    CLevelGrid(unsigned int Width, unsigned int Height);

    bool TouchesType(unsigned int x, unsigned int y, TileType Type) const;
};
