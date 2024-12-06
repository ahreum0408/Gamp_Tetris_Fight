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
#include "GDISelector.h"

Board::Board() :
    boardWidth(10), boardHeight(20), isSkill(false),
    currentBlock(nullptr), nextBlock(BLOCK_TYPE::NONE),
    m_pTex(nullptr), nextBlockTex(nullptr), myFont(nullptr)
{
    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Board", L"Texture\\gamp-background.bmp");
    boardVec.resize(boardHeight, std::vector<Block*>(boardWidth));
    this->SetName(L"Block");

    AddFontResource(L"Font\\Galmuri11.ttf");
}

Board::~Board() 
{
    ::DeleteObject(myFont);
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
        boardOrigin.y + 80.f };
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
        myFont = ::CreateFont(
              20                       // ����
            , 0                        // �� 0�̸� ���̿� ���
            , 0                        // ���� ��ü ����
            , 0                        // ���ؼ��� ������ ����
            , 0                  // ��Ʈ�� �β�
            , 0                        // ���Ÿ�
            , 0                        // ����
            , 0                        // ��Ҽ�
            , DEFAULT_CHARSET          // �ɸ��� ��
            , 0                        // ���е�
            , 0                        // ���е�
            , 0                        // ���е�
            , 0                        // ���е�
            , L"Galmuri11"        // �۲��̸�
        );
        GDISelector font(_hdc, myFont);
        SetTextColor(_hdc, RGB(255, 255, 255));

        // ��ų
        wstring wstr = L"���ݼ� ��ų �� : " + std::to_wstring(GET_SINGLE(PlayerManager)->GetSkillCount());
        TextOut(_hdc, 120, 60, wstr.c_str(), wstr.length());

        // ���ݼ�
        TextOut(_hdc, GetPos().x + 110, 180, L"[���ݼ�]", wcslen(L"[���ݼ�]"));
        TextOut(_hdc, GetPos().x + 110, 215, L"�� ȸ�� : W", wcslen(L"�� ȸ�� : W"));
        TextOut(_hdc, GetPos().x + 110, 250, L"�¿��̵� : A, D", wcslen(L"�¿��̵� : A, D"));
        TextOut(_hdc, GetPos().x + 110, 285, L"��ų : LShift", wcslen(L"��ų : LShift"));
        // �����
        TextOut(_hdc, GetPos().x + 110, 350, L"[�����]", wcslen(L"[�����]"));
        TextOut(_hdc, GetPos().x + 110, 385, L"�¿��̵� : ������ ���� ȭ��ǥ", wcslen(L"�¿��̵� : ������ ���� ȭ��ǥ"));
        TextOut(_hdc, GetPos().x + 110, 420, L"���� : ���� ȭ��ǥ", wcslen(L"���� : ���� ȭ��ǥ"));
        TextOut(_hdc, GetPos().x + 110, 455, L"�е� : Space", wcslen(L"�е� : Space"));
    }
}

void Board::Update()
{
    if (isGameOver) return;

#pragma region BlockMove
    if (currentBlock)
    {
        if (!isSkill)
        {
            // W Ű�� ���� ��� ȸ��
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

            // A, D Ű�� ���� ��� �̵�
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

        // LSHIFT Ű�� ���� ��� �� ���
        if (GET_KEYDOWN(KEY_TYPE::LSHIFT))
        {
            if (GET_SINGLE(PlayerManager)->StrikerUseSkill()) {
                isSkill = true;
                currentMoveDownDelay = 0;
            }
            else {
                cout << "you can't use skill" << endl;
            }
        }

        // Block Down
        if (moveDownTimer >= currentMoveDownDelay && currentBlock)
        {
            if (CheckFloor(currentBlock->GetBlocks()))
            {
                currentMoveDownDelay = moveDownDelay;

                // 1. �� �װ�
                BuildBlock(currentBlock);
                if (isGameOver) return;
                isSkill = false;
                // 2. �� á���� �˻�
                ClearFullRows();
                // 3. ���ο� �� ����
                currentBlock = nullptr;
                CreateBlock();
            }
            if (!currentBlock->GetIsDefence()) {
                currentBlock->MoveDown(); // �̰� �ٴڿ� �����°�
            }
            else {
                //GET_SINGLE(EventManager)->DeleteObject(currentBlock);
                currentBlock = nullptr; // ��� ���ص� �Ǵµ� �̰� �����ָ� �޸𸮰� ���ž�
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
        // ���� �������� ����� ��ġ
        float x = block->GetPos().x - boardOrigin.x;
        float y = block->GetPos().y - boardOrigin.y;

        int row = y / BLOCK_SIZE;
        int col = x / BLOCK_SIZE;

        if (row == boardHeight - endRow)
        {
            isGameOver = true;
            return;
        }

        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth)
        {
            if (boardVec[row][col] == nullptr)
                boardVec[row][col] = block;
        }
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

    if (++skillCnt == canSkillCnt)
        GET_SINGLE(PlayerManager)->AddStrikerSkillCount();
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
                pos.y += BLOCK_SIZE; // �� ĭ �Ʒ��� �̵�
                boardVec[r][col]->SetPos(pos);
            }
        }
    }

    // �� ���� �ʱ�ȭ
    for (int col = 0; col < boardWidth; ++col)
        boardVec[0][col] = nullptr;
}

#pragma region ClampCheck

bool Board::CheckFloor(const std::vector<Block*>& blocks) const
{
    float boardFloor = GetPos().y + GetSize().y / 2; // ������ ������(Screen Space ����)

    for (const Block* block : blocks)
    {
        if ((block->GetPos().y + BLOCK_SIZE / 2) == boardFloor)
            return true;

        if (ThereIsBlock(block, 0, 1)) return true;
    }
    return false;
}

bool Board::CheckClampRotat(Block_Parent* block)
{
    for (const Block* block : block->GetBlocks())
    {
        float x = block->GetPos().x;
        if (x - BLOCK_SIZE / 2 < GetBoardOrigin().x ||
            ThereIsBlock(block))
        {
            if (ThereIsBlock(block, 1))
                return false; // ���°� ���
            else
                currentBlock->MoveSide(false);
        }
        else if (x + BLOCK_SIZE / 2 > GetBoardOrigin().x + boardWidth * BLOCK_SIZE ||
            ThereIsBlock(block))
        {
            if (ThereIsBlock(block, -1))
                return false; // ���°� ���
            else
                currentBlock->MoveSide(true);
        }
    }

    return true;
}

bool Board::CheckClampLeft(const std::vector<Block*>& blocks) const
{
    float boardLeftOrigin = GetBoardOrigin().x; // ������ ������(Screen Space ����)

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
    // ���� �������� ����� ��ġ
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
        (SCREEN_WIDTH - boardWidth * BLOCK_SIZE) / 2,  // ���尡 ȭ���� ��� ���ĵ� ���
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

    // ������ ������ ��ǥ
    float boardStartY = GetPos().y - (boardHeight * BLOCK_SIZE) / 2;

    // ����� ������ -1��° �ٿ� ��ġ
    float blockStartX = GetPos().x - BLOCK_SIZE * 2;
    float blockStartY = boardStartY + BLOCK_SIZE * 4;

    block->SetPos({ blockStartX, blockStartY - BLOCK_SIZE / 2 });
    currentBlock = block;
    block->SetName(L"Block");
    GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);

    // ���� �� ����
    nextBlock = (BLOCK_TYPE)(rand() % 7);
    switch (nextBlock)
    {
    case BLOCK_TYPE::BLOCK_I:
        //cout << "I" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockI", L"Texture\\Complete version\\Skyblue.bmp");
        break;
    case BLOCK_TYPE::BLOCK_J:
        //cout << "J" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockJ", L"Texture\\Complete version\\Bule.bmp");
        break;
    case BLOCK_TYPE::BLOCK_L:
        //cout << "L" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockL", L"Texture\\Complete version\\Orange.bmp");
        break;
    case BLOCK_TYPE::BLOCK_O:
        //cout << "O" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockO", L"Texture\\Complete version\\Yellow.bmp");
        break;
    case BLOCK_TYPE::BLOCK_S:
        //cout << "S" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockS", L"Texture\\Complete version\\Red.bmp");
        break;
    case BLOCK_TYPE::BLOCK_Z:
        //cout << "Z" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockZ", L"Texture\\Complete version\\Green.bmp");
        break;
    case BLOCK_TYPE::BLOCK_T:
        //cout << "T" << endl;
        nextBlockTex = GET_SINGLE(ResourceManager)->
            TextureLoad(L"NextBlockT", L"Texture\\Complete version\\Purple.bmp");
        break;
    }
    block->SetBlockPosition();
}
