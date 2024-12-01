#include "pch.h"
#include "Defender.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"

#include "StateMachine.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"

Defender::Defender(): m_stateMachine(new StateMachine<Defender>(this)), m_jumpCount(0), m_maxJumpCount(4), m_verticalSpeed(0.0f), m_isGrounded(false){
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
//void Defender::ApplyGravity() {
//    if (m_currentState != DefenderState::Idle) {
//        m_verticalSpeed -= m_gravity * fDT; // 중력 적용
//        Vec2 pos = GetPos();
//        pos.y -= m_verticalSpeed * fDT;
//        SetPos(pos);
//    }
//}

void Defender::Update() {
    //Player::Update();
    m_stateMachine->Update();

    Vec2 vPos = GetPos();
    // 점프 (지면에 있을 때만)
    if (m_isGrounded && GET_KEYDOWN(KEY_TYPE::SPACE))
    {
        m_vVelocity.y = -m_jumpPower; // 위쪽으로 힘을 가함
        m_isGrounded = false;         // 점프 상태로 전환
    }

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
    }
    SetPos(vPos);
}
//void Defender::Jump() {
//    if (m_currentJumpCount < m_maxJumpCount) {
//        m_verticalSpeed = m_jumpPower; // 점프 속도 설정
//        m_currentState = DefenderState::Jump;        // 상태를 Jump로 변경
//        m_currentJumpCount++;
//        cout << "Defender jumps! Jump count: " << m_currentJumpCount << endl;
//    }
//}

void Defender::EnterCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        m_isGrounded = true;
        //Vec2 vPos = GetPos();
        //vPos.y = _other->GetLatedUpatedPos().y - m_collider->GetSize().y / 2; // 지면 위에 위치 고정
        //SetPos(vPos);
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
void Defender::PerformJump() {
    if (m_jumpCount < m_maxJumpCount) {
        m_jumpCount++;
        m_verticalSpeed = 300.0f; // 예시 점프 속도
        std::cout << "Jump performed! Jump count: " << m_jumpCount << std::endl;
    }
}

bool Defender::IsGrounded() const {
    return m_isGrounded;
}

bool Defender::IsJumpKeyPressed() const {
    return GET_KEYDOWN(KEY_TYPE::SPACE);
}

bool Defender::IsFalling() const {
    return m_verticalSpeed < 0;
}
bool Defender::IsGround(Collider* self, Collider* other)
{
    wstring name = other->GetOwner()->GetName();
    if (name == L"Wall") {
        return true;
    }
    return false;
}