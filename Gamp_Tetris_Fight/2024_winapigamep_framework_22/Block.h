#pragma once
#include "Object.h"
class Texture;
class Block_Parent;
class Collider;
class Velocity;

class Block :
	public Object
{
public:
	Block(wstring path, Block_Parent* parent);
	~Block();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
	void SetIsDefence(bool isDefence) {
		m_defence = isDefence;
		if (m_defence) {
			StartFireBlock();
		}
	}
	void SetIsBulit(bool isBulit) {
		m_built = isBulit;
	}
	bool GetIsDefence() {
		return m_defence;
	}
	bool GetIsBulit() {
		return m_built;
	}
private:
	void StartFireBlock();
	Vec2 GetDirection(Collider* _other, const Vec2& point);
	Vec2 GetRandomDirection();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	bool m_defence = false;
	bool m_built = false;
	Vec2 m_vDir;
	Texture* m_pTex;
	Block_Parent* m_parent;
	float m_blockSpeed = 3.0f;
private:
	Collider* m_collider;
	Velocity* m_velocity;
};

