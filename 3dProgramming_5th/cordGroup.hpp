class cordGroup
{
public:
	cordGroup()
	{
		for (float i = 0; i < 360; i++)
		{
			xGroup[(int)i] = glm::sin(glm::radians(i));
			yGroup[(int)i] = glm::cos(glm::radians(i));
		}
	}
	~cordGroup() {}
	float xGroup[360], yGroup[360];

	float GetXGroup(int num)
	{
		if (num < 360)
		{
			return xGroup[num];
		}
		else
		{
			return 0;
		}
	}
private:

};