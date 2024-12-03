#include "pch.h"
#include "Title.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Animator.h"
#include "Core.h"

Title::Title() :
	m_pTex(nullptr), gameRuleTex(nullptr), startTextTex(nullptr), gameruleTextTex(nullptr), exitTextTex(nullptr),
	index(0), curIndex(0),
	isGameRuleOn(false),
	mousePos(),
	startRect({ 50, 320, 250, 400 }),
	gameruleRect({ 50, 420, 350, 500 }),
	exitRect({ 50, 520, 250, 600 })
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Title", L"Texture\\StartScene\\StartScene.bmp");
	//gameRuleTex = GET_SINGLE(ResourceManager)->TextureLoad(L"GameRule", L"Texture\\gamp-background.bmp");

	startTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"StartTextOff", L"Texture\\StartScene\\StartTextOff.bmp");
	//gameruleTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"GameRuleTextOff", L"Texture\\gamp-background.bmp");
	//exitTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ExitTextOff", L"Texture\\gamp-background.bmp");
}

Title::~Title()
{
}

void Title::Update()
{
	if (isGameRuleOn)
		return;

	//GetCursorPos(&mousePos);
	//ScreenToClient(Core::GetInst()->GetHwnd(), &mousePos);

	//if (PtInRect(&startRect, mousePos))
	//	index = 0;
	//if (PtInRect(&gameruleRect, mousePos))
	//	index = 1;
	//if (PtInRect(&exitRect, mousePos))
	//	index = 2;

	if (GET_KEYDOWN(KEY_TYPE::DOWN) || GET_KEYDOWN(KEY_TYPE::S) && index < 2)
		index += 1;
	if (GET_KEYDOWN(KEY_TYPE::UP) || GET_KEYDOWN(KEY_TYPE::W) && index > 0)
		index -= 1;

	if (index != curIndex)
		switch (index)
		{
		case 0:
			curIndex = 0;
			startTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"StartTextOn", L"Texture\\StartScene\\StartTextOn.bmp");
			break;
		case 1:
			curIndex = 1;
			//gameruleTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"GameRuleTextOn", L"Texture\\StartScene\\GameruleTextOn.bmp");
			break;
		case 2:
			curIndex = 2;
			//exitTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ExitTextOn", L"Texture\\StartScene\\StartTextOn.bmp");
			break;
		default:
			break;
		}
}

void Title::Render(HDC _hdc)
{
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

	{
		// Start
		Vec2 vPos = { SCREEN_WIDTH / 4, 500 };
		Vec2 vSize = { 100, 250 };
		int width = startTextTex->GetWidth();
		int height = startTextTex->GetHeight();
		::TransparentBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height,
			startTextTex->GetTexDC()
			, 0, 0, width, height, RGB(255, 0, 255));
	}

	{
		//// GameRule
		//Vec2 vPos = GetPos();
		//Vec2 vSize = GetSize();
		//int width = gameruleTextTex->GetWidth();
		//int height = gameruleTextTex->GetHeight();
		//::TransparentBlt(_hdc
		//	, (int)(vPos.x - width / 2)
		//	, (int)(vPos.y - height / 2)
		//	, width, height,
		//	gameruleTextTex->GetTexDC()
		//	, 0, 0, width, height, RGB(255, 0, 255));
	}

	{
		//// Exit
		//Vec2 vPos = GetPos();
		//Vec2 vSize = GetSize();
		//int width = exitTextTex->GetWidth();
		//int height = exitTextTex->GetHeight();
		//::TransparentBlt(_hdc
		//	, (int)(vPos.x - width / 2)
		//	, (int)(vPos.y - height / 2)
		//	, width, height,
		//	exitTextTex->GetTexDC()
		//	, 0, 0, width, height, RGB(255, 0, 255));
	}
}
