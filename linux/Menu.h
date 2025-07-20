#pragma once


enum MenuOptions : short
{
	ANIM1,
	ANIM2,
	AMIM3,
	SETUP,
	MAX_MENUOPTIONS
};

enum SubMenuOptions : short
{
	WASD,
	TURN_X,
	TURN_Y,
	TURN_Z,
	WIREFRAME_POS,
	CAMERA_POS,
	PLAY_ANIM,
	MAX_SUBMENUOPTIONS
};

namespace Menu
{
	MenuOptions openMenu();
	SubMenuOptions openSubMenu();
}