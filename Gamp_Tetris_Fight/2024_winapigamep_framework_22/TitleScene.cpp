#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "Striker.h"
#include "Defender.h"
#include "Wall.h"
#include "CollisionManager.h"

void TitleScene::Init()
{
	{
		Object* oPlayer1 = new Striker;

		oPlayer1->SetPos({ SCREEN_WIDTH / 2.f,300.f });
		oPlayer1->SetSize({ 100.f,100.f });

		Player* pPlayer1 = dynamic_cast<Player*>(oPlayer1);
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // 이동 방향 설정

		AddObject(oPlayer1, LAYER::DEFENDER); // 레이어도 바꿔야할겅ㅁ
	}
	{
		Object* oPlayer2 = new Defender;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // 이동 방향 설정
		pPlayer2->SetName(L"Player");

		AddObject(oPlayer2, LAYER::DEFENDER);// 레이어도 바꿔야할겅ㅁ
	}
	// Bottom Wall
	Wall* bottomWall = new Wall;
	bottomWall->SetPos({ SCREEN_WIDTH / 2, 600 });
	bottomWall->SetSize({ 500, 50 });
	AddObject(bottomWall, LAYER::Wall);
	bottomWall->SetName(L"Wall");

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DEFENDER, LAYER::Wall);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::DEFENDER, LAYER::BLOCK);
}

void TitleScene::Update()
{
	Scene::Update();
}
