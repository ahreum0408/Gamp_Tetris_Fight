#pragma once
#include "Scene.h"
class StartScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Release() override;
public:
    bool isGameRuleOn = false;
};

