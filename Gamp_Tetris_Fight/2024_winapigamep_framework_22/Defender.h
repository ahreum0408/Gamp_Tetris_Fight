#pragma once
#include "Player.h"
#include "StateMachine.h"
#include "Animator.h"

class Defender : public Player
{
public:
	Defender();
public:
	void Update() override;
protected:
	bool CanUseSkill();
	void UseSkill();
public:
	virtual void EnterCollision(Collider* _other) override;
	virtual void StayCollision(Collider* _other) override;
	virtual void ExitCollision(Collider* _other) override;
	// 상태 관리
	StateMachine<Defender>* GetStateMachine() const { return m_stateMachine; }
	void Jump();
	bool IsGrounded() const { return m_isGrounded; }
	bool IsJumpKeyPressed() const { return GET_KEYDOWN(KEY_TYPE::SPACE); }
	bool IsFalling() const { return !m_isGrounded && GetPos().y < m_beforePos.y; }
public:
	void PlayIdleAnimation(){ animator->PlayAnimation(L"RedDinoIdle", true); }
	void PlayJumpAnimation(){ animator->PlayAnimation(L"RedDinoJump", true); }
	void PlayFallAnimation(){ animator->PlayAnimation(L"RedDinoFall", true); }
private:
	bool IsGround(Collider* self, Collider* other);
	void SetJumpCount() { m_jumpCount = 0; }
private:
	enum class DefenderState {
		Idle, Jump, Fall
	};

private:
	StateMachine<Defender>* m_stateMachine;
	int m_jumpCount;
	const int m_maxJumpCount;

	bool m_isGrounded;
	const float m_jumpPower = 300.f;
	const float m_gravity = 980.f;
	Vec2 m_vVelocity;

	Vec2 m_beforePos;
	Animator* animator;
};