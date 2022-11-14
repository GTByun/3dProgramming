#include "Matrix.hpp"
#include <crtdbg.h>

int main()
{
	Matrix* vec = new Identity(3);
	Matrix* mat = new Identity(3);
	mat = *mat * 2;
	Matrix* cc = *vec * *mat;
	cc->Print();
	return 0;
}