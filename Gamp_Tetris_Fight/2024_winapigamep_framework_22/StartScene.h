#pragma once
#include "Scene.h"
class StartScene :
    public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Release() override;
public:
    bool isGameRuleOn = false;
};

