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

    void BuildBlock(Block_Parent* blockParent); // ��� ����
    void ClearFullRows(); // ���� �� �� ����
    bool IsRowFull(int row) const; // Ư�� ���� ���� á���� Ȯ��
    void RemoveRow(int row); // Ư�� �� ����
    void MoveBlocksDown(int row); // �� ����� �Ʒ��� �̵�
    
    void CreateBlock();
    void SetGhostBlock();

    bool CheckFloor(const std::vector<Block*>& blocks) const; // ������ �� ������ �浹
    
    bool CheckClampRotat(Block_Parent* block); // �� �� üũ
    bool CheckClampLeft(const std::vector<Block*>& blocks) const; // �翷 �浹
    bool CheckClampRight(const std::vector<Block*>& blocks) const; // �翷 �浹
    
    bool ThereIsBlock(const Block* block, int X = 0, int Y = 0) const;
    Vec2 GetBoardOrigin() const;
private:
    const int boardWidth = 10; // ���� ���� ũ��
    const int boardHeight = 20; // ���� ���� ũ��

    // Block Down
    int moveDownTimer = 0;
    int currentMoveDownDelay = 200;
    const int moveDownDelay = 200;

    // Skill
    bool isSkill = false;
    int skillCnt = 0;
    int canSkillCnt = 4;

    Texture* m_pTex;

    // 2D �迭�� ���� ���� ����
    vector<vector<Block*>> boardVec;

    Block_Parent* currentBlock = nullptr; // ���� �����̴� ���
    Block_Ghost* ghostBlock = nullptr; // �ؿ� ������ ���� ���̴� ���
    BLOCK_TYPE nextBlock; // ���� ���
    Texture* nextBlockTex;

    // GameOver
    bool isGameOver = false;
    int endRow = 18;
};