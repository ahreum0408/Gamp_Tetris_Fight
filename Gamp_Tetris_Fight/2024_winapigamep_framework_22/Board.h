#pragma once
#include "Object.h"
#include "Block_Parent.h"
#include "Block_Ghost.h"
#include "Block.h"
class Board :
    public Object
{
public:
    Board();
    ~Board();

    void Update() override;
    void Render(HDC _hdc) override;

    void BuildBlock(Block_Parent* blockParent); // 블록 고정
    void ClearFullRows(); // 가득 찬 줄 삭제
    bool IsRowFull(int row) const; // 특정 줄이 가득 찼는지 확인
    void RemoveRow(int row); // 특정 줄 제거
    void MoveBlocksDown(int row); // 위 블록을 아래로 이동
    
    void CreateBlock();
    void SetGhostBlock();

    bool CheckFloor(const std::vector<Block*>& blocks) const; // 고정할 지 않할지 충돌
    
    bool CheckClampRotat(Block_Parent* block); // 돌 때 체크
    bool CheckClampLeft(const std::vector<Block*>& blocks) const; // 양옆 충돌
    bool CheckClampRight(const std::vector<Block*>& blocks) const; // 양옆 충돌
    
    bool ThereIsBlock(const Block* block, int X = 0, int Y = 0) const;
    Vec2 GetBoardOrigin() const;
private:
    const int boardWidth = 10; // 보드 가로 크기
    const int boardHeight = 20; // 보드 세로 크기

    // Block Down
    int moveDownTimer = 0;
    int currentMoveDownDelay = 200;
    const int moveDownDelay = 200;

    // Skill
    bool isSkill = false;
    int skillCnt = 0;
    int canSkillCnt = 4;

    Texture* m_pTex;

    // 2D 배열로 보드 상태 관리
    vector<vector<Block*>> boardVec;

    Block_Parent* currentBlock = nullptr; // 현재 움직이는 블록
    Block_Ghost* ghostBlock = nullptr; // 밑에 놓여질 곳이 보이는 블록
    BLOCK_TYPE nextBlock; // 다음 블록
    Texture* nextBlockTex;

    // GameOver
    bool isGameOver = false;
    int endRow = 18;
};