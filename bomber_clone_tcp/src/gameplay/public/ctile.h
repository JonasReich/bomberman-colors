#pragma once

#include <cstdint>
#include <queue>
#include <iostream>
#include <sstream>

#include "defines.h"
#include "level_grid.h"

struct Tile {
	static const Tile invalid;

	Tile() :
		x(-1),
		y(-1)
	{
	}

	Tile(int32_t _x, int32_t _y) :
		x(_x),
		y(_y)
	{
	}

	Tile(std::pair<int32_t, int32_t> _xy) :
		x(_xy.first),
		y(_xy.second)
	{
	}

	bool operator<(const Tile& _other) const
	{
		return (y < _other.y || y == _other.y && x < _other.x);
	}

	bool operator==(const Tile& _other) const
	{
		return (y == _other.y && x == _other.x);
	}

	bool operator!=(const Tile& _other) const
	{
		return !(*this == _other);
	}

	int32_t y;
	int32_t x;

	bool IsValid(const CLevelGrid& _Level) const
	{
		return y >= 0
			&& x >= 0
			&& y < static_cast<int32_t>(_Level.Height())
			&& x < static_cast<int32_t>(_Level.Width());
	}

	Tile GetNeighbour(EDirection _dir) const
	{
		switch (_dir)
		{
		case kDirection_Up:
			return Tile(x, y - 1);
		case kDirection_Right:
			return Tile(x + 1, y);
		case kDirection_Down:
			return Tile(x, y + 1);
		case kDirection_Left:
			return Tile(x - 1, y);
		default:
			return Tile(-1, -1);
		}
	}

	EDirection GetNeighbourDirection(Tile _neighbour) const
	{
		if (_neighbour.y == y)
		{
			if (_neighbour.x == x - 1)
				return kDirection_Left;
			if (_neighbour.x == x + 1)
				return kDirection_Right;
		}
		else if (_neighbour.x == x)
		{
			if (_neighbour.y == y - 1)
				return kDirection_Up;
			if (_neighbour.y == y + 1)
				return kDirection_Down;
		}
		return kDirection_NumOf;
	}

	std::vector<Tile> GetNeighbours(const CLevelGrid& _Level) const
	{
		std::vector<Tile> Neighbours;
		for (uint32_t i = 0; i < kDirection_NumOf; i++) {
			Tile n = GetNeighbour(EDirection(i));
			if (n.IsValid(_Level))
				Neighbours.push_back(n);
		}
		return Neighbours;
	}

	std::string ToString() const
	{
		std::stringstream S;
		S << "(" << x << "|" << y << ")";
		return S.str();
	}
};
