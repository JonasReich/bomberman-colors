::@echo off
if [%1%]==[] (
	set "map=dijkstra"
) else (
	set "map=%1"
)

:: server
start %~dp0bin\server\Debug\bomber_clone_server dat\%map%.ppm 1 2000

timeout 1

:: client
start %~dp0bin\client\Debug\bomber_clone_client localhost 2000 random clear
