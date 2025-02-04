#include "Slope.h"

#include "Fraction.h"

using namespace Slope;

const Fraction Slope::fractions[MAX_SLOPE_FRACTIONS] = {
//widest and highest slopes first
{ 1, WIDER_SLOPE_DX }, // SLOPE_1_3
{ HIGHER_SLOPE_DY, 1 }, // SLOPE_2_1

{ 1, 1 }, // SLOPE_1_1
{ 1, 2 }, // SLOPE_1_2
{ 2, 3 }, // SLOPE_2_3
{ 3, 2 }, // SLOPE_3_2
{ 1, WIDER_SLOPE_DX + 1 }, // A slope WIDER than WIDE
{ HIGHER_SLOPE_DY + 1, 1 }  // A slope HIGHER than HIGH
};

const char NULL{ '\0' };
//` ~ ! ^ ( ) - _ + = ; : ' " , . \ / | < > [ ] { } *

const char Slope::patterns[MAX_SLOPE_FRACTIONS][MAX_DY][MAX_DX] = {
	//widest and highest slopes first
	//WIDE (SLOPE_1_3)
   {'`','*','.',
	NULL,NULL,NULL,
	NULL,NULL,NULL},
	//HIGH (SLOPE_2_1)
   {'|',NULL,NULL,
	'\'',NULL,NULL,
	NULL,NULL,NULL},

	//SLOPE_1_1
   {'\\',NULL,NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL},
	//SLOPE_1_2
   {'`','.', NULL,
	NULL,NULL,NULL,
	NULL,NULL,NULL},
	//SLOPE_2_3
   {'\'',',',NULL,
	NULL,NULL,'.',
	NULL,NULL,NULL},
	//SLOPE_3_2
   {'|',NULL,NULL,
	'`','.',NULL,
	NULL,'|',NULL},
};