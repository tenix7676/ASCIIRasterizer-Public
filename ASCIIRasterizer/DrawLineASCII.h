#pragma once

#include "Slope.h"

namespace DrawLineASCII
{
	void drawLine(int x0, int y0, int x1, int y1);
	void drawLineHorizontalSpecificChar(int x0, int y0, int length, char c);
	void drawLineVerticalSpecificChar(int x0, int y0, int height, char c);

	//void drawSlopeFull(SlopeEnum slope, int x0, int y0, int delta_x, int delta_y, bool up);
}