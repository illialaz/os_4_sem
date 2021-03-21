#pragma once
#include <iostream>
#include "Number.h"

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif

class Vector {
private:
	Number x;
	Number y;
public:
	VECTOR_API Vector();
	VECTOR_API Vector(Number x, Number y);
	VECTOR_API Vector(int x, int y);
	VECTOR_API Vector(const Vector& v);
	VECTOR_API double r();
	VECTOR_API double u();
	VECTOR_API Vector operator+(Vector b);
	VECTOR_API friend std::ostream& operator<<(std::ostream& out, Vector v);
};
