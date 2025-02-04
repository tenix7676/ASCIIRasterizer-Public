#pragma once

#include "Fraction.h"


//When adding a new slope remember to update
//1. MAX_DX, MAX_DY
//2. SlopeEnum
//3. fractions[] in slope.cpp
//4. patterns in slope.cpp


enum SlopeEnum : short
{
	//Hard coded slopes:
	//WARNING! this enum and fractions should contain at least 2 elements, otherwise the program will go out of array bounds
	//widest and highest slopes first, (must match Slope::MAX_DX and Slope::MAX_DY)
	SLOPE_WIDE,
	SLOPE_HIGH,//this must match HIGHEST_SLOPE_DY

	SLOPE_1_1,
	SLOPE_1_2,
	SLOPE_2_3,
	SLOPE_3_2,
	//wider and higher slopes, edit accordingly to the widest and highest slopes, with a number +1
	//so if the widest slope is SLOPE_1_5 then SLOPE_1_GREATER_THAN_6 ends in a 6
	SLOPE_WIDER, //the slope is WIDER than WIDE
	SLOPE_HIGHER, //the slope is HIGHER than HIGH

	MAX_SLOPE_FRACTIONS,
	//Special slopes, don't touch these
	SLOPE_1_0,
	SLOPE_0_1,
	MAX_SLOPES
};


namespace Slope
{
	const int WIDER_SLOPE_DX{ 3 };
	const int HIGHER_SLOPE_DY{ 2 };
	const int MAX_DY{ 3 };
	const int MAX_DX{ 3 };
	extern const Fraction fractions[MAX_SLOPE_FRACTIONS];
	extern const char patterns[MAX_SLOPE_FRACTIONS][MAX_DY][MAX_DX];
}
