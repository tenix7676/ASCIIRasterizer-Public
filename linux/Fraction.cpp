#include "Fraction.h"

int GCD(int a, int b)
{
	if(b == 0) return 0;

	int remainder{ a % b };
	while(remainder != 0)
	{
		a = b;
		b = remainder;
		remainder = a % b;
	}

	return b;
}

Fraction::Fraction()
{
	numerator = 0;
	denominator = 1;
}
Fraction::Fraction(int number)
{
	numerator = number;
	denominator = 1;
}
Fraction::Fraction(int numerator, int denominator)
{
	this->numerator = numerator;
	this->denominator = denominator;
}
Fraction::~Fraction() {}

Fraction Fraction::simplify() 
{
	int gcd{ GCD(numerator, denominator) };
	numerator /= gcd;
	denominator /= gcd;

	if(denominator < 0) 
	{
		numerator *= -1;
		denominator *= -1;
	}

	return *this;
}

bool operator<(const Fraction& fraction1, const Fraction& fraction2)
{
	return fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator;
}
bool operator>(const Fraction& fraction1, const Fraction& fraction2)
{
	return fraction2 < fraction1;
}
bool operator>=(const Fraction& fraction1, const Fraction& fraction2)
{
	return !(fraction1 < fraction2);
}
bool operator<=(const Fraction& fraction1, const Fraction& fraction2)
{
	return !(fraction2 < fraction1);
}
bool operator==(const Fraction& fraction1, const Fraction& fraction2)
{
	return fraction1.numerator * fraction2.denominator == fraction2.numerator * fraction1.denominator;
}



Fraction operator-(const Fraction& fraction1)
{
	return Fraction(-fraction1.numerator, fraction1.denominator);
}



Fraction operator+(const Fraction& fraction1, const Fraction& fraction2)
{
	Fraction f;
	f.numerator = fraction1.numerator* fraction2.denominator + fraction2.numerator * fraction1.denominator;
	f.denominator = fraction1.denominator * fraction2.denominator;

	return f;
}
Fraction operator-(const Fraction& fraction1, const Fraction& fraction2)
{
	return fraction1 + -fraction2;
}
Fraction operator-=(Fraction& fraction1, const Fraction& fraction2)
{
	fraction1 = fraction1 - fraction2;
	return fraction1;
}


Fraction operator*(const Fraction& fraction1, const Fraction& fraction2)
{
	Fraction f;
	f.numerator = fraction1.numerator * fraction2.numerator;
	f.denominator = fraction1.denominator* fraction2.denominator;

	return f;
}
Fraction operator*=(Fraction& fraction1, const Fraction& fraction2)
{
	fraction1 = fraction1 * fraction2;
	return fraction1;
}
Fraction operator*(const Fraction& fraction1, const int number)
{
	Fraction f;
	f.numerator = fraction1.numerator * number;
	f.denominator = fraction1.denominator;

	return f;
}
Fraction operator*(const int number, const Fraction& fraction1)
{
	return fraction1 * number;
}


Fraction Fraction::invert()
{
	int temp_num { numerator };
	numerator = denominator;
	denominator = temp_num;

	if(denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}

	return *this;
}

Fraction operator/(const Fraction& fraction1, Fraction fraction2)
{
	return fraction1 * fraction2.invert();
}