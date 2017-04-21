=========================================================================================
Applications:
=========================================================================================
bin/Release/				-> Server + Client executables
-----------------------------------------------------------------------------------------
all_maps.cmd				-> launches the server for all maps in succession
-----------------------------------------------------------------------------------------
sc.bat					-> launches a server with 4 players and 2 bots
					   (mine and Dave's c3rberus bot)
-----------------------------------------------------------------------------------------
bot.bat					-> connects my bot to the tournament server


=========================================================================================
Maps:
=========================================================================================
dat/dijkstra.ppm			-> Custom Dijkstra Map


=========================================================================================
Source Files:
=========================================================================================
src/client/bomber_clone_client.cpp	-> Modified client script that contains the
					   majority of bot logic
-----------------------------------------------------------------------------------------
src/game_io.h				-> Modified I/O script that povides additional
game_io.cpp				   debugging tools and color console output
					   on windows machines
-----------------------------------------------------------------------------------------
src/server/bomber_clone_server.cpp	-> Added some lines to provide additional console
					   output (cycle + mapname) for improved debugging
-----------------------------------------------------------------------------------------
src/custom/				-> Additional Scripts not in the original project