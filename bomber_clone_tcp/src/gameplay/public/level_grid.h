#pragma once

#include <cstdint>

#include "array2d.h"
#include "tile.h"

class CLevelGrid : public TCArray2d<ETileType>
{
public:
    CLevelGrid() = default;
    CLevelGrid(uint32_t Width, uint32_t Height);

    bool TouchesType(uint32_t x, uint32_t y, ETileType Type) const;
};
