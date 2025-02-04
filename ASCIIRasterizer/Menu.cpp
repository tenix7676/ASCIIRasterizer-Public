#include "Menu.h"

#include <string>

#include "Screen.h"
#include "ScreenSize.h"
#include "DrawLineASCII.h"
#include "Input.h"

using namespace std;


namespace Menu
{
	string menu_option_strings[MAX_MENUOPTIONS] = {
		"Run animation 1",
		"Run animation 2",
		"Run animation 3",
		"Set up and run your own animation"
	};
	string submenu_option_strings[MAX_SUBMENUOPTIONS] = {
		"Turn cube with wasd",
		"Turn cube around x axis by angle",
		"Turn cube around y axis by angle",
		"Turn cube around z axis by angle",
		"Set cube position",
		"Set camera position",
		"Run Animation"
	};



	const char LINE_HORIZONTAL = 0xC4;
	const char LINE_VERTICAL = 0xB3;
	const char UPPER_LEFT_CORNER = 0xDA;
	const char UPPER_RIGHT_CORNER = 0xBF;
	const char LOWER_LEFT_CORNER = 0xC0;
	const char LOWER_RIGHT_CORNER = 0xD9;

	void drawBoxedList(int menu_x, int menu_y, int menu_width, int menu_height, int option_cursor_positon, string* list, int list_length)
	{
		//Draw sides
		Screen::drawLineHorizontal(menu_x + 1, menu_y, menu_width - 2, LINE_HORIZONTAL);
		Screen::drawLineHorizontal(menu_x + 1, menu_y + menu_height - 1, menu_width - 2, LINE_HORIZONTAL);
		Screen::drawLineVertical(menu_x, menu_y + 1, menu_height - 2, LINE_VERTICAL);
		Screen::drawLineVertical(menu_x + menu_width - 1, menu_y + 1, menu_height - 2, LINE_VERTICAL);

		//Draw corners
		Screen::draw(menu_x, menu_y, UPPER_LEFT_CORNER);
		Screen::draw(menu_x + menu_width - 1, menu_y, UPPER_RIGHT_CORNER);
		Screen::draw(menu_x, menu_y + menu_height - 1, LOWER_LEFT_CORNER);
		Screen::draw(menu_x + menu_width - 1, menu_y + menu_height - 1, LOWER_RIGHT_CORNER);

		for(int i{ 0 }; i < list_length; ++i)
		{
			if(i == option_cursor_positon)
				Screen::writeStringOneLineCenteredHighlighted(menu_x + menu_width / 2, menu_y + menu_height / 2 - list_length / 2 + i, list[i]);
			else
				Screen::writeStringOneLineCentered(menu_x + menu_width / 2, menu_y + menu_height / 2 - list_length / 2 + i, list[i]);
		}
	}

	void drawMenu(int menu_x, int menu_y, int menu_width, int menu_height, int option_cursor_positon)
	{
		drawBoxedList(menu_x, menu_y, menu_width, menu_height, option_cursor_positon, menu_option_strings, MAX_MENUOPTIONS);
	}

	void drawSubMenu(int menu_x, int menu_y, int menu_width, int menu_height, int option_cursor_positon)
	{
		drawBoxedList(menu_x, menu_y, menu_width, menu_height, option_cursor_positon, submenu_option_strings, MAX_SUBMENUOPTIONS);
	}


	MenuOptions openMenu()
	{
		int option_cursor_positon = 0;
		int menu_width = Screen::SCREEN_WIDTH * 3 / 4; //75% of screen 
		int menu_height = Screen::SCREEN_HEIGHT * 3 / 4;
	
		while(true)
		{
			Screen::reset();
			drawMenu(Screen::SCREEN_WIDTH / 2 - menu_width / 2, 1, menu_width, menu_height, option_cursor_positon);
			Screen::print();

			Input::updateKeyboard();
			if(Input::isDown(S))
			{
				if(option_cursor_positon < MAX_MENUOPTIONS - 1)
					++option_cursor_positon;
			}
			if(Input::isDown(W))
			{
				if(option_cursor_positon > 0)
					--option_cursor_positon;
			}

			if(Input::isDown(ENTER))
				return static_cast<MenuOptions>(option_cursor_positon);
		}
	}

	SubMenuOptions openSubMenu()
	{
		int option_cursor_positon = 0;
		int menu_width = Screen::SCREEN_WIDTH * 3 / 4; //75% of screen 
		int menu_height = Screen::SCREEN_HEIGHT * 3 / 4;

		while(true)
		{
			Screen::reset();
			drawSubMenu(Screen::SCREEN_WIDTH / 2 - menu_width / 2, 1, menu_width, menu_height, option_cursor_positon);
			Screen::print();

			Input::updateKeyboard();
			if(Input::isDown(S))
			{
				if(option_cursor_positon < MAX_SUBMENUOPTIONS - 1)
					++option_cursor_positon;
			}
			if(Input::isDown(W))
			{
				if(option_cursor_positon > 0)
					--option_cursor_positon;
			}

			if(Input::isDown(ENTER))
				return static_cast<SubMenuOptions>(option_cursor_positon);
		}
	}

}//end of namespace