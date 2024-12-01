#pragma once
#include "Player.h"
class Striker : public Player
{
	//DECLARE_SINGLE(Striker);
public:
	Striker();
	~Striker();
public:
	void Update() override;
	void PlusSkillCount() { // 이거 쾅 부분에서 호출해 줘야해
		m_skillCount++;
	}
protected:
	bool CanUseSkill();
	void UseSkill();
private:
	int m_skillCount = 0;
};

