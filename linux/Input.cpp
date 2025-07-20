#include "Input.h"

//#include <Windows.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
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

	bool isKeyPressed(Display* d, KeySym keysym) {
	    char keys_return[32];
	    XQueryKeymap(d, keys_return);
	
	    KeyCode keycode = XKeysymToKeycode(d, keysym);
	    if (keycode == 0) return false;
	
	    return (keys_return[keycode / 8] & (1 << (keycode % 8))) != 0;
	}
	void updateKeyboard()
	{
		Display* d = XOpenDisplay(nullptr);
		keyboardprevious[ENTER] = keyboardnow[ENTER];
		keyboardprevious[W] = keyboardnow[W];
		keyboardprevious[A] = keyboardnow[A];
		keyboardprevious[S] = keyboardnow[S];
		keyboardprevious[D] = keyboardnow[D];


		keyboardnow[ENTER] = isKeyPressed(d, XK_Return);
	
		// W: W key or Up arrow
		keyboardnow[W] = isKeyPressed(d, XK_w) || isKeyPressed(d, XK_Up);
		
		// A: A key or Left arrow
		keyboardnow[A] = isKeyPressed(d, XK_a) || isKeyPressed(d, XK_Left);
		
		// S: S key or Down arrow
		keyboardnow[S] = isKeyPressed(d, XK_s) || isKeyPressed(d, XK_Down);
		
		// D: D key or Right arrow
		keyboardnow[D] = isKeyPressed(d, XK_d) || isKeyPressed(d, XK_Right);

		XCloseDisplay(d);
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
			Screen_::reset();
			Screen_::print();
			Screen_::moveCursorTo00();

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
			Screen_::reset();
			Screen_::print();
			Screen_::moveCursorTo00();

			cout << message;

			cin >> d1 >> d2 >> d3;
		} while(std::cin.fail());
		std::cin.clear(); std::cin.ignore(5120, '\n');
	}

}//end of namespace
