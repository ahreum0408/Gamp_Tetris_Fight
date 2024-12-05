#pragma once
#include "Object.h"
class Texture;
class Defender;

class DefenceBlock : public Object
{
public:
	DefenceBlock(Defender* defender);
	~DefenceBlock();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other) override;
private:
	Texture* m_pTex;
	Defender* m_defender;
	float m_lifeTime;
};

