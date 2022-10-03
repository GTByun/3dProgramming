#pragma once

class cordGroup
{
public:
	int xGroup[359];
	int yGroup[359];

	cordGroup()
	{
		for (size_t i = 0; i < 360; i++)
		{
			xGroup[i] = glm::sin(glm::radians(i));
			yGroup[i] = glm::cos(glm::radians(i));
		}
	}
	~cordGroup() {}
};