//이건 행렬
class Matrix
{
public:
	//이건 데이터를 담는 2차원 배열
	double mat[3][3];
	//이건 생성자
	Matrix()
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				mat[i][j] = 0;
		}
	}
	//이건 소멸자
	~Matrix(){}
	//이건 행렬 출력
	void Print()
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				cout << mat[i][j] << (j == 2) ? "\n" : ", ";
		}
	}
	//이건 이동 행렬 생성 함수
	Matrix Translate(double x, double y)
	{
		Matrix m = Matrix().Identity();
		m.mat[2][0] = x;
		m.mat[2][1] = y;
		return m;
	}
	//이건 회전 행렬 생성 함수
	Matrix Rotate(double angle)
	{
		double radian = angle * 3.141592 / 180;
		Matrix m = Matrix().Identity();
		m.mat[0][0] = cos(radian);
		m.mat[0][1] = -sin(radian);
		m.mat[1][0] = sin(radian);
		m.mat[1][1] = cos(radian);
		return m;
	}
	//이건 크기 행렬 생성 함수
	Matrix Scale(double size)
	{
		Matrix m = Matrix().Identity();
		for (size_t i = 0; i < 2; i++)
			m.mat[i][i] = size;
		return m;
	}
private:
	//이건 항등 행렬 생성 함수
	Matrix Identity()
	{
		Matrix m;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				m.mat[i][j] = i == j ? 1 : 0;
		}
		return m;
	}
};

//이건 벡터
class Vector3
{
public:
	//이건 데이터를 저장하는 배열
	double pos[3];

	//이건 생성자
	Vector3(double x, double y)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = 1;
	}
	//이건 소멸자
	~Vector3() {}
	//이건 벡터 출력
	void Print()
	{
		cout << pos[0] << ", " << pos[1] << ", " << pos[2] << "\n";
	}
	//이건 행렬곱(Vector3 * Matrix)
	Vector3 operator*(Matrix& mat3)
	{
		Vector3 vec3 = Vector3(0, 0);
		vec3.pos[2] = 0;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				vec3.pos[i] += mat3.mat[j][i] * pos[j];
			}
		}
		return vec3;
	}
private:

};