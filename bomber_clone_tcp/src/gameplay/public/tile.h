#pragma once

/**
 * Type of a level grid tile.
 * Determines collision response and may trigger some overlap effects.
 */
enum class ETileType
{
    None = 0, // error type
    Free = 1,
    Rock = 2,
    Wall = 3,
    Upgrade_BombCount = 4,
    Upgrade_Size = 5,
    Trap = 6, // only spawn-marker, removed after loading level
    Fuse = 7, // only spawn-marker, removed after loading level
};
