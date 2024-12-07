#include "pch.h"
#include "IdleState.h"
#include "JumpState.h"
#include "FallState.h"

void IdleState::Enter(Defender* player) {
    player->PlayIdleAnimation();
}

void IdleState::Update(Defender* player) {
    if (player->IsJumpKeyPressed()) {
        player->GetStateMachine()->ChangeState(new JumpState());
    }
    if (player->IsFalling()) {
        player->GetStateMachine()->ChangeState(new FallState());
    }
    //if (!player->IsGrounded()) {
    //    player->GetStateMachine()->ChangeState(new FallState());
    //}
}

void IdleState::Exit(Defender* player) {
}