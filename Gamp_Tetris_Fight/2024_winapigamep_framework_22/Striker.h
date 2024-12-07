#pragma once
#include "Player.h"
class CameraComponent;

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
		cout << "더해짐 - " << m_skillCount << endl;
	}
	int GetSkillCount() { return m_skillCount; }
public:
	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;
protected:
	bool CanUseSkill();
public:
	bool UseSkill();
	void ShakeCamera();
private:
	int m_skillCount = 0;
private:
	Texture* m_pTex;
	CameraComponent* m_camera;
};

