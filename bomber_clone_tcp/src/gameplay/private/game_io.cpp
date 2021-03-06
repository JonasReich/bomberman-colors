
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <windows.h>

#include "gameplay_defines.h"
#include "game_io.h"
#include "vectorExtensions.h"
#include "color_debug.h"

void CGameIO::ASCIIExport(const CGameState & State, bool _debug)
{
	// Get a handle for the console the program is running in
	// We need this handle to set text color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Print a "DEBUG VIEW:" header
	if (_debug)
	{
		SetConsoleTextAttribute(hConsole, DebugColor::DEBUG_COLOR_YELLOW);
		std::cout << "DEBUG VIEW:\n";
		SetConsoleTextAttribute(hConsole, DebugColor::DEBUG_COLOR_DEFAULT);
	}

	uint32_t y;
	for (y = 0; y < State.m_LevelGrid.Height(); y++)
	{
		uint32_t x;
		for (x = 0; x < State.m_LevelGrid.Width(); x++)
		{
			// Set draw color according to DebugColor listed in TileDebugger
			if (_debug)
			{
				Tile currentTile(x, y);
				SetConsoleTextAttribute(hConsole, DebugColor::DEBUG_COLOR_DEFAULT);

				for (uint32_t i = 0; i < DEBUG_SET_NUMOF; i++)
				{
					if (VectorContains(TileDebugger::GetTiles((DebugSet)i), currentTile))
						SetConsoleTextAttribute(hConsole, kColorFromSet[i]);
				}
			}
			
			// From here on everything is unchanged...


			const std::vector<CUnit> UnitsOnTile = State.m_UnitManager.GetAllUnitsOnTile(x, y);
			if (UnitsOnTile.size() > 0)
			{
				const CUnit Unit = UnitsOnTile[0];

				switch (Unit.m_Type)
				{
				case EUnitType::Bomb:
					if (Unit.m_LifeTime > 0)
						std::cout << "()";
					else
						std::cout << "[]";
					break;
				case EUnitType::Fire:
					std::cout << "%%";
					break;
				case EUnitType::Hero:
				{
					static_assert(MaxPlayerCount < 10, "MaxPlayerCount must be smaller than 10 for this code to work");
					const char PlayerChar = '0' + (Unit.m_Owner % 10);
					std::cout << PlayerChar << PlayerChar;
					break;
				}
				default:
					std::cout << "!?";
				}
			}
			else
			{
				ETileType Type = State.m_LevelGrid.Get(x, y);

				switch (Type)
				{
				case ETileType::Free:
					std::cout << "  ";
					break;
				case ETileType::Wall:
					std::cout << "##";
					break;
				case ETileType::Rock:
					std::cout << "::";
					break;
				case ETileType::Upgrade_Size:
					std::cout << "<>";
					break;
				case ETileType::Upgrade_BombCount:
					std::cout << "++";
					break;
				default:
					std::cout << "??";
				}
			}
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}

void CGameIO::PPMImport(std::istream &InStream, CGameState &State)
{
	std::string Magic;
	std::getline(InStream, Magic);

	if (Magic.size() < 2)
	{
		State.m_LevelGrid.Resize(0, 0);
		return;
	}

	if (Magic[0] != 'P' && Magic[1] != '3')
	{
		std::cerr << "Expected P3, found unknown format code " << Magic[0] << Magic[1] << "\n";
		exit(-1);
	}

	if (InStream.peek() == '#')
	{
		std::string Comment;
		std::getline(InStream, Comment);
	}

	uint32_t Width;
	InStream >> Width;
	uint32_t Height;
	InStream >> Height;
	int32_t Legacy;
	InStream >> Legacy;

	State.m_LevelGrid.Resize(Width, Height);
	uint32_t iPlayer;
	for (iPlayer = 0; iPlayer < State.m_UnitManager.m_PlayerUnits.size(); iPlayer++)
	{
		State.m_UnitManager.m_PlayerUnits[iPlayer].clear();
	}

	uint32_t Row;
	for (Row = 0; Row < Height; Row++)
	{
		uint32_t Column;
		for (Column = 0; Column < Width; Column++)
		{
			int32_t Red;
			int32_t Green;
			int32_t Blue;

			InStream >> Red;
			InStream >> Green;
			InStream >> Blue;

			ETileType Type = ETileType::None;
			if (Red == Green && Red == Blue) // grey
			{
				if (Red < 64)
					Type = ETileType::Free;
				else if (Red < 196)
					Type = ETileType::Rock;
				else // if(Red >= 196)
					Type = ETileType::Wall;
			}
			else if (Red > Green && Red > Blue)
				Type = ETileType::Upgrade_Size;
			else if (Blue > Red && Blue > Green)
				Type = ETileType::Upgrade_BombCount;
			else if (Green > Red && Green > Blue)
				Type = ETileType::Trap;
			else if (Green == Red && Green > Blue)
				Type = ETileType::Fuse;

			State.m_LevelGrid.Set(Column, Row, Type);
		}
	}
}

void CGameIO::PPMExport(
	std::ostream &OutStream, const CGameState &State, const char *Comment)
{
	OutStream << "P3\n";
	OutStream << "# " << Comment << "\n";
	OutStream << State.m_LevelGrid.Width() << " " << State.m_LevelGrid.Height() << "\n";
	OutStream << "255\n";

	uint32_t Row;
	for (Row = 0; Row < State.m_LevelGrid.Height(); Row++)
	{
		uint32_t Column;
		for (Column = 0; Column < State.m_LevelGrid.Width(); Column++)
		{
			int32_t Red;
			int32_t Green;
			int32_t Blue;

			const ETileType Type = State.m_LevelGrid.Get(Column, Row);

			switch (Type)
			{
			case ETileType::Free:
				Red = 0;
				Green = 0;
				Blue = 0;
				break;
			case ETileType::Rock:
				Red = 128;
				Green = 128;
				Blue = 128;
				break;
			case ETileType::Wall:
				Red = 255;
				Green = 255;
				Blue = 255;
				break;
			case ETileType::Upgrade_Size:
				Red = 255;
				Green = 0;
				Blue = 0;
				break;
			case ETileType::Upgrade_BombCount:
				Red = 0;
				Green = 0;
				Blue = 255;
				break;
			default:
				Red = 0;
				Green = 0;
				Blue = 0;
				break;
			}

			OutStream << Red;
			OutStream << Green;
			OutStream << Blue;
		}
	}
}

void CGameIO::Save(std::ostream &OutStream, const CGameState &State, const char *Comment)
{
	PPMExport(OutStream, State, Comment);
}

void CGameIO::Load(std::istream &InStream, CGameState &State)
{
	PPMImport(InStream, State);
}
