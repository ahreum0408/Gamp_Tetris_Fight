#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDISelector.h"
#include "Velocity.h"
#include <string>

UINT Collider::m_sNextID = 0;

Collider::Collider()
    : m_vSize(30.f, 30.f)
    , m_vLatePos(0.f, 0.f)
    , m_vOffsetPos(0.f, 0.f)
    , m_ID(m_sNextID++)
{
}

Collider::~Collider()
{
}

void Collider::LateUpdate()
{
    const Object* pOwner = GetOwner();
    Vec2 vPos = pOwner->GetPos();
    m_vLatePos = vPos + m_vOffsetPos;
}

void Collider::Render(HDC _hdc)
{
    PEN_TYPE ePen = PEN_TYPE::GREEN;
    if (m_showDebug)
        ePen = PEN_TYPE::RED;
    GDISelector pen(_hdc, ePen);
    GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
    RECT_RENDER(_hdc, m_vLatePos.x, m_vLatePos.y,
        m_vSize.x, m_vSize.y);

}

void Collider::EnterCollision(Collider* _other)
{
    wstring name = _other->GetOwner()->GetName();
    if (!GetOwner()->GetComponent<Collider>()->GetIsTrigger() && name == L"Block")
    {
        Velocity* velocity = GetOwner()->GetComponent<Velocity>();
        if (velocity)
        {
            Vec2 ownerPos = GetOwner()->GetPos();
            Vec2 otherPos = _other->GetOwner()->GetPos();

            // 충돌 방향 계산 (자신 -> 상대 방향으로 계산)
            Vec2 collisionDir = ownerPos - otherPos; // 상대방 -> 자신으로 방향 설정
            collisionDir.Normalize();

            // 밀어내기 강도 증가
            Vec2 pushBack = collisionDir * 1.f; // 밀어내는 강도
            Vec2 newPos = ownerPos + pushBack;   // 새로운 위치 업데이트
            GetOwner()->SetPos(newPos);
        }
    }

    // 충돌 이벤트 처리
    GetOwner()->EnterCollision(_other);
    m_showDebug = true;
}

void Collider::StayCollision(Collider* _other)
{
    wstring name = _other->GetOwner()->GetName();
    if (!GetOwner()->GetComponent<Collider>()->GetIsTrigger() && name == L"Block")
    {
        Velocity* velocity = GetOwner()->GetComponent<Velocity>();
        if (velocity)
        {
            Vec2 ownerPos = GetOwner()->GetPos();
            Vec2 otherPos = _other->GetOwner()->GetPos();

            // 충돌 방향 계산 (자신 -> 상대 방향으로 계산)
            Vec2 collisionDir = ownerPos - otherPos; // 상대방 -> 자신으로 방향 설정
            collisionDir.Normalize();

            // 밀어내기 강도 증가
            Vec2 pushBack = collisionDir * 1.f; // 밀어내는 강도
            Vec2 newPos = ownerPos + pushBack;   // 새로운 위치 업데이트
            GetOwner()->SetPos(newPos);
        }
    }

    // 충돌 이벤트 처리
    GetOwner()->StayCollision(_other);
    m_showDebug = true;
}

void Collider::ExitCollision(Collider* _other)
{
    m_showDebug = false;
    GetOwner()->ExitCollision(_other);
}

CollisionDirection Collider::GetCollisionDirection(const Vec2& objectPos, const Vec2& otherPos) {
    float deltaX = otherPos.x - objectPos.x;
    float deltaY = otherPos.y - objectPos.y;

    float absX = std::fabs(deltaX);
    float absY = std::fabs(deltaY);

    if (absX > absY) {
        return (deltaX > 0) ? CollisionDirection::Left : CollisionDirection::Right;
    }
    else {
        return (deltaY > 0) ? CollisionDirection::Bottom : CollisionDirection::Top;
    }
}