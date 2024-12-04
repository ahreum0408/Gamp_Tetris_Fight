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

    // ���� ��ġ
    Vec2 currentPos = GetOwner()->GetPos();

    // ���ν�Ƽ ��� (���� ��ġ - ���� ��ġ)
    m_vVelocity = currentPos - m_vPrevPos;

    // ���� �������� ���� ���� ��ġ ����
    m_vPrevPos = currentPos;
}