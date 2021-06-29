#include <iostream>
#include <cmath>
#include "Number.h"
#include "Vector.h"

Vector::Vector() {
	this->x = Number(0);
	this->y = Number(0);
}

Vector::Vector(Number x, Number y) {
	this->x = x;
	this->y = y;
}

Vector::Vector(int x, int y) {
	this->x = Number(x);
	this->y = Number(y);
}

Vector::Vector(const Vector& v) {
	this->x = v.x;
	this->y = v.y;
}

double Vector::r() {
	return sqrt((this->x * this->x + this->y * this->y).get_a());
}

double Vector::u() {
	return atan((this->y / this->x).get_a());
}

Vector Vector::operator+(Vector b) {
	return Vector(this->x + b.x, this->y + b.y);
}

std::ostream& operator<<(std::ostream& out, Vector v) {
	out <<"(" << v.x << ", " << v.y << ")";
	return out;
}
