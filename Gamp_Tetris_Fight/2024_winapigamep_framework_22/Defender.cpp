#include "pch.h"
#include "Defender.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"

#include "StateMachine.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"
#include "ResourceManager.h"
#include "Animator.h"

Defender::Defender(): m_stateMachine(new StateMachine<Defender>(this)), m_jumpCount(0), m_maxJumpCount(4), m_isGrounded(false){
    m_collider->SetID(0);

    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Defender", L"Texture\\Dino\\DinoSprites - mort.bmp");

    this->AddComponent<Animator>();
    animator = GetComponent<Animator>();
    animator->CreateAnimation(L"RedDinoIdle", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 3, 0.1f);
    animator->CreateAnimation(L"RedDinoJump", m_pTex, Vec2(336.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);
    animator->CreateAnimation(L"RedDinoFall", m_pTex, Vec2(432.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);

    //PlayIdleAnimation();

    m_stateMachine->ChangeState(new IdleState());
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
    if (name == L"Wall" || name == L"Block") {
        return true;
    }
    return false;
}