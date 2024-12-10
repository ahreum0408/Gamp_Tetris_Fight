#pragma once
#include "Defender.h"
#include "Striker.h"

class PlayerManager
{
    DECLARE_SINGLE(PlayerManager);
public:
    void SetStriker(Striker* striker) { _striker = striker; }
    void SetDefender(Defender* defender) { _defender = defender; }

    Striker* GetStriker() { return _striker; }
    Defender* GetDefender() { return _defender; }
    void ShakeCamera() {
        _striker->ShakeCamera();
    }
    void AddStrikerSkillCount() {
        _striker->PlusSkillCount();
    }
    bool StrikerUseSkill() {
        return _striker->UseSkill();
    }
    int GetSkillCount() { return _striker->GetSkillCount(); }
    void SetDefenerWiner(bool isWin) {
        _isDefenderWiner = isWin;
    }
    bool GetWiner() {
        return _isDefenderWiner;
    }

    void DefenderDieCheck(Block* block)
    {
        //_defender->DieCheck(block);
    }
private:
    Striker* _striker;
    Defender* _defender;
    bool _isDefenderWiner = false;
};