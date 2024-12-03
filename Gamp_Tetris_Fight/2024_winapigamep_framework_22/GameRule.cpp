#include "pch.h"
#include "GameRule.h"
#include "ResourceManager.h"

GameRule::GameRule() :
	m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"GameRule", L"Texture\\StartScene\\GameRule.bmp");
}

GameRule::~GameRule()
{
}

void GameRule::Update()
{
}

void GameRule::Render(HDC _hdc)
{
	if (RulePopUp)
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
	}
}
