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
		// ���� ��ġ ����
		SetPos(vPos + velocityValue);
	}

	// ���� ȭ�� �ϴ��� ����� ����
	if (vPos.y <= -100) {
		cout << "������" << endl;
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Block::StartFireBlock() // ���� �ݺ��� �� �̰� �����ִ°� �ʿ���
{
	Vec2 direction = GetRandomDirection();
	m_vDir = direction;

	if (m_velocity) {
		m_velocity->SetVelocity(m_vDir * m_blockSpeed); // BLOCK_SPEED�� �ӵ� ���
	}
}

Vec2 Block::GetDirection(Collider* _other, const Vec2& point) {
	if (!_other) {
		return m_vDir; // Collider�� nullptr�̸� ���� ���� ����
	}

	Vec2 normal = _other->GetNormal(point); // �浹 ��뿡�� ���� ���
	normal.Normalize(); // ���� ���� ����ȭ

	// �ݻ� ���� ���
	Vec2 reflectedDir = m_vDir - normal * 2 * m_vDir.Dot(normal);
	reflectedDir.Normalize();

	// �ݻ� ������ ����(-Y ����)�� ����
	if (reflectedDir.y > 0) {
		reflectedDir.y = -reflectedDir.y; // �Ʒ��� ���� ��� �������� ����
	}

	// Y�� ������ �ʹ� ������ ����
	const float minY = -0.3f; // �ּ� Y�� ���� (�ʹ� ������ �ݻ� ����)
	if (reflectedDir.y > minY) {
		float adjustFactor = sqrt(1 - minY * minY); // X�� Y�� ���� ���͸� �����ϵ��� ����
		reflectedDir.x *= adjustFactor;
		reflectedDir.y = minY; // �ּ� Y������ ����
		reflectedDir.Normalize(); // ���� ���� ����ȭ
	}

	return reflectedDir; // �ݻ� ���� ��ȯ
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
			cout << "�� ���� ����" << endl;
			Vec2 newDirection = GetDirection(_other, m_collider->GetPosition());
			m_vDir = newDirection;

			if (m_velocity) {
				m_velocity->SetVelocity(m_vDir * m_blockSpeed); // BLOCK_SPEED�� �ӵ� ���
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
