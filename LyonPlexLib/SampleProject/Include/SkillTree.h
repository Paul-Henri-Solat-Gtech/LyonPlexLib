#pragma once

struct skill 
{
	std::string skillName = "namePending";
	int skillCost = 0;
	bool isUnlocked = false;
};

class SkillTree
{
public:
	void Init();
	void Update();

private:
	int m_skillPoints;
	std::vector<skill> m_skillsList;
};

