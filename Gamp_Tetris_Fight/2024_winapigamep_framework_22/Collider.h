#pragma once
#include "Component.h"
#include "Object.h"

enum class CollisionDirection
{
    None,
    Top,
    Bottom,
    Left,
    Right
};
class Collider : public Component
{
public:
    Collider();
    ~Collider();
public:
    void LateUpdate() override;
    void Render(HDC _hdc) override;
public:
    void EnterCollision(Collider* _other); // 충돌진입
    void StayCollision(Collider* _other); // 충돌중
    void ExitCollision(Collider* _other); // 충돌해제
    const UINT& GetID() const { return m_ID; }
    CollisionDirection GetCollisionDirection(const Vec2& objectPos, const Vec2& otherPos) const;
    Vec2 GetNormal(const Vec2& collisionPoint) const;
    Vec2 GetPosition() const {
        return GetOwner()->GetPos();
    }
public:
    void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
    const Vec2& GetSize() const { return m_vSize; }
    void SetOffSetPos(Vec2 _vOffsetPos)
    {
        m_vOffsetPos = _vOffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
    const Vec2& GetLatedUpatedPos() const
    {
        return m_vLatePos;
    }
    Vec2 GetOwnerPos() {
        return GetOwner()->GetPos();
    }
    void SetIsTrigger(bool value) { isTrigger = value; }
    bool GetIsTrigger() const { return isTrigger; }
private:
    bool m_showDebug = false;
    UINT m_ID; // 충돌체 고유 ID값
    static UINT m_sNextID;

    Vec2 m_vSize;
    Vec2 m_vOffsetPos;
    Vec2 m_vLatePos;

    bool isTrigger = true;
};