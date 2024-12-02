#include "pch.h"
#include "GameScene.h"
#include "Board.h"

#include "Striker.h"
#include "Defender.h"
#include "Wall.h"
#include "CollisionManager.h"
#include "PlayerManager.h"

void GameScene::Init()
{
	
	{
		Board* board = new Board;
		board->SetPos({ SCREEN_WIDTH / 2 + 100,
				SCREEN_HEIGHT / 2 - 200});
		board->SetSize({ 400.f, 800.f });
		AddObject(board, LAYER::BACKGROUND);
		board->CreateBlock();
	}
    {
        float leftEdge = BOARD_POSX - BOARD_SIZEX / 2;
        float rightEdge = BOARD_POSX + BOARD_SIZEX / 2;
        float bottomEdge = BOARD_POSY + BOARD_SIZEY / 2;

        // Left Wall
        Wall* leftWall = new Wall;
		leftWall->SetPos({ (int)leftEdge - 125, BOARD_POSY });
		leftWall->SetSize({ 50, BOARD_SIZEY });
		leftWall->SetWallSize(leftWall->GetSize());
		leftWall->SetName(L"SideWall");
        AddObject(leftWall, LAYER::Wall);

        // Right Wall
        Wall* rightWall = new Wall;
        rightWall->SetPos({ (int)rightEdge -75, BOARD_POSY });
        rightWall->SetSize({ 50, BOARD_SIZEY });
		rightWall->SetWallSize(rightWall->GetSize());
		rightWall->SetName(L"SideWall");
        AddObject(rightWall, LAYER::Wall);

        // Bottom Wall
        Wall* bottomWall = new Wall;
        bottomWall->SetPos({ BOARD_POSX - 100, (int)bottomEdge + 25 });
        bottomWall->SetSize({ BOARD_SIZEX, 50 });
		bottomWall->SetWallSize(bottomWall->GetSize());
		bottomWall->SetName(L"BottomWall");
        AddObject(bottomWall, LAYER::Wall);
    }
	{
		Object* oPlayer1 = new Striker;

		oPlayer1->SetPos({ SCREEN_WIDTH / 2.f,300.f });
		oPlayer1->SetSize({ 100.f,100.f });

		Player* pPlayer1 = dynamic_cast<Player*>(oPlayer1);
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // 이동 방향 설정
		pPlayer1->SetName(L"Striker");

		AddObject(oPlayer1, LAYER::PLAYER); // 레이어도 바꿔야할겅ㅁ
	}
	{
		Object* oPlayer2 = new Defender;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // 이동 방향 설정
		pPlayer2->SetName(L"Defender");

		AddObject(oPlayer2, LAYER::PLAYER);// 레이어도 바꿔야할겅ㅁ
	}

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::Wall);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BLOCK);
}

void GameScene::Update()
{
	Scene::Update();
}
