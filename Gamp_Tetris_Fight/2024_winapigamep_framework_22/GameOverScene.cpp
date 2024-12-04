#include "pch.h"
#include "GameOverScene.h"
#include "GameOver.h"
#include "InputManager.h"
#include "SceneManager.h"

void GameOverScene::Init()
{
	if (gameOver == nullptr)
	{
		GameOver* temp = new GameOver;
		temp->SetPos({ SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 });
		temp->SetSize({ 1000.f, 800.f });
		gameOver = temp;
	}
	AddObject(gameOver, LAYER::BACKGROUND);

}

void GameOverScene::Update()
{
	Scene::Update();

	if ((GET_KEYDOWN(KEY_TYPE::SPACE) || GET_KEYDOWN(KEY_TYPE::ENTER)))
	{
		switch (gameOver->curIndex)
		{
		case 0:
			GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
			break;
		case 1:
			exit(1);
			break;
		default:
			break;
		}
	}
}

void GameOverScene::Release()
{
	gameOver = nullptr;

	Scene::Release();
}
