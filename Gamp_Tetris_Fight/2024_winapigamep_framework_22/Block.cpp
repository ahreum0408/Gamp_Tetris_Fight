#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include <format>

Block::Block(wstring path) :
	m_vDir(1.f, 1.f),
	m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(std::format(L"{}Block", path), path);
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ BLOCK_SIZE, BLOCK_SIZE });
}
Block::~Block() {}

void Block::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}
void Block::Update()
{
}

void Block::EnterCollision(Collider* _other)
{
}

void Block::StayCollision(Collider* _other)
{
}

void Block::ExitCollision(Collider* _other)
{
}
