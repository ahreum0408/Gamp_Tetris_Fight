#include "pch.h"
#include "DefenceBlock.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Defender.h"
#include "TimeManager.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Camera.h"
#include "EventManager.h"

DefenceBlock::DefenceBlock(Defender* defender) : m_defender(defender), m_lifeTime(0.3f)
{
    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"DefenderBlock", L"Texture\\defend-block.bmp");
    AddComponent<Collider>();
    Collider* collider = GetComponent<Collider>();
    collider->SetSize({ 35,10 });
    collider->SetOffSetPos({ 2,0 });
    SetName(L"DefendBlock");
    //cout << "block : ";
    //cout << collider->GetOwner() << endl;
    collider->SetIsTrigger(false);
}

DefenceBlock::~DefenceBlock()
{
}

void DefenceBlock::Update()
{
    m_lifeTime -= fDT;

    // ���� �ð��� 0 ���ϰ� �Ǹ� ��� ����
    if (m_lifeTime <= 0.f) {
        GET_SINGLE(EventManager)->DeleteObject(this);
        return;
    }

    // Defender�� ��ġ ������� ��� ��ġ ���� (�ʿ��ϸ� ����)
    if (m_defender) {
        Vec2 defenderPos = m_defender->GetPos();
        Vec2 newPos = defenderPos;
        newPos.y -= 30.f; // ���� ����
        SetPos(newPos);
    }
}

void DefenceBlock::Render(HDC _hdc)
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

void DefenceBlock::EnterCollision(Collider* _other)
{
    wstring otherName = _other->GetOwner()->GetName();

    if (otherName == L"Block") {
        // �浹�� �߻��� ��� ó��
        cout << "defence block" << endl;

        // �ʿ� �� �ٷ� ��� �ı�
        //delete(this);
    }
}
