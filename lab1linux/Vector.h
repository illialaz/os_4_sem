#pragma once
#include <iostream>
#include "Number.h"

class Vector {
private:
Number x;
Number y;
public:
Vector();
Vector(Number x, Number y);
Vector(int x, int y);
Vector(const Vector& v);
double r();
double u();
Vector operator+(Vector b);
friend std::ostream& operator<<(std::ostream& out, Vector v);
};
