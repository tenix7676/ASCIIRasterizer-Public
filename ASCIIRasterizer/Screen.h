#pragma once
#include <string>


namespace Screen
{
	bool EnableVTMode();
	void moveCursorTo00();
	void makeCursorInvisible();
	void print();
	void reset();
	bool fitsInScreen(int x, int y);
	void drawNoCheck(int x, int y, char c);
	bool draw(int x, int y, char c);
	void drawLine(int x0, int y0, int x1, int y1);
	void drawLineHorizontal(int x0, int y0, int length, char c);
	void drawLineVertical(int x0, int y0, int height, char c);
	void writeStringOneLine(int x0, int y0, std::string s);
	void writeStringOneLineCentered(int x0, int y0, std::string s);
	void writeStringOneLineHighlighted(int x0, int y0, std::string s);
	void writeStringOneLineCenteredHighlighted(int x0, int y0, std::string s);
	void warningTooClose();
}