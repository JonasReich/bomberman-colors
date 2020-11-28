#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "net_shared.h"

#include "game_server.h"

#include "game_io.h"
#include "game_play.h"
#include "game_sim.h"
#include "game_state.h"
#include "game_state_io.h"
#include "player.h"

#include "sleep.h"


#define MAX_CLIENTS 4
// MUST BE SAME AS CLIENT BUFFER-SIZE
// IN CASE Of CRASH RECOMPILE & CHECK FOR OVERFLOW
#define BUFFER_SIZE 100000


int32_t main(int32_t argc, char **argv)
{
    std::cout << "starting dedicated server...\n";

	/*
	Level List:
	0. butterfly:	complex level
	1. grid:		grid, no destructibles / upgrades
	2. test3:		few upgrades, labyrinth
	*/

    const char *LevelName = (argc > 1) ? argv[1] : "../../dat/dijkstra.ppm";
    const uint32_t NrOfClients = (argc > 2) ? (atoi(argv[2]) > 4) ? 4 : atoi(argv[2]) : 1;
    const Uint16 Port = (argc > 3) ? atoi(argv[3]) : 2000;

    std::cout << "server: ";
    std::cout << "level " << LevelName << ", ";
    std::cout << NrOfClients << " clients, ";
    std::cout << "port " << Port << "\n";

    std::cout << "initializing SDL_Net...\n";
    if(SDLNet_Init() < 0)
    {
        std::cerr << "SDLNet_Init: " << SDLNet_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    TCPsocket ServerSocket;
    IPaddress ServerIP;

    std::cout << "resolving server ip...\n";
    if(SDLNet_ResolveHost(&ServerIP, 0, Port))
    {
        std::cerr << SDL_GetError() << "\n";
        exit(3); // TODO
    }
    std::cout << "Server IP: ";
    std::cout << CNet::TranslateAddr(ServerIP.host);
    std::cout << ", port: " << ServerIP.port;
    std::cout << "\n";

    std::cout << "opening server socket...\n";
    ServerSocket = SDLNet_TCP_Open(&ServerIP);
    if(!ServerSocket)
    {
        std::cerr << SDL_GetError() << "\n";
        exit(4); // TODO
    }

    std::vector<TCPsocket> ClientSocket(MAX_CLIENTS);

    std::cout << "listening at port " << Port << "...\n";
    uint32_t iClient;
    for(iClient = 0; iClient < NrOfClients; iClient++)
    {
        std::cout << "waiting for client " << iClient << "...\n";
        //std::cout << "waiting for client " << iClient << " of " << NrOfClients << "...\n";

        do
        {
            ClientSocket[iClient] = SDLNet_TCP_Accept(ServerSocket);
        }
        while(!ClientSocket[iClient]);
        std::cout << "client " << iClient << " connected ";
        IPaddress *ClientIP = SDLNet_TCP_GetPeerAddress(ClientSocket[iClient]);
        if(ClientIP)
        {
            std::cout << "(IP ";
            std::cout << CNet::TranslateAddr(ClientIP->host);
            std::cout << " port " << ClientIP->port << ")";
        }
        std::cout << "\n";
    }
    
    std::cout << "receiving player names...\n";
    std::map<int, std::string> PlayerNames;
    for(iClient = 0; iClient < NrOfClients; iClient++)
    {
        char PlayerName[16];
        if(SDLNet_TCP_Recv(ClientSocket[iClient], (void *)PlayerName, sizeof(PlayerName)) != sizeof(PlayerName))
        {
            std::cerr << "failed to receive player-name from client\n";
            std::cerr << SDL_GetError();
            exit(5);
        }

        std::cout << "Player " << iClient << ": " << PlayerName << "\n";
        PlayerNames[iClient] = PlayerName;
    }

    std::cout << "notifying clients...\n";
    for(iClient = 0; iClient < NrOfClients; iClient++)
    {
        CLocalState Local;
        Local.m_PlayerNr = iClient;

        if(SDLNet_TCP_Send(ClientSocket[iClient], (void *)(&Local), sizeof(CLocalState)) != sizeof(CLocalState))
        {
            std::cerr << "failed to notify client\n";
            std::cerr << SDL_GetError();
            exit(5);
        }
    }

    std::cout << "dedicated server running.\n";

    std::cout << "allocating buffer...\n";
    char Buffer[BUFFER_SIZE];

    CGlobalState Global;

    bool Quit = false;

    // Round-loop
    while(!Quit)
    {        
        CGameState State; // use a completely new game-state every round

        std::cout << "loading level \"" << LevelName << "\"...\n";
        std::ifstream LevelLoadStream(LevelName);

        CGameIO::PPMImport(LevelLoadStream, State);
        if(State.m_LevelGrid.Width() < 1 || State.m_LevelGrid.Height() < 1)
        {
            std::cerr << "failed to load level \"" << LevelName << "\"\n";
            exit(EXIT_FAILURE);
        }

        std::cout << "round " << Global.m_Round << "\n";
        std::cout << "spawning players...\n";

        for(iClient = 0; iClient < NrOfClients; iClient++)
        {
            State.m_Player.push_back(CPlayer());
            State.m_UnitManager.m_PlayerUnits.push_back(std::vector<CUnit>());
            State.m_UnitManager.m_PlayerUnits[iClient].clear();

            uint32_t SpawnX = ((iClient >> 0) & 1) ? 1 : State.m_LevelGrid.Width() - 2;
            uint32_t SpawnY = ((iClient >> 1) & 1) ? 1 : State.m_LevelGrid.Height() - 2;

            const CUnit NewPlayerUnit(iClient, EUnitType::Hero, SpawnX, SpawnY, 0);
            State.m_UnitManager.m_PlayerUnits[iClient].push_back(NewPlayerUnit);
        }

        // TEST: Additional player without heroes who owns non-player bombs and traps.
        {
            State.m_Player.push_back(CPlayer());
            State.m_UnitManager.m_PlayerUnits.push_back(std::vector<CUnit>());
            State.m_UnitManager.m_PlayerUnits[iClient].clear();
            //State.m_UnitManager.m_PlayerUnits[iClient].push_back(CUnit(iClient, EUnitType::Bomb, 1, 2, 0));
            for(uint32_t v = 0; v < State.m_LevelGrid.Height(); v++)
            {
                for(uint32_t u = 0; u < State.m_LevelGrid.Width(); u++)
                {
                    const ETileType Tile = State.m_LevelGrid.Get(u, v);
                    if(Tile == ETileType::Trap) // spawn trap
                    {
                        State.m_LevelGrid.Set(u, v, ETileType::Free);
                        State.m_UnitManager.m_PlayerUnits[iClient].push_back(CUnit(iClient, EUnitType::Bomb, u, v, 0));
                    }
                    else if(Tile == ETileType::Fuse) // spawn bomb
                    {
                        State.m_LevelGrid.Set(u, v, ETileType::Free);
                        State.m_UnitManager.m_PlayerUnits[iClient].push_back(CUnit(iClient, EUnitType::Bomb, u, v, 1));
                    }
                }
            }
        }

        Global.m_Cycle = 0;
        bool Finish = false;

        std::vector<PlayerControlType> Action;
        Action.resize(NrOfClients);

        // Main loop
        while(!Quit && !Finish)
        {
            // For debug only:
            system("cls");
			std::cout << "level: " << LevelName << "\n";
			std::cout << "cycle: " << Global.m_Cycle << "\n";
            CGameIO::ASCIIExport(State);

            // distribute game-state to clients
            uint32_t ConnectionFailsSend = 0;
            for(iClient = 0; iClient < NrOfClients; iClient++)
            {
                CLocalState Local;
                Local.m_PlayerNr = iClient;
                int32_t Len = CGameStateIO::Export(
                        State, Local, Global,
                        (char *)Buffer); // NOTE: ON CRASH ASSERT LEN < BUFFER_SIZE

                if(SDLNet_TCP_Send(ClientSocket[iClient], (void *)Buffer, BUFFER_SIZE) < BUFFER_SIZE)
                {
                    std::cout << "failed to send data to client " << iClient << "\n";
                    ConnectionFailsSend++;
                }
            }

            if(ConnectionFailsSend >= NrOfClients)
                Quit = true;

            // receive action-requests from clients
            uint32_t ConnectionFailsReceive = 0;
            for(iClient = 0; iClient < NrOfClients; iClient++)
            {
                if(State.m_UnitManager.CountPlayerUnits(iClient, EUnitType::Hero) <= 0)
                {
                    std::cout << "skipping hero-less player " << iClient << "\n";
                    continue;
                }

                std::cout << "receiving from client " << iClient << "\n";
                Action[iClient] = PLAYER_CONTROL_NONE;
                if(SDLNet_TCP_Recv(ClientSocket[iClient], (void *)(&(Action[iClient])), sizeof(PlayerControlType)) != sizeof(PlayerControlType))
                {
                    std::cerr << "failed to receive data from client " << iClient << "\n";
                    ConnectionFailsReceive++;
                }
                else
                {
                    std::cout << "client sent " << Action[iClient] << "\n";
                }
            }

            if(ConnectionFailsReceive >= NrOfClients)
                 Quit = true;

            CSleep::Do(50);

            // called once every round
            State = CGameSim::UpdateWorld(State, Action);
        
            uint32_t AliveCount = 0;
            for(iClient = 0; iClient < State.m_UnitManager.m_PlayerUnits.size(); iClient++)
            {
                if(State.m_UnitManager.CountPlayerUnits(iClient, EUnitType::Hero) > 0)
                    AliveCount++;
                else
                    std::cout << "client " << iClient << " has no more heros\n";
            }

            if(NrOfClients > 1)
            {
                if(AliveCount < 2)
                    Finish = true;
            }
            else
            {
                if(AliveCount < 1)
                    Finish = true;
            }

            Global.m_Cycle++;
        }

        for(iClient = 0; iClient < State.m_UnitManager.m_PlayerUnits.size(); iClient++)
        {
            if(State.m_UnitManager.CountPlayerUnits(iClient, EUnitType::Hero) > 0)
                Global.m_Score[iClient]++;
        }

        std::cout << "round complete\n";

        for(iClient = 0; iClient < State.m_UnitManager.m_PlayerUnits.size(); iClient++)
        {
            //std::cout << "Player " << iClient << " score " << Global.m_Score[iClient] << "\n";
            std::cout << "Player " << PlayerNames[iClient] << " score " << Global.m_Score[iClient] << "\n";
        }

        std::string Dummy;
        std::getline(std::cin, Dummy);

        Global.m_Round++;
    }

    std::cout << "shutting down server...\n";

    // Cleanup and exit
    SDLNet_TCP_Close(ServerSocket);
    for(iClient = 0; iClient < NrOfClients; iClient++)
    {
        SDLNet_TCP_Close(ClientSocket[iClient]);
    }

    SDLNet_Quit();

    std::cout << "done.\n";

    return EXIT_SUCCESS;
}
