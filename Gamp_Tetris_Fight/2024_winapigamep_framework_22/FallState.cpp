#include "pch.h"
#include "FallState.h"
#include "IdleState.h"


void FallState::Enter(Defender* player) {
    std::cout << "Entering Fall State" << std::endl;
}

void FallState::Update(Defender* player) {
    if (player->IsGrounded()) {
        player->GetStateMachine()->ChangeState(new IdleState());
    }
}

void FallState::Exit(Defender* player) {
    std::cout << "Exiting Fall State" << std::endl;
}