#include "pch.h"
#include "GameScene.h"
//#include "Block_I.h"
//#include "Block_J.h"
//#include "Block_L.h"
//#include "Block_O.h"
//#include "Block_S.h"
//#include "Block_T.h"
//#include "Block_Z.h"
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
				SCREEN_HEIGHT / 2});
		board->SetSize({ 400.f, 800.f });
		AddObject(board, LAYER::BACKGROUND);
		board->CreateBlock();

		m_boardPos = board->GetPos();
		m_boardSize = board->GetSize();
	}
    {
        float leftEdge = m_boardPos.x - m_boardSize.x / 2;
        float rightEdge = m_boardPos.x + m_boardSize.x / 2;
        float bottomEdge = m_boardPos.y + m_boardSize.y / 2;

        // Left Wall
        Wall* leftWall = new Wall;
        leftWall->SetPos({ leftEdge - 125, m_boardPos.y });
        leftWall->SetSize({ 50, (int)m_boardSize.y });
        AddObject(leftWall, LAYER::Wall);

        // Right Wall
        Wall* rightWall = new Wall;
        rightWall->SetPos({ rightEdge + -75, m_boardPos.y });
        rightWall->SetSize({ 50, (int)m_boardSize.y });
        AddObject(rightWall, LAYER::Wall);

        // Bottom Wall
        Wall* bottomWall = new Wall;
        bottomWall->SetPos({ m_boardPos.x - 100, bottomEdge + 25 });
        bottomWall->SetSize({ (int)m_boardSize.x, 50 });
        AddObject(bottomWall, LAYER::Wall);
    }
	{
		Object* oPlayer1 = new Striker;
		oPlayer1->SetPos({ SCREEN_WIDTH / 2.f,300.f });
		oPlayer1->SetSize({ 100.f,100.f });

		Player* pPlayer1 = dynamic_cast<Player*>(oPlayer1);
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // 이동 방향 설정
		AddObject(oPlayer1, LAYER::PLAYER); // 레이어도 바꿔야할겅ㅁ


		Object* oPlayer2 = new Defender;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // 이동 방향 설정
		AddObject(oPlayer2, LAYER::PLAYER);// 레이어도 바꿔야할겅ㅁ

		GET_SINGLE(PlayerManager)->SetStriker(dynamic_cast<Striker*>(oPlayer1));
		GET_SINGLE(PlayerManager)->SetDefender(dynamic_cast<Defender*>(oPlayer2));
	 
	}
    GET_SINGLE(CollisionManager)->CheckLayer(LAYER::Wall, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::Wall);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::BLOCK);
}

void GameScene::Update()
{
	Scene::Update();
}
