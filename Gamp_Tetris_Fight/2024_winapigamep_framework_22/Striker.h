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
	void PlusSkillCount() { // �̰� �� �κп��� ȣ���� �����
		m_skillCount++;
	}
protected:
	bool CanUseSkill();
	void UseSkill();
private:
	Texture* m_pTex;
private:
	int m_skillCount = 0;
};

