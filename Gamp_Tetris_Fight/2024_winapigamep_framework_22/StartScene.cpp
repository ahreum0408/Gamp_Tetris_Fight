#include "pch.h"
#include "StartScene.h"
#include "Title.h"
#include "GameRule.h"
#include "InputManager.h"
#include "SceneManager.h"

Title* title;
GameRule* PopUp;

void StartScene::Init()
{
	if (title == nullptr)
	{
		Title* titleTemp = new Title;
		titleTemp->SetPos({ SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 });
		titleTemp->SetSize({ 1000.f, 800.f });
		title = titleTemp;
	}
	AddObject(title, LAYER::BACKGROUND);

	if (PopUp == nullptr)
	{
		GameRule* gameRule = new GameRule;
		gameRule->SetPos({ SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 });
		gameRule->SetSize(Vec2(400.f, 400.f));
		PopUp = gameRule;
	}
	AddObject(PopUp, LAYER::BACKGROUND);
}

void StartScene::Update()
{
	Scene::Update();

	if (!isGameRuleOn && (GET_KEYDOWN(KEY_TYPE::SPACE) || GET_KEYDOWN(KEY_TYPE::ENTER)))
	{
		switch (title->curIndex)
		{
		case 0:
			GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
			break;
		case 1:
			isGameRuleOn = true;
			break;
		case 2:
			exit(1);
			break;
		default:
			break;
		}
	}
	else if (isGameRuleOn && GET_KEYDOWN(KEY_TYPE::ESC))
		isGameRuleOn = false;

	if (isGameRuleOn)
	{
		title->isGameRuleOn = true;
		PopUp->RulePopUp = true;
	}
	else
	{
		title->isGameRuleOn = false;
		PopUp->RulePopUp = false;
	}
}

void StartScene::Release()
{
	title = nullptr;
	PopUp = nullptr;

	Scene::Release();
}
