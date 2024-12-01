#pragma once
#include "Block_Parent.h"
class Block_Ghost :
    public Block_Parent
{
public:
    Block_Ghost();
    ~Block_Ghost();
    void Update() override;
    void Render(HDC _hdc) override;

    void Rotate() override;
    void MoveDown() override;
    void MoveSide(bool isLeft) override;

    void SetBlockPosition() override;

    bool CheckCollision(const std::vector<Vec2>& positions) override;
    const std::vector<Block*>& GetBlocks() override;
public:
    void SyncWithCurrentBlock(Block_Parent* currentBlock);
    void ClearBlocks();
private:
    wstring texturePath = L"Texture\\GreenBlock.bmp";

    vector<Block*> blockVec;
};
