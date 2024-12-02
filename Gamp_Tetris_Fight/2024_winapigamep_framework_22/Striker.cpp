#include "pch.h"
#include "Striker.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "Animator.h"

Striker::Striker() {
	this->AddComponent<CameraComponent>();
	m_collider->SetSize({ 35,40 });
	m_collider->SetOffSetPos({ 2, 0 });

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Striker", L"Texture\\Dino\\DinoSprites - vita.bmp");
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"GreenDinoIdle", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 3, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"GreenDinoIdle", true);
}
Striker::~Striker()
{
}

bool Striker::CanUseSkill()
{
	return m_skillCount > 0;
}

void Striker::UseSkill()
{
	if (CanUseSkill()) {
		cout << "struker use skill" << endl;
	}
}
void Striker::Update() {
	Vec2 vPos = GetPos();

	if (GET_KEYDOWN(m_leftMoveKey)) {
		vPos.x -= 48.f;
	}
	if (GET_KEYDOWN(m_rightMoveKey)) {
		vPos.x += 48.f;
	}
	if (GET_KEYDOWN(KEY_TYPE::LSHIFT)) { // ¾Æ·¡·Î Âï±â
		CameraComponent* cam = GetComponent<CameraComponent>();
		if (cam != nullptr) {
			cam->ShakeCamera();
		}
		UseSkill();
	}

	Player::Update();
}
