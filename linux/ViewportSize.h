#pragma once

#include "ScreenSize.h"

namespace Rasterizer
{
	//Keep the same width/height ratio as screen 
	static constexpr double VIEW_HEIGHT{ 2.0 };
	static constexpr double VIEW_WIDTH{ .5 * Screen_::SCREEN_WIDTH / Screen_::SCREEN_HEIGHT * VIEW_HEIGHT }; //0.5 cuz each character is twice as tall wide
}



