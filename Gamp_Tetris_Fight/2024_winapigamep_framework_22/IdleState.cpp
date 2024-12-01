#include "pch.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"

void IdleState::Enter(Defender* player) {
    std::cout << "Entering Idle State" << std::endl;
}

void IdleState::Update(Defender* player) {
    if (player->IsJumpKeyPressed()) {
        player->GetStateMachine()->ChangeState(new JumpState());
    }
    if (!player->IsGrounded()) {
        player->GetStateMachine()->ChangeState(new FallState());
    }
}

void IdleState::Exit(Defender* player) {
    std::cout << "Exiting Idle State" << std::endl;
}