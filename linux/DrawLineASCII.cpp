#include "DrawLineASCII.h"


#include "Screen.h"
#include "Slope.h"
#include "Fraction.h"

namespace DrawLineASCII
{
	//const char X_SEPERATOR{ '`' };
	//const char Y_SEPERATOR{ '|' };

	const char HORIZONTAL{ '-' };
	const char VERTICAL{ '|' };

	//TODO
	// Get rid of 2_1 and 3_1 and just make GREATER_THAN_1_1
	// 
	// 
	// 
	// drawLine() -> aproximateLine():
	// DONE draw 1_0
	// DONE draw 0_1
	// DONE draw GREATER_THAN_1_3 
	// DONE draw GREATER_THAN_3_1
	// DONE choose x overshot or y overshot or both fall too short:
	//		DONE drawSlopeX()*
	//		DONE drawSlopeY()*
	//		DONE drawSLopeXY()*
	// *DONE make it so that the last section doesnt end with a seperator


	//Warning: Arrays MUST be the same size
	void copyArray(Fraction* copy_into, const Fraction* copy_from, int size)
	{
		for (int i{ 0 }; i < size; ++i)
		{
			copy_into[i] = copy_from[i];
		}
	}




	SlopeEnum aproximateSlope(int delta_x, int delta_y)
	{
		// +--------------------------+
		// | Deal with special slopes |
		// +--------------------------+

		if (delta_x == 0)
			return SLOPE_1_0;
		if (delta_y == 0)
			return SLOPE_0_1;

		Fraction deltay_deltax{ delta_y, delta_x };

		if (deltay_deltax < Slope::fractions[SLOPE_WIDER])
			return SLOPE_WIDER;
		if (deltay_deltax > Slope::fractions[SLOPE_HIGHER])
			return SLOPE_HIGHER;

		// +-----------------------------+
		// | Deal with hard coded slopes |
		// +-----------------------------+

		Fraction differences[MAX_SLOPE_FRACTIONS] = {};
		copyArray(differences, Slope::fractions, MAX_SLOPE_FRACTIONS);

		//Find the closest slope from defined slopes to the actual slope (deltay_deltax)
		int closest_slope_index{ 0 };
		int i{ 0 };
		for (; i < MAX_SLOPE_FRACTIONS; ++i)
		{
			differences[i] -= deltay_deltax;

			if (differences[i] == 0)
			{
				closest_slope_index = i;
				break;
			}

			//Take the absolute value
			if (differences[i] < 0) differences[i] *= -1;

			//Find the smallest difference
			if (differences[i] < differences[closest_slope_index])
				closest_slope_index = i;
		}

		return static_cast<SlopeEnum>(closest_slope_index);
	}
	
	void distribute(int parts[Slope::MAX_DX], int number)
	{
		for(int i{ 0 }; i < number; ++i)
		{
			++parts[i % Slope::MAX_DX];
		}

	}
	void distribute(int* parts, int number, int parts_length)
	{
		for(int i{ 0 }; i < number; ++i)
		{
			++parts[i % parts_length];
		}

	}
	//Distrubutes number evenly from starting from the end
	void distributeEvenly(int* parts, int number, int parts_length)
	{
		int surplus_number = number % parts_length;
		distribute(parts, number - surplus_number, parts_length);
		if(surplus_number == 0)
			return;

		for(int i{ 1 }; i <= surplus_number; ++i)
		{
			//int index = parts_length - 1 - ((parts_length) / (surplus_number) * i);
			int index = parts_length * i / (surplus_number + 1)  - 1;
			++parts[index];
		}
	}


	void drawLineHorizontalSpecificChar(int x0, int y0, int length, char c)
	{
		for(int x{ 0 }; x < length; ++x)
			Screen_::draw(x0 + x, y0, c);
	}
	void drawLineHorizontal(int x0, int y0, int length)
	{
		if(length <= 0)
			return;

		drawLineHorizontalSpecificChar(x0, y0, length, '-');
	}
	void drawLineHorizontalSloped(int x0, int y0, int length, bool up=false)
	{
		if(length <= 0)
			return;

		int smaller_sections_lengths[Slope::MAX_DX] = { 0 };
		distribute(smaller_sections_lengths, length);
		int x{ 0 };
		for(int i{ 0 }; i < Slope::MAX_DX; ++i)
		{
			if(up) drawLineHorizontalSpecificChar(x0 + x, y0, smaller_sections_lengths[i], Slope::patterns[0][0][Slope::MAX_DX - i - 1]);
			else   drawLineHorizontalSpecificChar(x0 + x, y0, smaller_sections_lengths[i], Slope::patterns[0][0][i]);
			x += smaller_sections_lengths[i];
		}
	}
	void drawLineVerticalSpecificChar(int x0, int y0, int height, char c)//Mainly just for completness, used in menu.h
	{
		for(int y{ 0 }; y < height; ++y)
			Screen_::draw(x0, y0 + y, c);
	}
	void drawLineVertical(int x0, int y0, int height, bool up=false)
	{
		if(height <= 0)
			return;

		if(height == 1) //looks better
		{
			Screen_::draw(x0, y0, '.');
			return;
		}

		if(up)
		{
			for(int y{ 0 }; y < height; ++y)
			{
				Screen_::draw(x0, y0 - y, Slope::patterns[1][0][0]);
			}
		}
		else
		{
			for(int y{ 0 }; y < height; ++y)
			{
				Screen_::draw(x0, y0 + y, Slope::patterns[1][0][0]);
			}
		}
	}
	void drawLineVerticalSloped(int x0, int y0, int height, bool up=false)
	{
		if(height <= 0)
			return;

		if(up) 
		{
			for(int y{ 0 }; y < height - 1; ++y)
			{
				Screen_::draw(x0, y0 - y, Slope::patterns[1][0][0]);
			}
			Screen_::draw(x0, y0 - (height - 1), '.'); //Use the dot when going up
		}
		else
		{
			for(int y{ 0 }; y < height - 1; ++y)
			{
				Screen_::draw(x0, y0 + y, Slope::patterns[1][0][0]);
			}
			Screen_::draw(x0, y0 + (height - 1), Slope::patterns[1][Slope::HIGHER_SLOPE_DY - 1][0]);
		}
	}

	void drawSlopeOnce(SlopeEnum slope, int x0, int y0, bool up)
	{
		const int dx = Slope::fractions[slope].denominator;
		const int dy = Slope::fractions[slope].numerator;

		if(up)
		{
			for(int y{ 0 }; y < dy; ++y)
				for(int x{ 0 }; x < dx; ++x)
				{
					//swap the '\\' wiht '/; and vice versa
					char c{ Slope::patterns[slope][dy - y -1][dx - x - 1] };
					if     (c == '\\') c = '/';
					else if(c == '/')  c = '\\';

					Screen_::draw(x0 + x, y0 - (y), c);
				}
		}
		else
		{ 
			for(int y{ 0 }; y < dy; ++y)
				for(int x{ 0 }; x < dx; ++x)
				{
					Screen_::draw(x0 + x, y0 + y, Slope::patterns[slope][y][x]);
				}
		}
	}
	
	void drawSlopeFull(SlopeEnum slope, int x0, int y0, int delta_x, int delta_y, bool up)
	{
		int dx = Slope::fractions[slope].denominator;
		int dy = Slope::fractions[slope].numerator;

		if(slope == SLOPE_WIDER)
		{
			dy = 1;
			dx = delta_x / delta_y;
		}
		else if(slope == SLOPE_HIGHER)
		{
			dy = delta_y / delta_x;
			dx = 1;
		}

		int steps{ delta_x / dx };
		int premature_x = steps * dx;
		int premature_y = steps * dy;

		//x will never overshoot becaues delta_x / dx * dx <= delta_x

		//y overshot
		if(premature_y > delta_y)
		{
			//The new amount of steps can only be smaller
			steps = delta_y / dy;
			premature_x = steps * dx;
			premature_y = steps * dy;
		}

		int left_over_x = delta_x - premature_x;
		int left_over_y = delta_y - premature_y;


		int* x_seperation_lengths = new int[steps]{ 0 };
		int* y_seperation_heights = new int[steps]{ 0 };

		distributeEvenly(x_seperation_lengths, left_over_x, steps);
		distributeEvenly(y_seperation_heights, left_over_y, steps);

		int x{ 0 };
		int y{ 0 };


		for(int step{ 0 }; step < steps; ++step)
		{
			if(slope == SLOPE_WIDER)
			{
				if(!(dy == 1 and x_seperation_lengths[step] > 0)) //only for a special case, so it looks better, not too important
				{
					drawLineHorizontalSloped(x0 + x, y0 + y, dx, up);
					x += dx;
					if(up) y -= 1;
					else   y += 1;
				}
			}
			else if(slope == SLOPE_HIGHER)
			{
				drawLineVerticalSloped(x0 + x, y0 + y, dy, up);
				x += 1;
				if(up) y -= dy;
				else   y += dy;
			}
			else
			{
				if(!(dy == 1 and x_seperation_lengths[step] > 0)) //only for a special case, so it looks better, not too important
				{
					drawSlopeOnce(slope, x0 + x, y0 + y, up);
					x += dx;
					if(up) y -= dy;
					else   y += dy;
				}
			}
			drawLineVerticalSloped(x0 + x, y0 + y, y_seperation_heights[step], up);
			if (up) y -= y_seperation_heights[step];
			else   y += y_seperation_heights[step];

			if(dy == 1 and x_seperation_lengths[step] > 0) //only for a special case, so it looks better, not too important
			{
				drawLineHorizontalSloped(x0 + x, y0 + y, dx + x_seperation_lengths[step], up);
				x += dx + x_seperation_lengths[step];
				if(up) y -= dy;
				else   y += dy;
			}
			else
			{
				drawLineHorizontalSloped(x0 + x, y0 + y, x_seperation_lengths[step], up);
				x += x_seperation_lengths[step];
			}
		}


		delete[] x_seperation_lengths;
		delete[] y_seperation_heights;
	}

	void drawLine(int x0, int y0, int x1, int y1)
	{
		int delta_x{ x1 - x0 };
		int delta_y{ y1 - y0 };

		if(delta_x < 0)
		{
			x0 = x1;
			y0 = y1;
			delta_x *= -1;
			delta_y *= -1;
		}

		bool up{ delta_y < 0 ? true : false };
		if (up) delta_y *= -1; //take the abosulute value of delta_y


		SlopeEnum slope{ aproximateSlope(delta_x, delta_y) };

		switch(slope)
		{
		case SLOPE_1_0:
			drawLineVertical(x0, y0, delta_y, up);
			return;
		case SLOPE_0_1:
			drawLineHorizontal(x0, y0, delta_x);
			return;
		}

		drawSlopeFull(slope, x0, y0, delta_x, delta_y, up);
	}

}//end of namespace
