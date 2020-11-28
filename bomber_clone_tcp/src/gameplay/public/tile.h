#pragma once

typedef enum
{
    TILE_TYPE_NONE = 0, // error type
    TILE_TYPE_FREE = 1,
    TILE_TYPE_ROCK = 2,
    TILE_TYPE_WALL = 3,
    TILE_TYPE_UPNR = 4,
    TILE_TYPE_UPSZ = 5,
    TILE_TYPE_TRAP = 6, // only spawn-marker, removed after loading level
    TILE_TYPE_FUSE = 7, // only spawn-marker, removed after loading level
    //TILE_TYPE_FUEL,
    //TILE_TYPE_FIRE,
}
TileType;
