#include "Screen.h"

#include <Windows.h>
#include <iostream>

#include "ScreenSize.h"
#include "DrawLineASCII.h"

using namespace std;


namespace Screen
{

	char screen[SCREEN_HEIGHT][SCREEN_WIDTH+1] = { ' ' };
	bool screenColor[SCREEN_HEIGHT][SCREEN_WIDTH] = { false };


#ifdef DEBUG
	bool is_paused{ false };

	void pause()
	{
		is_paused = true;
	}
	void unpause()
	{
		is_paused = false;
	}
#endif

	bool EnableVTMode()
	{
		// Set output mode to handle virtual terminal sequences
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hOut == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		DWORD dwMode = 0;
		if (!GetConsoleMode(hOut, &dwMode))
		{
			return false;
		}

		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		if (!SetConsoleMode(hOut, dwMode))
		{
			return false;
		}
		return true;
	}

	void makeCursorInvisible()
	{
		cout << "\x1b[?25l";
	}
	void moveCursorTo00()
	{
		cout << "\x1b[H";//move cursor to 1,1
		cout << "\x1b[1A";//move cursor up by one
	}

	void print()
	{
#ifdef DEBUG
		if (!is_paused)
		{
			makeCursorInvisible();
			moveCursorTo00();
			for (int y{ 0 }; y < SCREEN_HEIGHT; ++y)
			{
				for (int x{ 0 }; x < SCREEN_WIDTH; ++x)
				{
					cout << screen[y][x];
				}
				cout << '\n';
			}
		}
#else
		makeCursorInvisible();
		moveCursorTo00();
		for (int y{ 0 }; y < SCREEN_HEIGHT; ++y)
		{
			bool color_found{ false };
			for(int x{ 0 }; x < SCREEN_WIDTH; ++x)
			{
				color_found = color_found or screenColor[y][x];
			}
			if(color_found)
			{
				for(int x{ 0 }; x < SCREEN_WIDTH; ++x)
				{
					if(screenColor[y][x])
					{
						cout << "\x1b[7m"; //invert color
						cout << screen[y][x];
					}
					else
					{
						cout << "\x1b[27m"; //normal color
						cout << screen[y][x];
					}
				}
				
			}
			if(!color_found)
			{
				cout << "\x1b[27m"; //set to normal color
				cout << screen[y];
			}

			cout << '\n';
		}
#endif
	}

	void reset()
	{
#ifdef DEBUG
		if (!is_paused)
		{
			for (int y{ 0 }; y < SCREEN_HEIGHT; ++y)
			{
				for (int x{ 0 }; x < SCREEN_WIDTH; ++x)
				{
					screen[y][x] = ' ';
				}
			}
		}
#else
		for (int y{ 0 }; y < SCREEN_HEIGHT; ++y)
		{
			for (int x{ 0 }; x < SCREEN_WIDTH; ++x)
			{
				screen[y][x] = ' ';
				screenColor[y][x] = false;
			}
			screen[y][SCREEN_WIDTH] = '\0';
		}
#endif
	}

	bool fitsInScreenWidth(int screen_x)
	{
		return 0 <= screen_x and screen_x < SCREEN_WIDTH;
	}

	bool fitsInScreenHeight(int screen_y)
	{
		return 0 <= screen_y and screen_y < SCREEN_HEIGHT;
	}

	bool fitsInScreen(int x, int y)
	{
		return fitsInScreenWidth(x) and fitsInScreenHeight(y);
	}

	void drawNoCheck(int x, int y, char c)
	{
		screen[y][x] = c;
	}
	bool draw(int x, int y, char c)
	{
		if (!fitsInScreen(x, y))
			return false;
		if (c != '\0')//This could be moved to drawSlopeOnce() to avoid unnecessary checks
			drawNoCheck(x, y, c);

		return true;
	}
	void drawLine(int x0, int y0, int x1, int y1)
	{
		DrawLineASCII::drawLine(x0, y0, x1, y1);
	}
	void drawLineHorizontal(int x0, int y0, int length, char c)
	{
		DrawLineASCII::drawLineHorizontalSpecificChar(x0, y0, length, c);
	}
	void drawLineVertical(int x0, int y0, int height, char c)
	{
		DrawLineASCII::drawLineVerticalSpecificChar(x0, y0, height, c);
	}
	//void writeOneLineString(int x0, int y0, string s)
	//{
	//	for(int x{ 0 }; x < s.size(); ++x)
	//		draw(x0 + x, y0, s[x]);
	//}
	void writeStringOneLine(int x0, int y0, string s)
	{
		for(int x{ 0 }; x < s.size(); ++x)
		{
			draw(x0 + x, y0, s[x]);
		}
	}
	void writeStringOneLineCentered(int x0, int y0, std::string s)
	{
		writeStringOneLine(x0 - s.size() / 2, y0, s);
	}


	void writeStringOneLineHighlighted(int x0, int y0, std::string s)
	{
		for(int x{ 0 }; x < s.size(); ++x)
		{
			draw(x0 + x, y0, s[x]);
			screenColor[y0][x0 + x] = true;
		}
	}
	void writeStringOneLineCenteredHighlighted(int x0, int y0, std::string s)
	{
		writeStringOneLineHighlighted(x0 - s.size() / 2, y0, s);
	}

	void warningTooClose()
	{
		writeStringOneLine(0, 0, "Warning: Points too close to viewport!");
	}


}//end of namespace