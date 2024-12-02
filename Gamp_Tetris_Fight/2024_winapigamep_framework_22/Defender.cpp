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
    m_collider->SetSize({ 35,40 });
    m_collider->SetOffSetPos({ 2,0 });

    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Defender", L"Texture\\Dino\\DinoSprites - mort.bmp");

    this->AddComponent<Animator>();
    animator = GetComponent<Animator>();
    animator->CreateAnimation(L"RedDinoIdle", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 3, 0.1f);
    animator->CreateAnimation(L"RedDinoJump", m_pTex, Vec2(336.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);
    animator->CreateAnimation(L"RedDinoFall", m_pTex, Vec2(432.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);

    //PlayIdleAnimation();

    m_stateMachine->ChangeState(new IdleState());
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

    SetPos(vPos);
}

void Defender::EnterCollision(Collider* _other)
{
    cout << "enter" << endl;
    if (IsGround(_other)) {
        m_isGrounded = true;
        m_vVelocity.y = 0; // 중력 가속도를 초기화
        SetJumpCount();
    }
    if (IsSideWall(_other)) {

    }
}

void Defender::StayCollision(Collider* _other)
{
    if (IsGround(_other)) {
        //cout << "stay" << endl;
        m_isGrounded = true;
    }
}

void Defender::ExitCollision(Collider* _other)
{
    if (IsGround(_other)) {
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
bool Defender::IsGround(Collider* other)
{
    wstring name = other->GetOwner()->GetName();
    if (name == L"BottomWall" || name == L"Block") {
        return true;
    }
    return false;
}

bool Defender::IsSideWall(Collider* other)
{
    wstring name = other->GetOwner()->GetName();
    if (name == L"SideWall") {
        return true;
    }
    return false;
}
