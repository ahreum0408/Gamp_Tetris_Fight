#include "pch.h"
#include "Block_Z.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Collider.h"

Block_Z::Block_Z() :
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

Block_Z::~Block_Z()
{
}

void Block_Z::Update()
{
}

void Block_Z::Render(HDC _hdc)
{
}

void Block_Z::Rotate()
{
	// 다음 회전 상태로 변경
	rotationIndex = (rotationIndex + 1) % 4;

	int centerIndex = 0;
	switch (rotationIndex)
	{
	case 0:
		centerIndex = 3;
		break;
	case 1:
		centerIndex = 1;
		break;
	case 2:
		centerIndex = 0;
		break;
	case 3:
		centerIndex = 2;
		break;
	}
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

void Block_Z::MoveDown()
{
	int centerIndex = 0;
	switch (rotationIndex)
	{
	case 0:
		centerIndex = 3;
		break;
	case 1:
		centerIndex = 1;
		break;
	case 2:
		centerIndex = 0;
		break;
	case 3:
		centerIndex = 2;
		break;
	}

	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		pos.y += BLOCK_SIZE; // 한 칸 아래로 이동
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) SetPos(blockVec[i]->GetPos());
	}
}

void Block_Z::MoveSide(bool isLeft)
{
	int centerIndex = 0;
	switch (rotationIndex)
	{
	case 0:
		centerIndex = 3;
		break;
	case 1:
		centerIndex = 1;
		break;
	case 2:
		centerIndex = 0;
		break;
	case 3:
		centerIndex = 2;
		break;
	}

	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		float moveValue = isLeft ? -BLOCK_SIZE : BLOCK_SIZE;
		pos.x += moveValue;
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) SetPos(blockVec[i]->GetPos());
	}
}

bool Block_Z::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

const std::vector<Block*>& Block_Z::GetBlocks() { return blockVec; }

void Block_Z::SetBlockPosition()
{
	int index = 0;
	Vec2 pos = GetPos();
	blockVec[3]->SetPos(GetPos());
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

void Block_Z::SetIsDefence(bool isDefence)
{
	for (auto block : blockVec) {
		block->SetIsDefence(isDefence);
	}
}

bool Block_Z::GetIsDefence()
{
	for (auto block : blockVec) {
		if (block->GetIsDefence()) {
			return true;
		}
	}
	return false;
}

bool Block_Z::IsAllChildLive()
{
	for (auto block : blockVec) {
		if (!block->GetIsDead()) {
			return false;
		}
	}
	return true;
}

void Block_Z::EnterCollision(Collider* _other)
{
}

void Block_Z::StayCollision(Collider* _other)
{
}

void Block_Z::ExitCollision(Collider* _other)
{
}
