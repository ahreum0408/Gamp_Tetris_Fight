#pragma once

#include "BaseState.h"
class JumpState : public BaseState {
public:
    void Enter(Defender* player) override;
    void Update(Defender* player) override;
    void Exit(Defender* player) override;
};