#include "pch.h"
#include "Velocity.h"
#include "Object.h"

Velocity::Velocity() :
    m_vPrevPos(0.f, 0.f),
    m_vVelocity(0.f, 0.f)
{
}

Velocity::~Velocity() {}

void Velocity::LateUpdate()
{
    if (!GetOwner()) return;

    // 현재 위치
    Vec2 currentPos = GetOwner()->GetPos();

    // 벨로시티 계산 (현재 위치 - 이전 위치)
    m_vVelocity = currentPos - m_vPrevPos;

    // 다음 프레임을 위해 현재 위치 저장
    m_vPrevPos = currentPos;
}