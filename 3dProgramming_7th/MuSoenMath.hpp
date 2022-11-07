//�̰� ���
class Matrix
{
public:
	//�̰� �����͸� ��� 2���� �迭
	double mat[3][3];
	//�̰� ������
	Matrix()
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				mat[i][j] = 0;
		}
	}
	//�̰� �Ҹ���
	~Matrix(){}
	//�̰� ��� ���
	void Print()
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
				cout << mat[i][j] << (j == 2) ? "\n" : ", ";
		}
	}
	//�̰� �̵� ��� ���� �Լ�
	Matrix Translate(double x, double y)
	{
		Matrix m = Matrix().Identity();
		m.mat[2][0] = x;
		m.mat[2][1] = y;
		return m;
	}
	//�̰� ȸ�� ��� ���� �Լ�
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
	//�̰� ũ�� ��� ���� �Լ�
	Matrix Scale(double size)
	{
		Matrix m = Matrix().Identity();
		for (size_t i = 0; i < 2; i++)
			m.mat[i][i] = size;
		return m;
	}
private:
	//�̰� �׵� ��� ���� �Լ�
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

//�̰� ����
class Vector3
{
public:
	//�̰� �����͸� �����ϴ� �迭
	double pos[3];

	//�̰� ������
	Vector3(double x, double y)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = 1;
	}
	//�̰� �Ҹ���
	~Vector3() {}
	//�̰� ���� ���
	void Print()
	{
		cout << pos[0] << ", " << pos[1] << ", " << pos[2] << "\n";
	}
	//�̰� ��İ�(Vector3 * Matrix)
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