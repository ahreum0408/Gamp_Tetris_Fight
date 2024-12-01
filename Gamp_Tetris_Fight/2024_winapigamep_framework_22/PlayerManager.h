#pragma once
#include "Defender.h"
#include "Striker.h"

class PlayerManager
{
    DECLARE_SINGLE(PlayerManager);
public:
    void SetStriker(Striker* striker) { _striker = striker;  }
    void SetDefender(Defender* defender) { _defender = defender; }

    Striker* GetStriker() { return _striker;}
    Defender* GetDefender() { return _defender; }

    void AddStrikerSkillCount() {
        _striker->PlusSkillCount();
    }
private:
    Striker* _striker;
    Defender* _defender;
};

