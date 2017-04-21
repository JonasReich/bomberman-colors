# bomberman-colors
Colorized ASCII Interpreter for MD.H Bomberman Exercise

The directory structure and base of the project were copied from Jakob Thomsens and Christoph Minnameiers
bomberman AI exercise at [Mediadesign University of Applied Sciences](http://www.mediadesign.de/).

The main project source code, C++ project, compiled executables and ppm-maps are in the 'bomber_clone_tcp' directory.
The 'external' directory contains all external third-party libraries (SDL and SDL_net).

## Executables
All of these are in the 'bomber_clone_tcp' directory:

| File              | Description                                                          |
|-------------------|----------------------------------------------------------------------|
| bin/Release/      | Server + Client executables                                          |
| client.cmd        | Launches the client and attempts to connect to localhost             |
| all_maps.bat      | Launches the server and client with all available maps in succession |
| server_client.bat | Launches client and server with my custom "Dijkstra" map             |

## Custom Map
I've added a [custom map](bomber_clone_tcp/dat/dijkstra.ppm) to specifically test bots for correct
implementation of Dijkstra pathfinding.

## Source Code
All custom code - that is code added or modified by the student or not included in the original
project - is located under 'src/custom'.

| bomer_clone_client | Modified client script that calls the colorized debugger |
|--------------------|----------------------------------------------------------|
| color_debug        | Main logic for colorized output                          |
| ctile              | Slightly modified tile class                             |
| defines            | Directions and PlayerControlTypes                        |
| vectorExtensions   | Adds a VectorContains() function which I used A LOT      |
