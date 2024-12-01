#include "pch.h"
#include "Wall.h"
#include "Collider.h"

Wall::Wall()
{
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 500,50 });
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Render(HDC _hdc)
{	
	ComponentRender(_hdc);

}
void Wall::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		//cout << "collision wall" << endl;
	}
}

void Wall::StayCollision(Collider* _other)
{

}

void Wall::ExitCollision(Collider* _other)
{

}