#include "pch.h"
#include "JumpState.h"
#include "FallState.h"

void JumpState::Enter(Defender* player) {
    player->PlayJumpAnimation();
    player->Jump(); // 점프 실행
}

void JumpState::Update(Defender* player) {
    if (player->IsJumpKeyPressed()) {
        player->Jump();
    }
    if (player->IsFalling()) {
        player->GetStateMachine()->ChangeState(new FallState());
    }
}

void JumpState::Exit(Defender* player) {
}