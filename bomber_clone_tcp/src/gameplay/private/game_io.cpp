
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <windows.h>

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

	unsigned int y;
	for (y = 0; y < State.m_LevelGrid.Height(); y++)
	{
		unsigned int x;
		for (x = 0; x < State.m_LevelGrid.Width(); x++)
		{
			// Set draw color according to DebugColor listed in TileDebugger
			if (_debug)
			{
				Tile currentTile(x, y);
				SetConsoleTextAttribute(hConsole, DebugColor::DEBUG_COLOR_DEFAULT);

				for (unsigned int i = 0; i < DEBUG_SET_NUMOF; i++)
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
					//std::cout << "!!";
					const char PlayerChar = '0' + (Unit.m_Owner % 10);
					std::cout << PlayerChar << PlayerChar;
					break;
				}
				/*case UNIT_TYPE_ROCK:
					std::cout << "()";
					break;*/
					/*case UNIT_TYPE_SHOT:
						std::cout << "<>";
						break;*/
				default:
					std::cout << "!?";
				}
			}
			else
			{
				TileType Type = State.m_LevelGrid.Get(x, y);

				switch (Type)
				{
				case TILE_TYPE_FREE:
					std::cout << "  ";
					break;
				case TILE_TYPE_WALL:
					std::cout << "##";
					break;
					/*case TILE_TYPE_FUEL:
						std::cout << "[]";
						break;*/
						/*case TILE_TYPE_FIRE:
							std::cout << "%%";
							break;*/
				case TILE_TYPE_ROCK:
					std::cout << "::";
					break;
				case TILE_TYPE_UPSZ:
					std::cout << "<>";
					break;
				case TILE_TYPE_UPNR:
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

	unsigned int Width;
	InStream >> Width;
	unsigned int Height;
	InStream >> Height;
	int Legacy;
	InStream >> Legacy;

	State.m_LevelGrid.Resize(Width, Height);
	unsigned int iPlayer;
	for (iPlayer = 0; iPlayer < State.m_UnitManager.m_PlayerUnits.size(); iPlayer++)
	{
		State.m_UnitManager.m_PlayerUnits[iPlayer].clear();
	}

	unsigned int Row;
	for (Row = 0; Row < Height; Row++)
	{
		unsigned int Column;
		for (Column = 0; Column < Width; Column++)
		{
			int Red;
			int Green;
			int Blue;

			InStream >> Red;
			InStream >> Green;
			InStream >> Blue;

			TileType Type = TILE_TYPE_NONE;
			if (Red == Green && Red == Blue) // grey
			{
				if (Red < 64)
					Type = TILE_TYPE_FREE;
				else if (Red < 196)
					Type = TILE_TYPE_ROCK;
				else // if(Red >= 196)
					Type = TILE_TYPE_WALL;
			}
			else if (Red > Green && Red > Blue)
				Type = TILE_TYPE_UPSZ;
			else if (Blue > Red && Blue > Green)
				Type = TILE_TYPE_UPNR;
			else if (Green > Red && Green > Blue)
				Type = TILE_TYPE_TRAP;
			else if (Green == Red && Green > Blue)
				Type = TILE_TYPE_FUSE;

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

	unsigned int Row;
	for (Row = 0; Row < State.m_LevelGrid.Height(); Row++)
	{
		unsigned int Column;
		for (Column = 0; Column < State.m_LevelGrid.Width(); Column++)
		{
			int Red;
			int Green;
			int Blue;

			const TileType Type = State.m_LevelGrid.Get(Column, Row);

			switch (Type)
			{
			case TILE_TYPE_FREE:
				Red = 0;
				Green = 0;
				Blue = 0;
				break;
			case TILE_TYPE_ROCK:
				Red = 128;
				Green = 128;
				Blue = 128;
				break;
			case TILE_TYPE_WALL:
				Red = 255;
				Green = 255;
				Blue = 255;
				break;
			case TILE_TYPE_UPSZ:
				Red = 255;
				Green = 0;
				Blue = 0;
				break;
			case TILE_TYPE_UPNR:
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

void CGameIO::Save(
	std::ostream &OutStream, const CGameState &State, const char *Comment)
{
	PPMExport(OutStream, State, Comment);

	/*unsigned int iPlayer;
	for(iPlayer = 0; iPlayer < State.m_UnitManager.m_PlayersAndUnits.size(); iPlayer++)
	{
		State.m_UnitManager.m_PlayersAndUnits[iPlayer].clear();
	}*/
}

void CGameIO::Load(std::istream &InStream, CGameState &State)
{
	PPMImport(InStream, State);

	/*unsigned int iPlayer;
	for(iPlayer = 0; iPlayer < State.m_UnitManager.m_PlayersAndUnits.size(); iPlayer++)
	{
		State.m_UnitManager.m_PlayersAndUnits[iPlayer].clear();
	}*/
}
