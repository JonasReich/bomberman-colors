#include "color_debug.h"

DebugStream DBOUT;

void TileDebugger::AddToDebugSet(DebugSet _set, Tile _tile) {
	Instance().m_tiles[_set].push_back(_tile);
}

void TileDebugger::AddToDebugSet(DebugSet _set, std::vector<Tile> _tiles) {
	for (Tile t : _tiles)
		Instance().m_tiles[_set].push_back(t);
}

void TileDebugger::Clear()
{
	for (std::vector<Tile>& vector : Instance().m_tiles)
		vector.clear();
}

std::vector<Tile> TileDebugger::GetTiles(DebugSet _set) {
	return Instance().m_tiles[_set];
}

TileDebugger& TileDebugger::Instance() {
	static TileDebugger _instance;
	return _instance;
}

TileDebugger::TileDebugger() {}
TileDebugger::~TileDebugger() {}
TileDebugger::TileDebugger(const TileDebugger&) {}
TileDebugger & TileDebugger::operator = (const TileDebugger & TD) { return *this; }
