#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Collider.h"
#include "Camera.h"
#include "Velocity.h"
#include "Block_Parent.h"
#include "PlayerManager.h"
#include <format>

Block::Block(wstring path, Block_Parent* parent) :
	m_vDir(1.f, 1.f),
	m_pTex(nullptr),
	m_parent(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(std::format(L"{}Block", path), path);
	this->AddComponent<Collider>();
	this->AddComponent<Velocity>();
	m_velocity = GetComponent<Velocity>();
	m_collider = GetComponent<Collider>();
	m_collider->SetSize({ BLOCK_SIZE, BLOCK_SIZE });
	SetName(L"Block");
	m_parent = parent;
}
Block::~Block() {}

void Block::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Vec2 camerapos = GET_SINGLE(Camera)->GetCameraPos();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2 - ((int)camerapos.x))
		, (int)(vPos.y - height / 2 - ((int)camerapos.y))
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}
void Block::Update()
{
	Vec2 vPos = GetPos();

	if (m_velocity && GetIsDefence()) {
		Vec2 velocityValue = m_velocity->GetVelocity();
		// 현재 위치 갱신
		SetPos(vPos + velocityValue);
	}

	// 블럭이 화면 하단을 벗어나면 삭제
	if (vPos.y <= -100) {
		cout << "블럭삭제" << endl;
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Block::StartFireBlock() // 무한 반복이 됨 이거 끊어주는게 필요함
{
	Vec2 direction = GetRandomDirection();
	m_vDir = direction;

	if (m_velocity) {
		m_velocity->SetVelocity(m_vDir * m_blockSpeed); // BLOCK_SPEED는 속도 상수
	}
}

Vec2 Block::GetDirection(Collider* _other, const Vec2& point) {
	if (!_other) {
		return m_vDir; // Collider가 nullptr이면 기존 방향 유지
	}

	Vec2 normal = _other->GetNormal(point); // 충돌 상대에서 법선 계산
	normal.Normalize(); // 법선 벡터 정규화

	// 반사 벡터 계산
	Vec2 reflectedDir = m_vDir - normal * 2 * m_vDir.Dot(normal);
	reflectedDir.Normalize();

	// 반사 방향이 위쪽(-Y 방향)을 강제
	if (reflectedDir.y > 0) {
		reflectedDir.y = -reflectedDir.y; // 아래로 가는 경우 위쪽으로 반전
	}

	// Y축 성분이 너무 작으면 보정
	const float minY = -0.3f; // 최소 Y값 제한 (너무 평평한 반사 방지)
	if (reflectedDir.y > minY) {
		float adjustFactor = sqrt(1 - minY * minY); // X와 Y가 단위 벡터를 유지하도록 보정
		reflectedDir.x *= adjustFactor;
		reflectedDir.y = minY; // 최소 Y값으로 보정
		reflectedDir.Normalize(); // 최종 벡터 정규화
	}

	return reflectedDir; // 반사 방향 반환
}
Vec2 Block::GetRandomDirection() {
	float minAngle = -120.f * (M_PI / 180.f);
	float maxAngle = 120.f * (M_PI / 180.f);
	float randomAngle = minAngle + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxAngle - minAngle)));

	float x = cos(randomAngle);
	float y = sin(randomAngle);

	Vec2 returnVec;
	returnVec.x = x;
	returnVec.y = y;
	returnVec.Normalize();
	return returnVec;
}

void Block::EnterCollision(Collider* _other)
{
	wstring name = _other->GetOwner()->GetName();
	if (name == L"DefendBlock") {
		if (m_parent) {
			m_parent->SetIsDefence(true);
		}
	}
	else if (GetIsDefence()) {
		if (name == L"Wall" || name == L"Block") {
			GET_SINGLE(PlayerManager)->ShakeCamera();
			cout << "블럭 방향 변경" << endl;
			Vec2 newDirection = GetDirection(_other, m_collider->GetPosition());
			m_vDir = newDirection;

			if (m_velocity) {
				m_velocity->SetVelocity(m_vDir * m_blockSpeed); // BLOCK_SPEED는 속도 상수
			}
		}
	}
}
void Block::StayCollision(Collider* _other)
{
}
void Block::ExitCollision(Collider* _other)
{
}
