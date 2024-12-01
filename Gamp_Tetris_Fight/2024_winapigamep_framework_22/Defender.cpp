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

void Defender::Update() {
    Player::Update();
    m_stateMachine->Update();

    Vec2 vPos = GetPos();
    m_beforePos = vPos;

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
        SetJumpCount();
    }
    SetPos(vPos);
}

void Defender::EnterCollision(Collider* _other)
{
    if (IsGround(m_collider, _other)) {
        m_isGrounded = true;
        m_vVelocity.y = 0; // �߷� ���ӵ��� �ʱ�ȭ
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
         m_isGrounded = false;         // ���� ���·� ��ȯ
        m_jumpCount++;

        Vec2 vPos = GetPos();
        m_vVelocity.y = -m_jumpPower; // �������� ���� ����
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