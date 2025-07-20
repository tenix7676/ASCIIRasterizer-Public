#pragma once

//The negative sign should never be in the denominator, automatically put it in the numerator
class Fraction
{
public:
	int numerator;
	int denominator;
	
	Fraction();
	Fraction(int number);
	Fraction(int numerator, int denominator);
	~Fraction();

	Fraction simplify();
	friend bool operator<(const Fraction& fraction1, const Fraction& fraction2);
	friend bool operator>(const Fraction& fraction1, const Fraction& fraction2);
	friend bool operator>=(const Fraction& fraction1, const Fraction& fraction2);
	friend bool operator<=(const Fraction& fraction1, const Fraction& fraction2);
	friend bool operator==(const Fraction& fraction1, const Fraction& fraction2);

	//negation
	friend Fraction operator-(const Fraction& fraction1);

	friend Fraction operator+(const Fraction& fraction1, const Fraction& fraction2);
	friend Fraction operator-(const Fraction& fraction1, const Fraction& fraction2);
	friend Fraction operator-=(Fraction& fraction1, const Fraction& fraction2);

	friend Fraction operator*(const Fraction& fraction1, const Fraction& fraction2);
	friend Fraction operator*=(Fraction& fraction1, const Fraction& fraction2);
	friend Fraction operator/(const Fraction& fraction1, Fraction fraction2);


	friend Fraction operator*(const int number, const Fraction& fraction1);
	friend Fraction operator*(const Fraction& fraction1, const int number);

	Fraction invert();
};




