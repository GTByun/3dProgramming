#include <iostream>

using namespace std;

class Matrix
{
public:
	int width;
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
		{
			delete[] data[i];
		}
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

	/*x : ���� ��ġ, y : ���� ��ġ, value : ���԰�*/
	void Set(int x, int y, double value)
	{
		data[y][x] = value;
	}

	/*x : ���� ��ġ, y : ���� ��ġ, value : ������*/
	void Plus(int x, int y, double value)
	{
		data[y][x] += value;
	}

	/*x : ���� ��ġ, y : ���� ��ġ*/
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
	double** data;
};

class Identity : public Matrix
{
public:
	Identity(int size) : Matrix(size, size)
	{
		for (size_t i = 0; i < size; i++)
			Set(i, i, 1);
	};
};

class Matrix4 : public Matrix
{
public:
	Matrix4() : Matrix(4, 4){}
};

class Matrix3 : public Matrix
{
public:
	Matrix3() : Matrix(3, 3){}
};

class Vector3 : public Matrix
{
public:
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
	Vector4x1(double x, double y, double z, double w) : Matrix(1, 4)
	{
		Set(0, 0, x);
		Set(0, 1, y);
		Set(0, 2, z);
		Set(0, 3, z);
	}
};


Matrix* operator+(Matrix& mat1, Matrix& mat2)
{
	if (mat1.width != mat2.width || mat1.height != mat2.height)
	{
		cout << "���� : ���� �ʴ� ��ĳ����� �տ���";
		return new Matrix(1, 1);
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
	Matrix* rtn = new Matrix(mat.width, mat.height);
	for (size_t i = 0; i < mat.width; i++)
	{
		for (size_t j = 0; j < mat.height; j++)
			rtn->Set(i, j, mat.Get(i, j) / num);
	}
	return rtn;
}