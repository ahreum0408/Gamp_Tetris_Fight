#include "pch.h"
#include "GameOver.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "PlayerManager.h"

GameOver::GameOver() :
	m_pTex(nullptr), retryTextTex(nullptr), exitTextTex(nullptr),
	index(0), curIndex(1)
{
	// 둘 중 누가 이겼는지 빨간 디노인지
	cout << GET_SINGLE(PlayerManager)->GetWiner() << endl;
	if (GET_SINGLE(PlayerManager)->GetWiner())
		m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"RedDinoWin", L"Texture\\GameOverScene\\RedDinoWin.bmp");
	else
		m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"GreenDinoWin", L"Texture\\GameOverScene\\GreenDinoWin.bmp");

	retryTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"RetryTextOff", L"Texture\\GameOverScene\\RetryTextOff.bmp");
	exitTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ExitTextOff", L"Texture\\StartScene\\ExitTextOff.bmp");

	GET_SINGLE(ResourceManager)->LoadSound(L"UIClick", L"Sound\\UIClick.wav", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"GameWin", L"Sound\\GameWin.wav", false);
	GET_SINGLE(ResourceManager)->Play(L"GameWin");
}

GameOver::~GameOver()
{
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::EFFECT);
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
}

void GameOver::Update()
{
	if (GET_KEYDOWN(KEY_TYPE::DOWN) || GET_KEYDOWN(KEY_TYPE::S))
	{
		if (index < 1)
		{
			index += 1;
			GET_SINGLE(ResourceManager)->Play(L"UIClick");
		}
	}

	if (GET_KEYDOWN(KEY_TYPE::UP) || GET_KEYDOWN(KEY_TYPE::W))
	{

		if (index > 0)
		{
			index -= 1;
			GET_SINGLE(ResourceManager)->Play(L"UIClick");
		}
	}

	if (index != curIndex)
		switch (index)
		{
		case 0:
			curIndex = 0;
			retryTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"RetryTextOn", L"Texture\\GameOverScene\\RetryTextOn.bmp");
			exitTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ExitTextOff", L"Texture\\StartScene\\ExitTextOff.bmp");
			break;
		case 1:
			curIndex = 1;
			retryTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"RetryTextOff", L"Texture\\GameOverScene\\RetryTextOff.bmp");
			exitTextTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ExitTextOn", L"Texture\\StartScene\\ExitTextOn.bmp");
			break;
		default:
			break;
		}
}

void GameOver::Render(HDC _hdc)
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
		// Retry
		Vec2 vPos = { SCREEN_WIDTH / 4, 500 };
		Vec2 vSize = { 100, 250 };
		int width = retryTextTex->GetWidth();
		int height = retryTextTex->GetHeight();
		::TransparentBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height,
			retryTextTex->GetTexDC()
			, 0, 0, width, height, RGB(255, 0, 255));
	}

	{
		// Exit
		Vec2 vPos = { SCREEN_WIDTH / 4, 600 };
		Vec2 vSize = { 100, 250 };
		int width = exitTextTex->GetWidth();
		int height = exitTextTex->GetHeight();
		::TransparentBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height,
			exitTextTex->GetTexDC()
			, 0, 0, width, height, RGB(255, 0, 255));
	}
}
