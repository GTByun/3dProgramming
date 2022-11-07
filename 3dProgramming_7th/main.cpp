#include <cmath>
#include <iostream>

using namespace std;

#include "MuSoenMath.hpp"

void main()
{
	Vector3 v = Vector3(1, 1);
	Matrix Translate = Matrix().Translate(3.5, 0), Rotate = Matrix().Rotate(30), Scale = Matrix().Scale(2);
	v = v * Translate * Rotate * Scale;
	v.Print();
}