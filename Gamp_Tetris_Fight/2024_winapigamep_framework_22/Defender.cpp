#include "pch.h"
#include "Defender.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"

#include "StateMachine.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"

Defender::Defender(): m_stateMachine(new StateMachine<Defender>(this)), m_jumpCount(0), m_maxJumpCount(4), m_isGrounded(false){
    m_stateMachine->ChangeState(new IdleState());
    m_collider->SetID(0);
}

bool Defender::CanUseSkill() // 패딩은 언제가 가능함
{
	return true;
}
void Defender::UseSkill()
{
	if (CanUseSkill()) {
		cout << "defender use skill" << endl;
	}
}

void Defender::Update() {
    Player::Update();
    m_stateMachine->Update();

    Vec2 vPos = GetPos();
    m_beforePos = vPos;

    // 중력 적용
    if (!m_isGrounded)
    {
        m_vVelocity.y += m_gravity * fDT; // 중력 가속도 적용
    }

    // 위치 업데이트
    vPos.y += m_vVelocity.y * fDT;

    // 땅에 닿으면 위치 고정 및 상태 초기화
    if (m_isGrounded)
    {
        m_vVelocity.y = 0; // 중력 가속도를 초기화
        SetJumpCount();
    }
    SetPos(vPos);
}

void Defender::EnterCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        m_isGrounded = true;
        m_vVelocity.y = 0; // 중력 가속도를 초기화
        SetJumpCount();
    }
}

void Defender::StayCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        //cout << "stay" << endl;
        m_isGrounded = true;
    }
}

void Defender::ExitCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        m_isGrounded = false;
    }
}
void Defender::Jump() {
    if (m_jumpCount < m_maxJumpCount) {
         m_isGrounded = false;         // 점프 상태로 전환
        m_jumpCount++;

        Vec2 vPos = GetPos();
        m_vVelocity.y = -m_jumpPower; // 위쪽으로 힘을 가함
        vPos.y += m_vVelocity.y * fDT;
        SetPos(vPos);
    }
}
bool Defender::IsGround(Collider* self, Collider* other)
{
    wstring name = other->GetOwner()->GetName();
    if (name == L"Wall") {
        return true;
    }
    return false;
}