#pragma once

#include <ostream>

#include "ctile.h"

// -----------------------------------------
// DBOUT is a debug alternative to std::cout that is removed in release builds
//
// Usage: DBOUT << "Hello world";
//
// Source: https://stackoverflow.com/questions/2571157/debug-only-ostreams-in-c/2571234#2571234
// -----------------------------------------

#ifdef _DEBUG
    class DebugStream {};
    template <typename T>
    DebugStream &operator<<(DebugStream &s, T) { return s; }
	extern DebugStream DBOUT;
#else
    typedef ostream DebugStream;
	DebugStream DBOUT = std::cout;
#endif

// -----------------------------------------
// Colors Table
// -----------------------------------------
// Source: https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

//	0 = Black       8 = Gray
//	1 = Blue        9 = Light Blue
//	2 = Green       10 = Light Green
//	3 = Aqua        11 = Light Aqua
//	4 = Red         12 = Light Red
//	5 = Purple      13 = Light Purple
//	6 = Yellow      14 = Light Yellow
//	7 = White       15 = Bright White

typedef enum
{
	// DEBUG_COLOR_TEMPLATE = <fg> + <bg> * 16
	DEBUG_COLOR_DEFAULT = 15 + 0 * 16,
	DEBUG_COLOR_YELLOW = 4 + 14 * 16,
	DEBUG_COLOR_GREEN = 6 + 10 * 16,
	DEBUG_COLOR_RED = 1 + 12 * 16,
	DEBUG_COLOR_BLUE = 10 + 9 * 16,
	DEBUG_COLOR_WHITE = 0 + 15 * 16,
	DEBUG_COLOR_GRAY = 0 + 8 * 16
} DebugColor;

// -----------------------------------------
// Debug sets are subsets of tiles that are assigned a debug color
// These are the names I used for the bomberman exercise
// Feel free to alter the names and add more items to the enum!
// -----------------------------------------
typedef enum
{
	DEBUG_SET_TEST,
	DEBUG_SET_ACTION,
	DEBUG_SET_UPGRADE,
	DEBUG_SET_PLAYER,
	DEBUG_SET_ENEMY,
	DEBUG_SET_NUMOF
} DebugSet;

// -----------------------------------------
// This list assigns a color to a set
// Make sure that you add a color for each set!
// -----------------------------------------
static const DebugColor kColorFromSet[] =
{
	DEBUG_COLOR_GRAY,	//DEBUG_SET_TEST,
	DEBUG_COLOR_YELLOW,	//DEBUG_SET_ACTION,
	DEBUG_COLOR_BLUE,	//DEBUG_SET_UPGRADE,
	DEBUG_COLOR_GREEN,	//DEBUG_SET_PLAYER,
	DEBUG_COLOR_RED,	//DEBUG_SET_ENEMY,
	DEBUG_COLOR_DEFAULT	//DEBUG_SET_NUMOF
};

// -----------------------------------------
// Tile Debugger
// -----------------------------------------
// This Debuger is a singleton/god object that allows you to
// add/remove tiles to debug sets
// -----------------------------------------
class TileDebugger
{
public:
	static void AddToDebugSet(DebugSet _set, Tile _tile);
	static void AddToDebugSet(DebugSet _set, std::vector<Tile> _tiles);
	static void Clear();
	static std::vector<Tile> GetTiles(DebugSet _set);

private:
	static TileDebugger& Instance();
	TileDebugger();
	~TileDebugger();
	TileDebugger(const TileDebugger&);
	TileDebugger & operator = (const TileDebugger &);
	std::vector<Tile> m_tiles[DEBUG_SET_NUMOF];
};
