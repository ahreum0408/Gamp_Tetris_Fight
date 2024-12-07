#include "pch.h"
#include "Block_T.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Collider.h"

Block_T::Block_T() :
	blockNum(4),
	m_vDir(1.f, 1.f),
	rotationIndex(0)
{
	for (int i = 0; i < blockNum; ++i)
	{
		Block* block = new Block(texturePath, this);
		blockVec.push_back(block);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);
	}
}

Block_T::~Block_T()
{
}

void Block_T::Update()
{
}

void Block_T::Render(HDC _hdc)
{
}

void Block_T::Rotate()
{
	// 다음 회전 상태로 변경
	rotationIndex = (rotationIndex + 1) % 4;

	int centerIndex = rotationIndex == 1 || rotationIndex == 2 ? 1 : 2;
	blockVec[centerIndex]->SetPos(GetPos());
	Vec2 centerPos = blockVec[centerIndex]->GetPos();

	int index = 0;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (Rotation[rotationIndex][y][x] == 1)
			{
				Vec2 newPos = centerPos;
				newPos.x += (x - 1) * BLOCK_SIZE;
				newPos.y += (y - 1) * BLOCK_SIZE;
				blockVec[index++]->SetPos(newPos);
			}
		}
	}
}

void Block_T::MoveDown()
{
	int centerIndex = rotationIndex == 1 || rotationIndex == 2 ? 1 : 2;
	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		pos.y += BLOCK_SIZE; // 한 칸 아래로 이동
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) SetPos(blockVec[i]->GetPos());
	}
}

void Block_T::MoveSide(bool isLeft)
{
	int centerIndex = rotationIndex == 1 || rotationIndex == 2 ? 1 : 2;

	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		float moveValue = isLeft ? -BLOCK_SIZE : BLOCK_SIZE;
		pos.x += moveValue;
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) SetPos(blockVec[i]->GetPos());
	}
}

bool Block_T::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

const std::vector<Block*>& Block_T::GetBlocks() { return blockVec; }

void Block_T::SetBlockPosition()
{
	int index = 0;
	Vec2 pos = GetPos();
	blockVec[2]->SetPos(GetPos());
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (Rotation[rotationIndex][y][x] == 1)
			{
				Vec2 newPos = pos;
				newPos.x += (x - 1) * BLOCK_SIZE;
				newPos.y += (y - 1) * BLOCK_SIZE;
				blockVec[index++]->SetPos(newPos);
			}
		}
	}
}

void Block_T::SetIsDefence(bool isDefence)
{
	for (auto block : blockVec) {
		block->SetIsDefence(isDefence);
	}
}

bool Block_T::GetIsDefence()
{
	for (auto block : blockVec) {
		if (block->GetIsDefence()) {
			return true;
		}
	}
	return false;
}

bool Block_T::IsAllChildAlive()
{
	for (auto block : blockVec) {
		if (!block->GetIsDead()) {
			return false;
		}
	}
	return true;
}

void Block_T::EnterCollision(Collider* _other)
{
}

void Block_T::StayCollision(Collider* _other)
{
}

void Block_T::ExitCollision(Collider* _other)
{
}
