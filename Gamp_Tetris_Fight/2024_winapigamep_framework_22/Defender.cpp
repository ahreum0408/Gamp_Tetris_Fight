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
#include "Velocity.h"
#include "DefenceBlock.h"
#include "GameScene.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Block.h"
#include "PlayerManager.h"

Defender::Defender() : m_stateMachine(new StateMachine<Defender>(this)), m_jumpCount(0), m_maxJumpCount(3), m_isGrounded(false) {
    m_pCollider->SetSize({ 35,35 });
    m_pCollider->SetOffSetPos({ 2,0 });
    m_pCollider->SetIsTrigger(false);

    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Defender", L"Texture\\Dino\\DinoSprites - mort.bmp");

    m_animator->CreateAnimation(L"RedDinoIdle", m_pTex, Vec2(0.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 3, 0.1f);
    m_animator->CreateAnimation(L"RedDinoJump", m_pTex, Vec2(336.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);
    m_animator->CreateAnimation(L"RedDinoFall", m_pTex, Vec2(432.f, 0.f), Vec2(48.f, 48.f), Vec2(48.f, 0.f), 1, 0.1f);

    m_velocity = GetComponent<Velocity>();

    m_stateMachine->ChangeState(new IdleState());

    GET_SINGLE(PlayerManager)->SetDefender(this);
}

bool Defender::CanUseSkill() // �е��� ������ ������
{
    return m_defenceSkillCount > 0;
}
void Defender::UseSkill()
{
    if (CanUseSkill()) {
        CreateDefendBlock();
        m_defenceSkillCount--;
    }
}
void Defender::Update() {
    Vec2 vPos = GetPos();
    m_beforePos = vPos;

    if (GET_KEYDOWN(KEY_TYPE::SPACE)) {
        UseSkill();
    }

    m_stateMachine->Update();

    // �߷� ����
    if (!m_isGrounded)
    {
        m_vVelocity.y += m_gravity * fDT; // �߷� ���ӵ� ����
    }

    // ��ġ ������Ʈ
    vPos.y += m_vVelocity.y * fDT;
    SetPos(vPos);

    // ���潺 �� ����
    time += fDT; // DeltaTime�� �̿��� �ð� ����

    Player::Update();

    if (time >= m_defenceSkillCoolTime) // 0.05�� �������� ����w
    {
        time = 0.0f; // Ÿ�̸� �ʱ�ȭ
        m_defenceSkillCount++; // ��鸲 Ƚ�� ����
    }
}

void Defender::EnterCollision(Collider* _other) {
    if (IsGround(_other)) {
        m_isGrounded = true;
        m_vVelocity.y = 0; // �߷� ���ӵ��� �ʱ�ȭ
        SetJumpCount();
    }
    //CollisionDirection direction = m_pCollider->GetCollisionDirection(GetPos(), _other->GetOwnerPos());
    //if (direction == CollisionDirection::Top) {
    //    Block* block = dynamic_cast<Block*>(_other->GetOwner());
    //    if (!block->GetIsStop()) { // ���� �������� �ʾҰ�
    //        if (!block->GetIsDefence() || block->GetIsBulit()) {
    //            cout << "����� ����.." << endl;
    //            GET_SINGLE(PlayerManager)->SetDefenerWiner(false);
    //            GET_SINGLE(EventManager)->ChangeScene(L"GameOverScene");
    //        }
    //    }
    //}
}
void Defender::StayCollision(Collider* _other)
{
    //CollisionDirection direction = m_pCollider->GetCollisionDirection(GetPos(), _other->GetOwnerPos());
    //if (direction == CollisionDirection::Top) {
    //    Block* block = dynamic_cast<Block*>(_other->GetOwner());
    //    if (!block->GetIsStop()) { // ���� �������� �ʾҰ�
    //        if (!block->GetIsDefence() || block->GetIsBulit()) {
    //            cout << "����� ����.." << endl;
    //            GET_SINGLE(PlayerManager)->SetDefenerWiner(false);
    //            GET_SINGLE(EventManager)->ChangeScene(L"GameOverScene");
    //        }
    //    }
    //}
}
void Defender::ExitCollision(Collider* _other)
{
    m_canMoveLeft = true;
    m_canMoveRight = true;
    if (IsGround(_other)) {
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
void Defender::CreateDefendBlock()
{
    Object* block = new DefenceBlock(this); // Defender �ڽ��� ����
    GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::DEFENCEBLOCK);

    // �ʱ� ��� ��ġ ����
    Vec2 defenderPos = GetPos();
    Vec2 blockPos = defenderPos;
    blockPos.y -= 50.f; // Defender �ٷ� ���� ����
    block->SetPos(blockPos);
}
void Defender::DieCheck(Block* block)
{
    Vec2 vPos = GetPos();
    Vec2 targetPos = block->GetPos();
    if (vPos.x >= targetPos.x - BLOCK_SIZE / 2 && vPos.x <= targetPos.x + BLOCK_SIZE / 2
        && vPos.y >= targetPos.y - BLOCK_SIZE / 2 && vPos.y <= targetPos.y - BLOCK_SIZE / 2)
    {
        if (!block->GetIsStop()) {
            if (!block->GetIsDefence() || block->GetIsBulit()) {
                cout << "����� ����.." << endl;
                GET_SINGLE(PlayerManager)->SetDefenerWiner(false);
                GET_SINGLE(EventManager)->ChangeScene(L"GameOverScene");
            }
        }
    }
}
bool Defender::IsGround(Collider* other) // block�� �ٴ��϶�, �ٴ��϶� 
{
    CollisionDirection direction = m_pCollider->GetCollisionDirection(GetPos(), other->GetOwnerPos());
    wstring name = other->GetOwner()->GetName();
    if (name == L"Wall" || direction == CollisionDirection::Bottom) {
        return true;
    }
    return false;
}
bool Defender::IsBlock(Collider* other)
{
    wstring name = other->GetOwner()->GetName();

    if (name == L"Block") {
        return true;
    }
    return false;
}
