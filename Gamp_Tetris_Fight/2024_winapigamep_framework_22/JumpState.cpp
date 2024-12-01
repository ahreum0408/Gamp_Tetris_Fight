#include "pch.h"
#include "JumpState.h"
#include "FallState.h"

void JumpState::Enter(Defender* player) {
    std::cout << "Entering Jump State" << std::endl;
    player->Jump(); // 점프 실행
}

void JumpState::Update(Defender* player) {
    if (player->IsFalling()) {
        player->GetStateMachine()->ChangeState(new FallState());
    }
}

void JumpState::Exit(Defender* player) {
    std::cout << "Exiting Jump State" << std::endl;
}