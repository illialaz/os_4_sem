#include "framework.h"
#include "Number.h"

Number::Number() {
	a = 0;
}

Number::Number(double num) {
	this->a = num;
}

Number::Number(const Number& num) { this->a = num.a; }

Number Number::operator+(const Number& num) {
	return Number(this->a + num.a);
}

Number Number::operator-(const Number& num) {
	return Number(this->a - num.a);
}

Number Number::operator*(const Number& num) {
	return Number(this->a * num.a);
}

Number Number::operator/(const Number& num) {
	return Number(this->a / num.a);
}

std::ostream& operator<<(std::ostream& out, Number a) {
	out << a.a;
	return out;
}

double Number::get_a() {
	return this->a;
}
