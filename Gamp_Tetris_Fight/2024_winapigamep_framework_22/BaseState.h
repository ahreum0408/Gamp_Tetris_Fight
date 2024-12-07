#pragma once
#include "Defender.h"
class BaseState
{
public:
    virtual ~BaseState() = default;

    virtual void Enter(Defender* player) abstract;   // 상태에 들어올 때 호출
    virtual void Update(Defender* player) abstract; // 매 프레임 호출
    virtual void Exit(Defender* player) abstract;   // 상태에서 나갈 때 호출
};

