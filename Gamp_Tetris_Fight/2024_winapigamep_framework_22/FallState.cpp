#include "pch.h"
#include "FallState.h"
#include "IdleState.h"
#include "JumpState.h"

void FallState::Enter(Defender* player) {
    player->PlayFallAnimation();
}

void FallState::Update(Defender* player) {
    if (player->IsJumpKeyPressed()) {
        player->GetStateMachine()->ChangeState(new JumpState());
    }
    if (player->IsGrounded()) {
        player->GetStateMachine()->ChangeState(new IdleState());
    }
}

void FallState::Exit(Defender* player) {
}