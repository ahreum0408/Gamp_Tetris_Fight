#pragma once
#include "Block_Parent.h"
#include "Block.h"
class Block_T :
    public Block_Parent
{
public:
    Block_T();
    ~Block_T();
    void Update() override;
    void Render(HDC _hdc) override;

    void Rotate() override;
    void MoveDown() override;
    void MoveSide(bool isLeft) override;

    // override
    bool CheckCollision(const std::vector<Vec2>& positions) override;
    const std::vector<Block*>& GetBlocks() override;
    void SetBlockPosition() override;

    void SetIsDefence(bool isDefence) override;
    bool GetIsDefence() override;
public:
    void SetDir(Vec2 _dir)
    {
        m_vDir = _dir;
        m_vDir.Normalize();
    }
public:
    virtual void EnterCollision(Collider* _other);
    virtual void StayCollision(Collider* _other);
    virtual void ExitCollision(Collider* _other);
private:
    // Block Spawn
    int blockNum;
    wstring texturePath = L"Texture\\PurpleBlock.bmp";

    vector<Block*> blockVec;
    Vec2 m_vDir;

    int rotationIndex; // 현재 회전 상태를 나타내는 인덱스
    int Rotation[4][3][3] =
    {
        {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        },

        {
            {0, 1, 0},
            {0, 1, 1},
            {0, 1, 0}
        },

        {
            {0, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
        },

        {
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    };
};

