#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "InputManager.h"
#include "TimeManager.h"
#include<random>

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::LateUpdate()
{
	// 흔들기를 진행 중이라면 타이머를 업데이트
	if (m_shakeCount > 0)
	{
		time += fDT; // DeltaTime을 이용해 시간 누적

		if (time >= 0.05f) // 0.05초 간격으로 흔들기
		{
			ShakeCamera();
			time = 0.0f; // 타이머 초기화
			m_shakeCount--; // 흔들림 횟수 감소
		}
	}
}

void CameraComponent::Render(HDC _hdc)
{
}

void CameraComponent::ShakeCamera()
{
	Vec2 pos = GET_SINGLE(Camera)->GetCameraPos();

	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> distX(-3, 3);
	std::uniform_int_distribution<int> distY(-3, 3);

	pos.x += distX(mt);
	pos.y += distY(mt);

	GET_SINGLE(Camera)->SetCameraPos(pos);
}
void CameraComponent::StartShake()
{
	m_shakeCount = 5; // 흔들기 횟수 5번으로 설정
}
