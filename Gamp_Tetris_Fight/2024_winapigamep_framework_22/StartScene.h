#pragma once
#include "Scene.h"
#include "GameRule.h"
#include "Title.h"
class StartScene :
    public Scene
{
    virtual void Init() override;
    virtual void Update() override;
    virtual void Release() override;
public:
    bool isGameRuleOn = false;
private:
    Title* title;
    GameRule* PopUp;
};

