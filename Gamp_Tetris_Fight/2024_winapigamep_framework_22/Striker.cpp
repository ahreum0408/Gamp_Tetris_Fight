#include "pch.h"
#include "Striker.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "PlayerManager.h"
#include "EventManager.h"
#include "Block.h"

Striker::Striker() : m_skillCount(0) {
	this->AddComponent<CameraComponent>();

	m_pCollider->SetSize({ 35,40 });
	m_pCollider->SetOffSetPos({ 2, 0 });

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Striker", L"Texture\\Dino\\DinoSprites - vita.bmp");

	m_animator->CreateAnimation(L"GreenDinoIdle", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 3, 0.1f);
	m_animator->PlayAnimation(L"GreenDinoIdle", true);

	m_camera = GetComponent<CameraComponent>();

	GET_SINGLE(PlayerManager)->SetStriker(this);
}
Striker::~Striker()
{
}

void Striker::EnterCollision(Collider* _other)
{
	wstring name = _other->GetOwner()->GetName();
	if (name == L"Block") {
		Block* block = dynamic_cast<Block*>(_other->GetOwner());
		if (block->GetIsDefence()) {
			cout << "공격수 배패.." << endl;
			GET_SINGLE(PlayerManager)->SetDefenerWiner(true);
			GET_SINGLE(EventManager)->ChangeScene(L"GameOverScene");
		}
	}
}
void Striker::StayCollision(Collider* _other)
{
}
void Striker::ExitCollision(Collider* _other)
{
}

bool Striker::CanUseSkill()
{
	return m_skillCount > 0;
}

bool Striker::UseSkill()
{
	if (CanUseSkill()) {
		if (m_camera != nullptr) {
			cout << "shake camera" << endl;
			m_camera->StartShake();
		}
		m_skillCount--;
		cout << "깍임 - " << m_skillCount << endl;
		return true;
	}
	return false;
}
void Striker::ShakeCamera()
{
	m_camera->StartShake();
}
void Striker::Update() {
	Player::Update();
}
