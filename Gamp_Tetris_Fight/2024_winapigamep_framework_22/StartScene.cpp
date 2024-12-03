#include "pch.h"
#include "StartScene.h"
#include "Title.h"

void StartScene::Init()
{
	{
		Title* title = new Title;
		title->SetPos({ SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 });
		title->SetSize({ 1000.f, 800.f });
		AddObject(title, LAYER::BACKGROUND);
	}
}

void StartScene::Update()
{
	Scene::Update();
}
