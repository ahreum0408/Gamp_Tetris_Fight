#pragma once
#include "Object.h"
#include "Block.h"
class Block_Parent :
    public Object
{
public:
    Block_Parent();
    virtual ~Block_Parent();

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

    virtual void Rotate() abstract;
    virtual void MoveDown() abstract;
    virtual void MoveSide(bool isLeft) abstract;

    virtual void SetBlockPosition() abstract;

    virtual bool CheckCollision(const std::vector<Vec2>& positions) abstract;
    virtual const std::vector<Block*>& GetBlocks() abstract;

    virtual void SetIsDefence(bool isDefence) abstract;
    virtual bool GetIsDefence() abstract;
};