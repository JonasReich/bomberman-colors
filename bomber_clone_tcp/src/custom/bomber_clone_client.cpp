#include <iostream>
#include <ctime>
#include <stdlib.h>

#include "ctile.h"

#include "net_shared.h"

#include "game_play.h"
#include "game_state.h"
#include "game_state_io.h"
#include "game_io.h"

// MUST BE SAME AS SERVER BUFFER-SIZE
// IN CASE Of CRASH RECOMPILE & CHECK FOR OVERFLOW
#define BUFFER_SIZE 100000

int main(int argc, char **argv)
{
	srand((unsigned int)time(0));
	// Check for parameters
	/*if(argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " host port\n";
		std::cerr << "e.g.   " << argv[0] << " localhost 2000\n";
		std::cerr << "e.g.   " << argv[0] << " 127.0.0.1 2000\n";
		exit(EXIT_FAILURE);
	}*/

	const char *DestinationName = (argc > 1) ? argv[1] : "localhost";
	const Uint16 DestinationPort = (argc > 2) ? atoi(argv[2]) : 2000;
	const std::string Behaviour = (argc > 3) ? argv[3] : "manual";

	// Initialize SDL_net
	if (SDLNet_Init() < 0)
	{
		std::cerr << "SDLNet_Init: " << SDLNet_GetError() << "\n";
		exit(EXIT_FAILURE);
	}

	IPaddress ServerIP;
	TCPsocket ServerSocket;

	std::cout << "resolving hostname...\n";
	if (SDLNet_ResolveHost(&ServerIP, DestinationName, DestinationPort))
	{
		std::cerr << "failed to resolve " << DestinationName << "\n";
		std::cerr << SDL_GetError();
		exit(3);
	}

	Uint32 ServerIPHost = ServerIP.host;
	std::cout << "Server IP: ";
	std::cout << CNet::TranslateAddr(ServerIP.host);
	std::cout << ", port " << ServerIP.port;
	std::cout << "\n";

	std::cout << "connecting to server ";
	std::cout << CNet::TranslateAddr(ServerIP.host) << ":" << DestinationPort;
	std::cout << " (" << DestinationName << ")";
	std::cout << "...\n";
	ServerSocket = SDLNet_TCP_Open(&ServerIP);
	if (!ServerSocket)
	{
		std::cerr << "failed to connect to server\n";
		std::cerr << SDL_GetError();
		exit(4);
	}

	std::cerr << "sending player name...\n";
	const char PlayerName[16] = "TESTPLAYER";
	if (SDLNet_TCP_Send(ServerSocket, (void *)PlayerName, sizeof(PlayerName)) != sizeof(PlayerName))
	{
		std::cerr << "failed to notify client\n";
		std::cerr << SDL_GetError();
		exit(5);
	}

	std::cerr << "receiving local info...\n";
	CLocalState Local;
	if (SDLNet_TCP_Recv(ServerSocket, (void *)(&Local), sizeof(CLocalState)) != sizeof(CLocalState))
	{
		std::cerr << "failed to receive local info\n";
		std::cerr << SDL_GetError();
		exit(5);
	}

	std::cout << "Player number " << Local.m_PlayerNr << "\n";

	char Buffer[BUFFER_SIZE];

	CGameState State;
	CGlobalState Global;

	std::cout << "client running.\n";

	// variables for bot
	//std::vector<std::vector<CUnit>> playerUnits = State.m_UnitManager.m_PlayerUnits;

	// Main loop
	bool Quit = false;
	while (!Quit)
	{
		if (SDLNet_TCP_Recv(ServerSocket, (void *)Buffer, BUFFER_SIZE) != BUFFER_SIZE)
		{
			std::cerr << "failed to receive data from server\n";
			std::cerr << SDL_GetError();
			exit(5);
		}

		CGameStateIO::Import(State, Local, Global, Buffer);
		CGameIO::ASCIIExport(State);

		std::cout << "Server round: " << Global.m_Round << " cycle: " << Global.m_Cycle << "\n";
		std::cout << "I'm player " << Local.m_PlayerNr;

		if ((unsigned int)Local.m_PlayerNr < State.m_UnitManager.m_PlayerUnits.size())
			std::cout << " owning " << State.m_UnitManager.m_PlayerUnits[Local.m_PlayerNr].size() << " units";
		else
			std::cout << " invalid id!";

		std::cout << "\n";
		const unsigned int BombsInUse = State.m_UnitManager.CountPlayerUnits(Local.m_PlayerNr, UNIT_TYPE_BOMB);
		std::cout << "explosion-size: " << State.m_Player[Local.m_PlayerNr].m_ExplosionSize << " ";
		std::cout << "bomb-nr: " << State.m_Player[Local.m_PlayerNr].m_BombNr << " ";
		std::cout << "bombs in use: " << BombsInUse << " ";

		if (Local.m_PlayerNr < 4)
			std::cout << "score: " << Global.m_Score[Local.m_PlayerNr] << " ";
		else
			std::cout << "score: - ";

		std::cout << "\n";

		PlayerControlType Action;

		if (State.m_UnitManager.CountPlayerUnits(Local.m_PlayerNr, UNIT_TYPE_HERO) > 0)
		{
			std::cout << "Please enter action:\n";
			if (Behaviour == "bot")
			{
				std::vector<std::pair<unsigned int, unsigned int>> playerPositions;
				for (unsigned int i = 0; i < State.m_UnitManager.m_PlayerUnits.size(); i++)
				{
					std::pair<unsigned int, unsigned int>& Pos = State.m_UnitManager.GetHeroPosition(i);
					playerPositions.push_back(Pos);
					if (Pos.first == -1 || Pos.second == -1)
						std::cout << "ERROR: player " << i << " has invalid position\n";
					else if (i == Local.m_PlayerNr)
						std::cout << "(my) ";
					std::cout << "position of player " << i << ": (" << Pos.first << "|" << Pos.second << ")\n";
				}

				Tile playerTile = Tile(playerPositions[Local.m_PlayerNr].first, playerPositions[Local.m_PlayerNr].second);
				std::vector<Tile> path = BFS(playerTile, TILE_TYPE_UPNR, State.m_LevelGrid);

				if (path.size() > 0) {
					Tile& targetTile = path[0];

					if (targetTile.iCol < (int)playerPositions[Local.m_PlayerNr].first)
						Action = PLAYER_CONTROL_MOVE_UP;
					else if (targetTile.iCol > (int)playerPositions[Local.m_PlayerNr].first)
						Action = PLAYER_CONTROL_MOVE_DOWN;
					else if (targetTile.iRow < (int)playerPositions[Local.m_PlayerNr].second)
						Action = PLAYER_CONTROL_MOVE_LEFT;
					else if (targetTile.iRow > (int)playerPositions[Local.m_PlayerNr].second)
						Action = PLAYER_CONTROL_MOVE_RIGHT;
					else
						Action = PLAYER_CONTROL_NONE;
				}
				else
					Action = PLAYER_CONTROL_NONE;
			}
			else if (Behaviour == "random")
			{
				const unsigned int r = rand() % 4;

				if (r == 0)
					Action = PLAYER_CONTROL_MOVE_UP;
				else if (r == 1)
					Action = PLAYER_CONTROL_MOVE_DOWN;
				else if (r == 2)
					Action = PLAYER_CONTROL_MOVE_LEFT;
				else if (r == 3)
					Action = PLAYER_CONTROL_MOVE_RIGHT;
				else
					Action = PLAYER_CONTROL_NONE;
			}
			else // if(Behaviour == "manual")
			{
				std::string Line;
				std::getline(std::cin, Line);

				if (Line == "w" || Line == "up")
					Action = PLAYER_CONTROL_MOVE_UP;
				else if (Line == "s" || Line == "down")
					Action = PLAYER_CONTROL_MOVE_DOWN;
				else if (Line == "a" || Line == "left")
					Action = PLAYER_CONTROL_MOVE_LEFT;
				else if (Line == "d" || Line == "right")
					Action = PLAYER_CONTROL_MOVE_RIGHT;
				else if (Line == "f" || Line == "fire")
					Action = PLAYER_CONTROL_BOMB;
				else if (Line == "t" || Line == "trap")
					Action = PLAYER_CONTROL_TRAP;
				else
					Action = PLAYER_CONTROL_NONE;
			}
		}
		else
		{
			std::cout << "Player has no hero-units - skipping input.\n";
		}

		memcpy((void *)Buffer, (void *)&Action, sizeof(PlayerControlType));

		if (SDLNet_TCP_Send(ServerSocket, (void *)Buffer, sizeof(PlayerControlType)) != sizeof(PlayerControlType))
		{
			std::cerr << "failed to send data to server\n";
			std::cerr << SDL_GetError();
			exit(5);
		}
	}

	// Cleanup and exit
	SDLNet_TCP_Close(ServerSocket);
	SDLNet_Quit();

	std::cout << "done\n";

	return EXIT_SUCCESS;
}
