#pragma once

#include <string>

enum KeyType
{
	W,
	A,
	S,
	D,
	ENTER,
	MAX_KEYS
};

namespace Input
{
	void updateKeyboard();
	bool isDown(KeyType key);
	bool isHeld(KeyType key);
	bool isUp(KeyType key);
	double inDouble(std::string message);
	void in3Double(std::string message, double& x, double& y, double& z);
}