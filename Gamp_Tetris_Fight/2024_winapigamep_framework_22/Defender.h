#pragma once
#include "Player.h"
#include "StateMachine.h"

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
	void PerformJump();
	bool IsGrounded() const;
	bool IsJumpKeyPressed() const;
	bool IsFalling() const;
private:
	//void Jump();
	//void ApplyGravity();
	bool IsGround(Collider* self, Collider* other);
private:
	enum class DefenderState {
		Idle, Jump, Fall
	};

private:
	StateMachine<Defender>* m_stateMachine;
	int m_jumpCount;
	const int m_maxJumpCount;
	float m_verticalSpeed;

	bool m_isGrounded;
	const float m_jumpPower = 300.f;
	const float m_gravity = 980.f;
	Vec2 m_vVelocity;
};