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

bool Defender::CanUseSkill() // �е��� ������ ������
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
//        m_verticalSpeed -= m_gravity * fDT; // �߷� ����
//        Vec2 pos = GetPos();
//        pos.y -= m_verticalSpeed * fDT;
//        SetPos(pos);
//    }
//}

void Defender::Update() {
    //Player::Update();
    m_stateMachine->Update();

    Vec2 vPos = GetPos();
    // ���� (���鿡 ���� ����)
    if (m_isGrounded && GET_KEYDOWN(KEY_TYPE::SPACE))
    {
        m_vVelocity.y = -m_jumpPower; // �������� ���� ����
        m_isGrounded = false;         // ���� ���·� ��ȯ
    }

    // �߷� ����
    if (!m_isGrounded)
    {
        m_vVelocity.y += m_gravity * fDT; // �߷� ���ӵ� ����
    }

    // ��ġ ������Ʈ
    vPos.y += m_vVelocity.y * fDT;

    // ���� ������ ��ġ ���� �� ���� �ʱ�ȭ
    if (m_isGrounded)
    {
        m_vVelocity.y = 0; // �߷� ���ӵ��� �ʱ�ȭ
    }
    SetPos(vPos);
}
//void Defender::Jump() {
//    if (m_currentJumpCount < m_maxJumpCount) {
//        m_verticalSpeed = m_jumpPower; // ���� �ӵ� ����
//        m_currentState = DefenderState::Jump;        // ���¸� Jump�� ����
//        m_currentJumpCount++;
//        cout << "Defender jumps! Jump count: " << m_currentJumpCount << endl;
//    }
//}

void Defender::EnterCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        m_isGrounded = true;
        //Vec2 vPos = GetPos();
        //vPos.y = _other->GetLatedUpatedPos().y - m_collider->GetSize().y / 2; // ���� ���� ��ġ ����
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
        m_verticalSpeed = 300.0f; // ���� ���� �ӵ�
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