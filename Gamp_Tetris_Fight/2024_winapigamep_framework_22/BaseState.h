#pragma once
#include "Defender.h"
class BaseState
{
public:
    virtual ~BaseState() = default;

    virtual void Enter(Defender* player) abstract;   // ���¿� ���� �� ȣ��
    virtual void Update(Defender* player) abstract; // �� ������ ȣ��
    virtual void Exit(Defender* player) abstract;   // ���¿��� ���� �� ȣ��
};

