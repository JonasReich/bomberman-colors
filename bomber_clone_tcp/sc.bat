
::@echo off
if [%1%]==[] (
	set "map=cross"
) else (
	set "map=%1"
)


:: server
start %~dp0bin\Release\bomber_clone_server\bomber_clone_server dat\%map%.ppm 1 2000

timeout 1

:: cerberus
:: start C:\Users\joreich\vorlesung_softwaretechnik\main\BomberCloneServer\bin\cerb3rus_ai_Release.exe

:: my bot
%~dp0bin\Release\bomber_clone_client\bomber_clone_client localhost 2000 bot clear
