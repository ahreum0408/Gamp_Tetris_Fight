#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "InputManager.h"
#include<random>

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::LateUpdate()
{
}

void CameraComponent::Render(HDC _hdc)
{
}

void CameraComponent::ShakeCamera()
{
	Vec2 pos = GET_SINGLE(Camera)->GetCameraPos();

	//pos.x = std::clamp(pos.x, (float)SCREEN_WIDTH / 2, 3024.0f - SCREEN_WIDTH / 2);
	//pos.y = std::clamp(pos.y, (float)SCREEN_HEIGHT / 2, 2064.0f - SCREEN_HEIGHT / 2);

	std::random_device rd;
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> distX(-3, 3);	
	std::uniform_int_distribution<int> distY(-3, 3);

	pos.x += distX(mt);
	pos.y += distY(mt);

	GET_SINGLE(Camera)->SetCameraPos(pos);
}
