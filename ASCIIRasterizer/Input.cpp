#include "Input.h"

#include <Windows.h>
#include <string>
#include <iostream>

#include "Screen.h"

using namespace std;

namespace Input
{
	bool keyboardprevious[MAX_KEYS]{};
	bool keyboardnow[MAX_KEYS]{};


	//void resetButtonStates(bool keyboard[MAX_KEYS])
	//{
	//	for(int i{ 0 }; i < MAX_KEYS; ++i)
	//	{
	//		keyboard[i] = false;
	//	}
	//}


	void updateKeyboard()
	{
		keyboardprevious[ENTER] = keyboardnow[ENTER];
		keyboardprevious[W] = keyboardnow[W];
		keyboardprevious[A] = keyboardnow[A];
		keyboardprevious[S] = keyboardnow[S];
		keyboardprevious[D] = keyboardnow[D];

		keyboardnow[ENTER] = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;
		keyboardnow[W] = (GetAsyncKeyState(0x57) & 0x8000) != 0 or (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
		keyboardnow[A] = (GetAsyncKeyState(0x41) & 0x8000) != 0 or (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
		keyboardnow[S] = (GetAsyncKeyState(0x53) & 0x8000) != 0 or (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
		keyboardnow[D] = (GetAsyncKeyState(0x44) & 0x8000) != 0 or (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
	}

	bool isPressed(KeyType key)
	{
		return keyboardnow[key];
	}
	bool wasPressed(KeyType key)
	{
		return keyboardprevious[key];
	}
	bool isDown(KeyType key)
	{
		return isPressed(key) and !wasPressed(key);
	}
	bool isHeld(KeyType key)
	{
		return isPressed(key) and wasPressed(key);
	}
	bool isUp(KeyType key)
	{
		return !isPressed(key) and wasPressed(key);
	}
	double inDouble(string message)
	{
		double d;
		do
		{
			std::cin.clear(); std::cin.ignore(5120, '\n');
			Screen::reset();
			Screen::print();
			Screen::moveCursorTo00();

			cout << message;

			cin >> d;
		} while(std::cin.fail());
		std::cin.clear(); std::cin.ignore(5120, '\n');

		return d;
	}
	void in3Double(string message, double& d1, double& d2, double& d3)
	{
		do
		{
			std::cin.clear(); std::cin.ignore(5120, '\n');
			Screen::reset();
			Screen::print();
			Screen::moveCursorTo00();

			cout << message;

			cin >> d1 >> d2 >> d3;
		} while(std::cin.fail());
		std::cin.clear(); std::cin.ignore(5120, '\n');
	}

}//end of namespace