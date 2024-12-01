#pragma once
#include "Defender.h"
class BaseState
{
public:
    virtual ~BaseState() = default;

    virtual void Enter(Defender* player) = 0;   // ���¿� ���� �� ȣ��
    virtual void Update(Defender* player) = 0; // �� ������ ȣ��
    virtual void Exit(Defender* player) = 0;   // ���¿��� ���� �� ȣ��
};

