#include "pch.h"
#include "CameraComponent.h"
#include "Camera.h"
#include "InputManager.h"
#include "TimeManager.h"
#include<random>

CameraComponent::CameraComponent()
{
	m_defaultPos = GET_SINGLE(Camera)->GetCameraPos();
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::LateUpdate()
{
	// ���⸦ ���� ���̶�� Ÿ�̸Ӹ� ������Ʈ
	if (m_shakeCount > 0)
	{
		time += fDT; // DeltaTime�� �̿��� �ð� ����

		if (time >= 0.05f) // 0.05�� �������� ����
		{
			if (m_shakeCount == 1) {
				GET_SINGLE(Camera)->SetCameraPos(m_defaultPos);
			}
			else {
				ShakeCamera();
			}
			time = 0.0f; // Ÿ�̸� �ʱ�ȭ
			m_shakeCount--; // ��鸲 Ƚ�� ����
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
	m_shakeCount = 5 + 1; // ���� Ƚ�� 5������ ����
}
