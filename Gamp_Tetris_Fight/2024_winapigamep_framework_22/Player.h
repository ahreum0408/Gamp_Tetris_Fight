#pragma once
#include "Object.h"
#include "InputManager.h"

class Texture;

class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void SetKey(KEY_TYPE _leftKey, KEY_TYPE _rightKey) {
		m_leftMoveKey = _leftKey;
		m_rightMoveKey = _rightKey;
	}
public:
	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;
protected:
	bool CanUseSkill();
	void UseSkill();
protected:
	KEY_TYPE m_leftMoveKey;
	KEY_TYPE m_rightMoveKey;
	Collider* m_collider;

	// 플레이어 크기 만큼 더 조절
	const float minX = 300 + 24;
	const float maxX = 700 - 24;
};

