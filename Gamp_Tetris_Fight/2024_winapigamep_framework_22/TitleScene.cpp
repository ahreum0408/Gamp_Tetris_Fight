#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
//#include "Enemy.h"
//#include "CollisionManager.h"
//#include "ResourceManager.h"

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
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // �̵� ���� ����

		AddObject(oPlayer1, LAYER::PLAYER); // ���̾ �ٲ���ҰϤ�
	}
	{
		Object* oPlayer2 = new Defender;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // �̵� ���� ����
		pPlayer2->SetName(L"Player");

		AddObject(oPlayer2, LAYER::PLAYER);// ���̾ �ٲ���ҰϤ�
	}
	// Bottom Wall
	Wall* bottomWall = new Wall;
	bottomWall->SetPos({ SCREEN_WIDTH / 2, 600 });
	bottomWall->SetSize({ 500, 50 });
	AddObject(bottomWall, LAYER::Wall); 
	bottomWall->SetName(L"Wall");

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::Wall);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BLOCK);
}

void TitleScene::Update()
{
	Scene::Update();
	/*if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");*/
}
