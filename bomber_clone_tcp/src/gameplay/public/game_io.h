#pragma once

#include "game_state.h"

// -----------------------------------------
// Game IO
// -----------------------------------------
// Based on Jakobs Game IO class, this version extends
// the ASCIIExport() function to accept a debug bool.
// When set to true, it colorizes all tiles according to
// the debug sets they have been added to.
// -----------------------------------------
class CGameIO
{
public:
	// Print a game state to the console
	// Setting _debug to true enables (colorized) debug mode
	// This is not tied to debug/release builds!
	static void ASCIIExport(const CGameState &State, bool _debug = false);
	static void PPMImport(std::istream &is, CGameState &State);
	static void PPMExport(std::ostream &os, const CGameState &State, const char *Comment);

	static void Save(std::ostream &os, const CGameState &State, const char *Comment);
	static void Load(std::istream &is, CGameState &State);

private:
	CGameIO();
};
