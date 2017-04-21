::@echo off

for %%f in (%~dp0dat\*.ppm) do (
	if exist %~dp0bin\Release\bomber_clone_server\bomber_clone_server.exe (
		if exist %~dp0bin\Release\bomber_clone_client\bomber_clone_client.exe (
			%~dp0sc %%~nf
		)
	)
)
