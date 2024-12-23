#include "pch.h"
#include "Board.h"
#include "ResourceManager.h"
#include "PlayerManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Block.h"
#include "Block_Parent.h"
#include "Texture.h"
#include "Scene.h"
#include "Block_I.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"
#include "Camera.h"

Board::Board() :
    boardWidth(10), boardHeight(19), isSkill(false),
    currentBlock(nullptr), nextBlock(BLOCK_TYPE::NONE),
    m_pTex(nullptr), nextBlockTex(nullptr)
{
    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Board", L"Texture\\gamp-background.bmp");
    boardVec.resize(boardHeight, std::vector<Block*>(boardWidth));

    this->SetName(L"Block");

    // Sound
    GET_SINGLE(ResourceManager)->LoadSound(L"BlockBreak", L"Sound\\BlockBreak.wav", false);
    GET_SINGLE(ResourceManager)->LoadSound(L"BlockDown", L"Sound\\BlockDown.wav", false);
    GET_SINGLE(ResourceManager)->LoadSound(L"BigBlockDown", L"Sound\\BigBlockDown.wav", false);
}

Board::~Board()
{
    // Board 리셋
    for (int i = 0; i < boardHeight; ++i)
    {
        for (int j = 0; j < boardWidth; ++j)
        {
            if (boardVec[i][j] != nullptr)
            {
                GET_SINGLE(EventManager)->DeleteObject(boardVec[i][j]);
            }
        }
    }
    boardVec.clear();
}

void Board::Render(HDC _hdc)
{
    {
        // Board
        Vec2 vPos = GetPos();
        Vec2 vSize = GetSize();
        Vec2 camerapos = GET_SINGLE(Camera)->GetCameraPos();
        int width = m_pTex->GetWidth();
        int height = m_pTex->GetHeight();

        ::TransparentBlt(_hdc
            , (int)(vPos.x - width / 2 - ((int)camerapos.x))
            , (int)(vPos.y - height / 2 - ((int)camerapos.y))
            , width, height,
            m_pTex->GetTexDC()
            , 0, 0, width, height, RGB(255, 0, 255));
    }

    {
        // NextBlock
        Vec2 boardOrigin = GetBoardOrigin();
        Vec2 vPos = { boardOrigin.x + boardWidth * BLOCK_SIZE + 100.f,
        boardOrigin.y + 60.f };
        Vec2 vSize = { 120.f,80.f };
        Vec2 camerapos = GET_SINGLE(Camera)->GetCameraPos();
        int width = nextBlockTex->GetWidth();
        int height = nextBlockTex->GetHeight();
        ::TransparentBlt(_hdc
            , (int)(vPos.x - width / 2 - ((int)camerapos.x))
            , (int)(vPos.y - height / 2 - ((int)camerapos.y))
            , width, height,
            nextBlockTex->GetTexDC()
            , 0, 0, width, height, RGB(255, 0, 255));
    }

    {
        HFONT myFont = ::CreateFont(
            30                         // 높이
            , 0                        // 폭 0이면 높이와 비례
            , 0                        // 글자 전체 기울기
            , 0                        // 기준선이 정해진 기울기
            , 0                       // 폰트의 두께
            , 0                        // 이탤릭
            , 0                        // 밑줄
            , 0                        // 취소선
            , DEFAULT_CHARSET          // 케릭터 셋
            , 0                        // 정밀도
            , 0                        // 정밀도
            , 0                        // 정밀도
            , 0                        // 정밀도
            , L"던파 비트비트체 v2"           // 글꼴이름
        );
        HFONT oldFont = (HFONT)::SelectObject(_hdc, myFont);
        SetTextColor(_hdc, RGB(255, 255, 255));
        SetBkMode(_hdc, TRANSPARENT);

        {
            // 스킬
            wstring wstr = L"공격수 스킬 수 : " + std::to_wstring(GET_SINGLE(PlayerManager)->GetStrikerSkillCount());
            TextOut(_hdc, 120, 60, wstr.c_str(), wstr.length());
            wstr = L"수비수 스킬 수 : " + std::to_wstring(GET_SINGLE(PlayerManager)->GetDefenderSkillCount());
            TextOut(_hdc, 120, 95, wstr.c_str(), wstr.length());

            // 공격수
            TextOut(_hdc, GetPos().x + 110, 180, L"[공격수]", wcslen(L"[공격수]"));
            TextOut(_hdc, GetPos().x + 110, 215, L"블럭 회전 : W", wcslen(L"블럭 회전 : W"));
            TextOut(_hdc, GetPos().x + 110, 250, L"좌우이동 : A, D", wcslen(L"좌우이동 : A, D"));
            TextOut(_hdc, GetPos().x + 110, 285, L"스킬 : LShift", wcslen(L"스킬 : LShift"));
            // 수비수
            TextOut(_hdc, GetPos().x + 110, 350, L"[수비수]", wcslen(L"[수비수]"));
            TextOut(_hdc, GetPos().x + 110, 385, L"좌우이동 : 오른쪽 왼쪽 화살표", wcslen(L"좌우이동 : 오른쪽 왼쪽 화살표"));
            TextOut(_hdc, GetPos().x + 110, 420, L"점프 : 위쪽 화살표", wcslen(L"점프 : 위쪽 화살표"));
            TextOut(_hdc, GetPos().x + 110, 455, L"패딩 : Space", wcslen(L"패딩 : Space"));
        }

        SelectObject(_hdc, oldFont);
        DeleteObject(myFont);
    }
}

void Board::Update()
{
    if (isGameOver) return;
    if (currentBlock->IsAllChildAlive()) {
        currentMoveDownDelay = moveDownDelay;

        currentBlock = nullptr;
        CreateBlock();
        m_isFireing = false;
        cout << m_isFireing << endl;
    }
#pragma region BlockMove
    if (currentBlock && !m_isFireing)
    {
        if (!isSkill)
        {
            // W 키를 눌러 블록 회전
            if (GET_KEYDOWN(KEY_TYPE::W))
            {
                currentBlock->Rotate();
                if (false == CheckClampRotat(currentBlock))
                {
                    currentBlock->Rotate();
                    currentBlock->Rotate();
                    currentBlock->Rotate();
                }
            }
            // A, D 키를 눌러 블록 이동
            if (GET_KEYDOWN(KEY_TYPE::A))
            {
                currentBlock->MoveSide(true);
                if (CheckClampLeft(currentBlock->GetBlocks()))
                    currentBlock->MoveSide(false);
            }
            if (GET_KEYDOWN(KEY_TYPE::D))
            {
                currentBlock->MoveSide(false);
                if (CheckClampRight(currentBlock->GetBlocks()))
                    currentBlock->MoveSide(true);
            }

        }
        // LSHIFT 키를 눌러 블록 쾅 찍기
        if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
        {
            if (GET_SINGLE(PlayerManager)->StrikerUseSkill()) {
                isSkill = true;
                currentMoveDownDelay = 0;
                GET_SINGLE(ResourceManager)->Play(L"BigBlockDown");
            }
            else {
                cout << "you can't use skill" << endl;
            }
        }

        // Block Down
        if (moveDownTimer >= currentMoveDownDelay)
        {
            if (CheckFloor(currentBlock->GetBlocks()))
            {
                currentMoveDownDelay = moveDownDelay;

                // 1. 블럭 쌓고
                BuildBlock(currentBlock);
                if (!isSkill) GET_SINGLE(ResourceManager)->Play(L"BlockDown");
                if (isGameOver) return;
                isSkill = false;
                // 2. 줄 찼는지 검사
                ClearFullRows();
                // 3. 새로운 블럭 생성
                currentBlock = nullptr;
                CreateBlock();
            }
            if (!currentBlock->GetIsDefence()) {
                currentBlock->MoveDown(); // 이게 바닥에 내리는거
            }
            else {
                m_isFireing = true;
                cout << m_isFireing << endl;
            }
            moveDownTimer = 0;
        }
        else
            moveDownTimer++;
    }
#pragma endregion
}

void Board::BuildBlock(Block_Parent* blockParent)
{
    Vec2 boardOrigin = GetBoardOrigin();

    for (Block* block : blockParent->GetBlocks())
    {
        // 보드 기준으로 계산한 위치
        float x = block->GetPos().x - boardOrigin.x;
        float y = block->GetPos().y - boardOrigin.y;

        int row = y / BLOCK_SIZE;
        int col = x / BLOCK_SIZE;

        if (row == boardHeight - endRow)
        {
            isGameOver = true;
            cout << "공격수 배패.." << endl;
            GET_SINGLE(PlayerManager)->SetDefenerWiner(true);
            GET_SINGLE(EventManager)->ChangeScene(L"GameOverScene");
            return;
        }
        currentBlock->SetIsBulit(true);
        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth)
        {
            if (boardVec[row][col] == nullptr)
                boardVec[row][col] = block;
        }

        GET_SINGLE(PlayerManager)->DefenderDieCheck(block);
    }
}

void Board::ClearFullRows()
{
    for (int row = 0; row < boardHeight; ++row)
    {
        if (IsRowFull(row))
        {
            RemoveRow(row);
            MoveBlocksDown(row);
        }
    }
}

bool Board::IsRowFull(int row) const
{
    for (int col = 0; col < boardWidth; ++col)
    {
        if (boardVec[row][col] == nullptr)
            return false;
    }
    return true;
}

void Board::RemoveRow(int row)
{
    for (int col = 0; col < boardWidth; ++col)
    {
        GET_SINGLE(EventManager)->DeleteObject(boardVec[row][col]);
        boardVec[row][col] = nullptr;
    }

    GET_SINGLE(ResourceManager)->Play(L"BlockBreak");

    if (++skillCnt == canSkillCnt)
    {
        skillCnt = 0;
        GET_SINGLE(PlayerManager)->AddStrikerSkillCount();
    }
}

void Board::MoveBlocksDown(int row)
{
    for (int r = row; r > 0; --r)
    {
        for (int col = 0; col < boardWidth; ++col)
        {
            boardVec[r][col] = boardVec[r - 1][col];
            if (boardVec[r][col])
            {
                Vec2 pos = boardVec[r][col]->GetPos();
                pos.y += BLOCK_SIZE; // 한 칸 아래로 이동
                boardVec[r][col]->SetPos(pos);
            }
        }
    }

    // 맨 윗줄 초기화
    for (int col = 0; col < boardWidth; ++col)
        boardVec[0][col] = nullptr;
}

#pragma region ClampCheck

bool Board::CheckFloor(const std::vector<Block*>& blocks) const
{
    // 이거 이상한데
    float boardFloor = GetPos().y + (boardHeight / 2 * BLOCK_SIZE); // 보드의 시작점(Screen Space 기준)

    for (const Block* block : blocks)
    {
        if ((block->GetPos().y + BLOCK_SIZE / 2) == boardFloor)
            return true;

        if (ThereIsBlock(block, 0, 1)) return true;
    }
    return false;
}

bool Board::CheckClampRotat(Block_Parent* blockParent)
{
    for (const Block* block : blockParent->GetBlocks())
    {
        float x = block->GetPos().x;
        if (x - BLOCK_SIZE / 2 < GetBoardOrigin().x ||
            ThereIsBlock(block))
        {
            for (const Block* block : blockParent->GetBlocks())
            {
                if (ThereIsBlock(block, 1) || ThereIsBlock(block))
                {
                    cout << " 취소 " << endl;
                    return false; // 도는거 취소
                }
            }
            cout << " MoveSide " << endl;
            currentBlock->MoveSide(false);
        }
        else if (x + BLOCK_SIZE / 2 > GetBoardOrigin().x + boardWidth * BLOCK_SIZE ||
            ThereIsBlock(block))
        {
            for (const Block* block : blockParent->GetBlocks())
            {
                if (ThereIsBlock(block, -1) || ThereIsBlock(block))
                {
                    cout << " 취소 " << endl;
                    return false; // 도는거 취소
                }
            }
            cout << " MoveSide " << endl;
            currentBlock->MoveSide(true);
        }
    }

    return true;
}

bool Board::CheckClampLeft(const std::vector<Block*>& blocks) const
{
    float boardLeftOrigin = GetBoardOrigin().x; // 보드의 시작점(Screen Space 기준)

    for (const Block* block : blocks)
    {
        float x = block->GetPos().x;
        if (x - BLOCK_SIZE / 2 < boardLeftOrigin)
            return true;

        if (ThereIsBlock(block))
            return true;
    }
    return false;
}

bool Board::CheckClampRight(const std::vector<Block*>& blocks) const
{
    float boardRightOrigin = GetBoardOrigin().x + boardWidth * BLOCK_SIZE;

    for (const Block* block : blocks)
    {
        float x = block->GetPos().x;
        if (x + BLOCK_SIZE / 2 > boardRightOrigin)
            return true;

        if (ThereIsBlock(block)) return true;
    }
    return false;
}

#pragma endregion

bool Board::ThereIsBlock(const Block* block, int X, int Y) const
{
    Vec2 boardOrigin = GetBoardOrigin();
    // 보드 기준으로 계산한 위치
    float x = block->GetPos().x - boardOrigin.x;
    float y = block->GetPos().y - boardOrigin.y;

    int row = y / BLOCK_SIZE + Y;
    int col = x / BLOCK_SIZE + X;

    if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth)
    {
        if (boardVec[row][col] != nullptr)
            return true;
    }
    return false;
}

Vec2 Board::GetBoardOrigin() const
{
    return Vec2(
        (SCREEN_WIDTH - boardWidth * BLOCK_SIZE) / 2,  // 보드가 화면의 가운데 정렬된 경우
        (SCREEN_HEIGHT - boardHeight * BLOCK_SIZE) / 2
    );
}

void Board::CreateBlock()
{
    if (nextBlock == BLOCK_TYPE::NONE)
        nextBlock = (BLOCK_TYPE)(rand() % 7);

    Block_Parent* block = nullptr;
    switch (nextBlock)
    {
    case BLOCK_TYPE::BLOCK_I:
        block = new Block_I;
        break;
    case BLOCK_TYPE::BLOCK_J:
        block = new Block_J;
        break;
    case BLOCK_TYPE::BLOCK_L:
        block = new Block_L;
        break;
    case BLOCK_TYPE::BLOCK_O:
        block = new Block_O;
        break;
    case BLOCK_TYPE::BLOCK_S:
        block = new Block_S;
        break;
    case BLOCK_TYPE::BLOCK_Z:
        block = new Block_Z;
        break;
    case BLOCK_TYPE::BLOCK_T:
        block = new Block_T;
        break;
    }

    // 보드의 시작점 좌표
    float boardStartY = GetPos().y - (boardHeight * BLOCK_SIZE) / 2;

    float blockStartX = GetPos().x - BLOCK_SIZE * 2;
    float blockStartY = boardStartY + BLOCK_SIZE - 20;

    block->SetPos({ blockStartX, blockStartY - BLOCK_SIZE / 2 });
    currentBlock = block;
    block->SetName(L"Block");
    GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);

    // 다음 블럭 지정
    nextBlock = (BLOCK_TYPE)(rand() % 7);
    switch (nextBlock)
    {
    case BLOCK_TYPE::BLOCK_I:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockI", L"Texture\\Complete version\\Skyblue.bmp");
        break;
    case BLOCK_TYPE::BLOCK_J:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockJ", L"Texture\\Complete version\\Bule.bmp");
        break;
    case BLOCK_TYPE::BLOCK_L:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockL", L"Texture\\Complete version\\Orange.bmp");
        break;
    case BLOCK_TYPE::BLOCK_O:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockO", L"Texture\\Complete version\\Yellow.bmp");
        break;
    case BLOCK_TYPE::BLOCK_S:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockS", L"Texture\\Complete version\\Red.bmp");
        break;
    case BLOCK_TYPE::BLOCK_Z:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockZ", L"Texture\\Complete version\\Green.bmp");
        break;
    case BLOCK_TYPE::BLOCK_T:
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockT", L"Texture\\Complete version\\Purple.bmp");
        break;
    }
    block->SetBlockPosition();
}
