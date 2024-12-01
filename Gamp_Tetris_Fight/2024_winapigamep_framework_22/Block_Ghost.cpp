#include "pch.h"
#include "Block_Ghost.h"
#include "EventManager.h"

Block_Ghost::Block_Ghost()
{
}

Block_Ghost::~Block_Ghost()
{
}

void Block_Ghost::Update()
{
}

void Block_Ghost::Render(HDC _hdc)
{
}

void Block_Ghost::Rotate()
{
}

void Block_Ghost::MoveDown()
{
}

void Block_Ghost::MoveSide(bool isLeft)
{
}

bool Block_Ghost::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

const std::vector<Block*>& Block_Ghost::GetBlocks() { return blockVec; }

void Block_Ghost::SetBlockPosition()
{
}

void Block_Ghost::SyncWithCurrentBlock(Block_Parent* currentBlock)
{
    if (!currentBlock) return;

    SetPos(currentBlock->GetPos());

    // 현재 블록의 구성을 고스트 블록에 복사
    const std::vector<Block*>& currentBlocks = currentBlock->GetBlocks();

    ClearBlocks();

    // 현재 블록 구성에 맞게 고스트 블록 생성
    for (Block* block : currentBlocks)
    {
        Block* ghostBlock = new Block(texturePath);
        ghostBlock->SetPos(block->GetPos());
        blockVec.push_back(block);
    }
}

void Block_Ghost::ClearBlocks()
{
    for (Block* block : blockVec)
    {
        GET_SINGLE(EventManager)->DeleteObject(block);
    }

    blockVec.clear();
}
