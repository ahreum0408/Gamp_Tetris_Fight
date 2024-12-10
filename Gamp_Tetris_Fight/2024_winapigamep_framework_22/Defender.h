#pragma once
#include "Player.h"
#include "StateMachine.h"
#include "Animator.h"
#include "Velocity.h"
#include "Block.h"

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
	bool IsJumpKeyPressed() const { return GET_KEYDOWN(KEY_TYPE::UP) && !m_isBlockAbove; }
	bool IsFalling() const { return !m_isGrounded && GetPos().y < m_beforePos.y; }
	void CreateDefendBlock();

	void DieCheck(Block* block);
public:
	void PlayIdleAnimation() { m_animator->PlayAnimation(L"RedDinoIdle", true); }
	void PlayJumpAnimation() { m_animator->PlayAnimation(L"RedDinoJump", true); }
	void PlayFallAnimation() { m_animator->PlayAnimation(L"RedDinoFall", true); }
private:
	bool IsGround(Collider* other);
	bool IsBlock(Collider* other);
	void SetJumpCount() { m_jumpCount = 0; }
public:
	int GetSkillCount() { return m_defenceSkillCount; }
private:
	enum class DefenderState {
		Idle, Jump, Fall
	};
	Texture* m_pTex;
private:
	StateMachine<Defender>* m_stateMachine;
	int m_jumpCount;
	const int m_maxJumpCount;

	int m_defenceSkillCount = 0;
	int m_defenceSkillCoolTime = 20;
	float time;

	bool m_isGrounded;
	bool m_isBlockAbove = false;
	const float m_jumpPower = 350.f;
	const float m_gravity = 980.f;
	Vec2 m_vVelocity;
	Object* m_currentDefenceBlock;

	Vec2 m_beforePos;
	Collider* m_jumpCollider;
	Velocity* m_velocity;
};