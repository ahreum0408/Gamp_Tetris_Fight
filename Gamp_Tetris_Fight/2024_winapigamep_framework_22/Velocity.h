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
    Vec2 m_vPrevPos;    // 이전 위치
    Vec2 m_vVelocity;   // 벨로시티(현재 위치 - 이전 위치)
};