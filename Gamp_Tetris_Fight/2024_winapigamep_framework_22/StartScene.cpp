#include "pch.h"
#include "StartScene.h"
#include "Title.h"
#include "GameRule.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

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

	GET_SINGLE(ResourceManager)->LoadSound(L"UIClick", L"Sound\\UIClick.wav", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGMTitle", L"Sound\\BGM\\BGM_Title.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGMTitle");
}

void StartScene::Update()
{
	Scene::Update();

	if (!isGameRuleOn && (GET_KEYDOWN(KEY_TYPE::SPACE) || GET_KEYDOWN(KEY_TYPE::ENTER)))
	{
		GET_SINGLE(ResourceManager)->Play(L"UIClick");
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
	{
		GET_SINGLE(ResourceManager)->Play(L"UIClick");
		isGameRuleOn = false;
	}

	if (title != nullptr && PopUp != nullptr)
	{
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
}

void StartScene::Release()
{
	title = nullptr;
	PopUp = nullptr;

	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	Scene::Release();
}
