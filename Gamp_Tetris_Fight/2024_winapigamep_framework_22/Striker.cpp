#include "pch.h"
#include "Striker.h"
#include "CameraComponent.h"
#include "InputManager.h"
#include "Collider.h"

Striker::Striker() {
	this->AddComponent<CameraComponent>();
	m_collider->SetID(1);
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
	Player::Update();

	if (GET_KEYDOWN(KEY_TYPE::LSHIFT)) { // ¾Æ·¡·Î Âï±â
		CameraComponent* cam = GetComponent<CameraComponent>();
		if (cam != nullptr) {
			cam->ShakeCamera();
		}
		UseSkill();
	}
}
