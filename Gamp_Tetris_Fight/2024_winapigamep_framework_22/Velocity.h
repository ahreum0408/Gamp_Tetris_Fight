#pragma once
#include "Component.h"
#include "Vec2.h"

class Velocity : public Component
{
public:
    Velocity();
    ~Velocity();

    void LateUpdate() override;
    void Render(HDC _hdc) override {}

    void SetVelocity(const Vec2& newVelocity) {
        m_vVelocity = newVelocity;
    }
    Vec2 GetVelocity() const { return m_vVelocity; }

private:
    Vec2 m_vPrevPos;    // ���� ��ġ
    Vec2 m_vVelocity;   // ���ν�Ƽ(���� ��ġ - ���� ��ġ)
};