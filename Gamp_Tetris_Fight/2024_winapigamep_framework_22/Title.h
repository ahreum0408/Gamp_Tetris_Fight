#pragma once
#include "Object.h"
#include "Texture.h"
class Title :
    public Object
{
public:
	Title();
	~Title();

	void Update() override;
	void Render(HDC _hdc) override;
public:
	int curIndex;
	bool isGameRuleOn;
private:
	int index = 0;

	Texture* m_pTex;
	Texture* startTextTex;
	Texture* gameruleTextTex;
	Texture* exitTextTex;
};

