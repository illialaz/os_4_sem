#pragma once
#include <iostream>

class Number {
private:
	double a;
public:
	Number();

	Number(double num);

	Number(const Number& num);

	Number operator+(const Number& num);

	Number operator-(const Number& num);

	Number operator*(const Number& num);

	Number operator/(const Number& num);

	friend std::ostream& operator<<(std::ostream& out, Number a);

	double get_a();
};
