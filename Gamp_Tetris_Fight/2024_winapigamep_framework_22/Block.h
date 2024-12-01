#pragma once
#include "Object.h"
class Texture;
class Block :
    public Object
{
public:
	Block(wstring path);
	~Block();
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}

public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Vec2 m_vDir;
	Texture* m_pTex;
};

