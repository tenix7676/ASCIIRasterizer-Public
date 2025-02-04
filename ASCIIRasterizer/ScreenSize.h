#pragma once

namespace Screen
{
	static constexpr int SCREEN_WIDTH{ 70*3/2};
	static constexpr int SCREEN_HEIGHT{ 20*3/2 };
	//Each 1 character in the x direction in actuality is 0.5 length in the x direction
	//So the screen's dimensions are (screen_width / 2) x (screen_height)
	//with the smallest x difference dx == 0.5, and the smallest y difference dy == 1  
}
