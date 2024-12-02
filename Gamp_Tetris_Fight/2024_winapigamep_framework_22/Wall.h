#pragma once
#include "Object.h"
#include "Collider.h"

class Wall : public Object
{
public:
	Wall();
	~Wall();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;

	void SetID(int id) {
		GetComponent<Collider>()->SetID(id);
	}
	void SetWallSize(Vec2 size) { GetComponent<Collider>()->SetSize(size); }
};

