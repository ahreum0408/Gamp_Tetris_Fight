#pragma once
#include "Object.h"
#include "Texture.h"
class GameRule :
    public Object
{
public:
    GameRule();
    ~GameRule();

    void Update() override;
    void Render(HDC _hdc) override;
public:
	bool RulePopUp = false;
private:
	Texture* m_pTex;
};

