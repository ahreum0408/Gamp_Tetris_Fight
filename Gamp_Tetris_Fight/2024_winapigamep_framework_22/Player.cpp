#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Velocity.h"
#include "TimeManager.h"

Player::Player() : m_leftMoveKey(KEY_TYPE::A), m_rightMoveKey(KEY_TYPE::D)
{
	this->AddComponent<Collider>();
	m_pCollider = GetComponent<Collider>();

	this->AddComponent<Animator>();
	m_animator = GetComponent<Animator>();

	this->AddComponent<Velocity>();
}
Player::~Player()
{

}
void Player::Update()
{
	Vec2 vPos = GetPos();

	if (GET_KEY(m_leftMoveKey) && m_canMoveLeft) {
		vPos.x -= 100.f * fDT;
	}
	if (GET_KEY(m_rightMoveKey) && m_canMoveRight) {
		vPos.x += 100.f * fDT;
	}

	vPos.x = std::clamp(vPos.x, minX, maxX);

	SetPos(vPos);
}

void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::EnterCollision(Collider* _other)
{

}

void Player::StayCollision(Collider* _other)
{

}

void Player::ExitCollision(Collider* _other)
{

}

bool Player::CanUseSkill()
{
	return false;
}

void Player::UseSkill()
{
}