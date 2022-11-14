#include <iostream>
#include <cmath>

using namespace std;

class Matrix
{
public:
	/*너비*/
	int width;
	/*높이*/
	int height;
	
	/*width : 행렬 너비, height : 행렬 높이*/
	Matrix(int width, int height)
	{
		this->width = width;
		this->height = height;
		data = new double* [height];
		for (size_t i = 0; i < height; i++)
			data[i] = new double[width];
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
				data[i][j] = 0;
		}
	}
	~Matrix()
	{
		for (size_t i = 0; i < height; i++)
			delete[] data[i];
		delete[] data;
	}

	/*행렬 출력*/
	void Print()
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
				cout << Get(j, i) << " ";
			cout << "\n";
		}
	}

	/*행렬 한 칸에 값을 대입한다.
	x : 가로 위치, y : 세로 위치, value : 대입값*/
	void Set(int x, int y, double value)
	{
		data[y][x] = value;
	}

	/*행렬 한 칸에 값을 더한다.
	x : 가로 위치, y : 세로 위치, value : 증감값*/
	void Plus(int x, int y, double value)
	{
		data[y][x] += value;
	}

	/*행렬 한 칸의 값을 가져온다.
	x : 가로 위치, y : 세로 위치*/
	double Get(int x, int y)
	{
		return data[y][x];
	}

	/*전치행렬*/
	Matrix* Transpose()
	{
		Matrix* rtn = new Matrix(height, width);
		for (size_t i = 0; i < width; i++)
		{
			for (size_t j = 0; j < height; j++)
				rtn->Set(j, i, Get(i, j));
		}
		return rtn;
	}
private:
	/*행렬값*/
	double** data;
};

class Identity : public Matrix
{
public:
	/*항등행렬
	size : 가로세로 크기*/
	Identity(int size) : Matrix(size, size)
	{
		for (size_t i = 0; i < size; i++)
			Set(i, i, 1);
	};
};

class Matrix4 : public Matrix
{
public:
	/*모든 값이 0인 배열 생성*/
	Matrix4() : Matrix(4, 4){}
	/*4 * 4 정적 배열의 값을 복사하여 생성
	data : 배열*/
	Matrix4(double data[4][4]) : Matrix(4, 4)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
				Set(j, i, data[i][j]);
		}
	}
};

class Matrix3 : public Matrix
{
public:
	/*모든 값이 0인 배열 생성*/
	Matrix3() : Matrix(3, 3){}
	/*3 * 3 정적 배열의 값을 복사하여 생성
	data : 배열*/
	Matrix3(double data[3][3]) : Matrix(3, 3)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				Set(j, i, data[i][j]);
		}
	}
};

class Vector3 : public Matrix
{
public:
	/*3차원 벡터(가로) 생성
	x : 1번째 값, y : 2번째 값, z : 3번째 값*/
	Vector3(double x, double y, double z) : Matrix(3, 1)
	{
		Set(0, 0, x);
		Set(1, 0, y);
		Set(2, 0, z);
	}
};

class Vector1x3 : public Matrix
{
public:
	/*3차원 벡터(세로) 생성
	x : 1번째 값, y : 2번째 값, z : 3번째 값*/
	Vector1x3(double x, double y, double z) : Matrix(1, 3)
	{
		Set(0, 0, x);
		Set(0, 1, y);
		Set(0, 2, z);
	}
};

class Vector4 : public Matrix
{
public:
	/*4차원 벡터(가로) 생성
	x : 1번째 값, y : 2번째 값, z : 3번째 값, w : 4번째 값*/
	Vector4(double x, double y, double z, double w) : Matrix(4, 1)
	{
		Set(0, 0, x);
		Set(1, 0, y);
		Set(2, 0, z);
		Set(3, 0, z);
	}
};

class Vector4x1 : public Matrix
{
	/*4차원 벡터(세로) 생성
	x : 1번째 값, y : 2번째 값, z : 3번째 값, w : 4번째 값*/
	Vector4x1(double x, double y, double z, double w) : Matrix(1, 4)
	{
		Set(0, 0, x);
		Set(0, 1, y);
		Set(0, 2, z);
		Set(0, 3, z);
	}
};

class Position2 : public Identity
{
public:
	Position2(double x, double y) : Identity(3)
	{
		Set(0, 2, x);
		Set(1, 2, y);
	}
};

class Rotation2 : public Identity
{
public:
	Rotation2(double degree) : Identity(3)
	{
		double radian = degree * 3.141592 / 180;
		Set(0, 0, cos(radian));
		Set(1, 0, sin(radian));
		Set(0, 1, -sin(radian));
		Set(1, 1, cos(radian));
	}
};

class Scale2 : public Identity
{
public:
	Scale2(double x, double y) : Identity(3)
	{
		Set(0, 0, x);
		Set(1, 1, y);
	}
	Scale2(double size) : Identity(3)
	{
		Set(0, 0, size);
		Set(1, 1, size);
	}
};

class Position3 : public Identity
{
public:
	Position3(double x, double y, double z) : Identity(4)
	{
		Set(0, 2, x);
		Set(1, 2, y);
		Set(2, 2, z);
	}
};

enum Rotate3Option
{
	Roll,
	Yaw,
	Pitch
};

class Rotation3 : public Identity
{
public:
	Rotation3(Rotate3Option r3o, double degree) : Identity(4)
	{
		double radian = degree * 3.141592 / 180;
		int changePos[2] = { 0, 1 };
		switch (r3o)
		{
		case Roll:
			break;
		case Yaw:
			changePos[1] = 2;
			break;
		case Pitch:
			changePos[0] = 1;
			changePos[1] = 2;
			break;
		}
		Set(changePos[0], changePos[0], cos(radian));
		Set(changePos[1], changePos[0], sin(radian));
		Set(changePos[0], changePos[1], -sin(radian));
		Set(changePos[1], changePos[1], cos(radian));
	}
};

class Scale3 : public Identity
{
public:
	Scale3(double x, double y, double z) : Identity(4)
	{
		Set(0, 0, x);
		Set(1, 1, y);
		Set(2, 2, z);
	}
	Scale3(double size) : Identity(4)
	{
		Set(0, 0, size);
		Set(1, 1, size);
		Set(2, 2, size);
	}
};

Matrix* operator+(Matrix& mat1, Matrix& mat2)
{
	if (mat1.width != mat2.width || mat1.height != mat2.height)
	{
		cout << "오류 : 맞지 않는 행렬끼리의 합연산";
		exit(-1);
	}
	Matrix* rtn = new Matrix(mat1.width, mat1.height);
	for (size_t i = 0; i < mat1.width; i++)
	{
		for (size_t j = 0; j < mat1.height; j++)
			rtn->Set(i, j, mat1.Get(i, j) + mat2.Get(i, j));
	}
	return rtn;
};

Matrix* operator-(Matrix& mat1, Matrix& mat2)
{
	if (mat1.width != mat2.width || mat1.height != mat2.height)
	{
		cout << "오류 : 규격 외의 행렬 간의 합연산";
		exit(-1);
	}
	Matrix* rtn = new Matrix(mat1.width, mat1.height);
	for (size_t i = 0; i < mat1.width; i++)
	{
		for (size_t j = 0; j < mat1.height; j++)
			rtn->Set(i, j, mat1.Get(i, j) - mat2.Get(i, j));
	}
	return rtn;
};

Matrix* operator*(Matrix& mat1, Matrix& mat2)
{
	if (mat1.width != mat2.height)
	{
		cout << "오류 : 규격 외의 행렬 간의 곱연산";
		exit(-1);
	}
	int size = mat1.width;
	Matrix* rtn = new Matrix(mat2.width, mat1.height);
	
	for (size_t i = 0; i < rtn->width; i++)
	{
		for (size_t j = 0; j < rtn->height; j++)
		{
			for (size_t k = 0; k < size; k++)
				rtn->Plus(i, j, mat1.Get(k, j) * mat2.Get(i, k));
		}
	}
	return rtn;
}

Matrix* operator*(Matrix& mat, double num)
{
	Matrix* rtn = new Matrix(mat.width, mat.height);
	for (size_t i = 0; i < mat.width; i++)
	{
		for (size_t j = 0; j < mat.height; j++)
			rtn->Set(i, j, mat.Get(i, j) * num);
	}
	return rtn;
}

Matrix* operator*(double num, Matrix& mat)
{
	Matrix* rtn = new Matrix(mat.width, mat.height);
	for (size_t i = 0; i < mat.width; i++)
	{
		for (size_t j = 0; j < mat.height; j++)
			rtn->Set(i, j, mat.Get(i, j) * num);
	}
	return rtn;
}

Matrix* operator/(Matrix& mat, double num)
{
	if (num == 0)
	{
		cout << "오류 : 0으로 나눌 수 없음";
		exit(-1);
	}
	Matrix* rtn = new Matrix(mat.width, mat.height);
	for (size_t i = 0; i < mat.width; i++)
	{
		for (size_t j = 0; j < mat.height; j++)
			rtn->Set(i, j, mat.Get(i, j) / num);
	}
	return rtn;
}