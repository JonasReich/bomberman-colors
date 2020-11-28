#pragma once
#include "game_play.h"

enum EDirection {
	kDirection_Up,
	kDirection_Right,
	kDirection_Down,
	kDirection_Left,
	//..
	kDirection_NumOf,
};

static const PlayerControlType kPlayerMoveFromDirection[] =
{
	PLAYER_CONTROL_MOVE_UP, //kDirection_Up,
	PLAYER_CONTROL_MOVE_RIGHT,//kDirection_Right,
	PLAYER_CONTROL_MOVE_DOWN,//kDirection_Down,
	PLAYER_CONTROL_MOVE_LEFT,//kDirection_Left,
	////..
	PLAYER_CONTROL_NONE//kDirection_NumOf,
};
