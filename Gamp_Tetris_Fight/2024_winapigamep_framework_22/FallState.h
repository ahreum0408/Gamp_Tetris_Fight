#pragma once
#include "BaseState.h"
class FallState : public BaseState {
public:
    void Enter(Defender* player) override;
    void Update(Defender* player) override;
    void Exit(Defender* player) override;
};
