#include "pch.h"
#include "Block_L.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Collider.h"

Block_L::Block_L() :
    blockNum(4),
    m_vDir(1.f, 1.f),
    rotationIndex(0)
{
	for (int i = 0; i < blockNum; ++i)
	{
		Block* block = new Block(texturePath);
		blockVec.push_back(block);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);
	}
}

Block_L::~Block_L()
{
}

void Block_L::Update()
{
}

void Block_L::Render(HDC _hdc)
{
}

void Block_L::Rotate()
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

void Block_L::MoveDown()
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

void Block_L::MoveSide(bool isLeft)
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

bool Block_L::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

const std::vector<Block*>& Block_L::GetBlocks() { return blockVec; }

void Block_L::SetBlockPosition()
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

void Block_L::EnterCollision(Collider* _other)
{
}

void Block_L::StayCollision(Collider* _other)
{
}

void Block_L::ExitCollision(Collider* _other)
{
}
