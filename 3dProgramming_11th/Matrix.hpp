#include <iostream>
#include <cmath>

using namespace std;

class Matrix
{
public:
	/*�ʺ�*/
	int width;
	/*����*/
	int height;
	
	/*width : ��� �ʺ�, height : ��� ����*/
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

	/*��� ���*/
	void Print()
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
				cout << Get(j, i) << " ";
			cout << "\n";
		}
	}

	/*��� �� ĭ�� ���� �����Ѵ�.
	x : ���� ��ġ, y : ���� ��ġ, value : ���԰�*/
	void Set(int x, int y, double value)
	{
		data[y][x] = value;
	}

	/*��� �� ĭ�� ���� ���Ѵ�.
	x : ���� ��ġ, y : ���� ��ġ, value : ������*/
	void Plus(int x, int y, double value)
	{
		data[y][x] += value;
	}

	/*��� �� ĭ�� ���� �����´�.
	x : ���� ��ġ, y : ���� ��ġ*/
	double Get(int x, int y)
	{
		return data[y][x];
	}

	/*��ġ���*/
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
	/*��İ�*/
	double** data;
};

class Identity : public Matrix
{
public:
	/*�׵����
	size : ���μ��� ũ��*/
	Identity(int size) : Matrix(size, size)
	{
		for (size_t i = 0; i < size; i++)
			Set(i, i, 1);
	};
};

class Matrix4 : public Matrix
{
public:
	/*��� ���� 0�� �迭 ����*/
	Matrix4() : Matrix(4, 4){}
	/*4 * 4 ���� �迭�� ���� �����Ͽ� ����
	data : �迭*/
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
	/*��� ���� 0�� �迭 ����*/
	Matrix3() : Matrix(3, 3){}
	/*3 * 3 ���� �迭�� ���� �����Ͽ� ����
	data : �迭*/
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
	/*3���� ����(����) ����
	x : 1��° ��, y : 2��° ��, z : 3��° ��*/
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
	/*3���� ����(����) ����
	x : 1��° ��, y : 2��° ��, z : 3��° ��*/
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
	/*4���� ����(����) ����
	x : 1��° ��, y : 2��° ��, z : 3��° ��, w : 4��° ��*/
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
	/*4���� ����(����) ����
	x : 1��° ��, y : 2��° ��, z : 3��° ��, w : 4��° ��*/
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
		cout << "���� : ���� �ʴ� ��ĳ����� �տ���";
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
		cout << "���� : �԰� ���� ��� ���� �տ���";
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
		cout << "���� : �԰� ���� ��� ���� ������";
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
		cout << "���� : 0���� ���� �� ����";
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