#pragma once
#include "Defender.h"
#include "Striker.h"

class PlayerManager
{
    DECLARE_SINGLE(PlayerManager);
public:
    void SetStriker(Striker* striker) { _striker = striker; }

    Striker* GetStriker() { return _striker; }

    void AddStrikerSkillCount() {
        _striker->PlusSkillCount();
    }
    bool StrikerUseSkill() {
        return _striker->UseSkill();
    }	
    int GetSkillCount() { return _striker->GetSkillCount(); }
private:
    Striker* _striker;
};