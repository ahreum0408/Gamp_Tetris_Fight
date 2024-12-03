#pragma once
#include "Scene.h"
class GameOverScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Release() override;
};

