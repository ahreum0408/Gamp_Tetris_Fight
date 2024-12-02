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

private:
	Texture* m_pTex;
	Texture* startTextTex;
	Texture* gameruleTextTex;
	Texture* exitTextTex;

	int index;
	int curIndex;

	POINT mousePos;
	RECT startRect;
	RECT gameruleRect;
	RECT exitRect;

	// Game Rule
	bool isGameRuleOn = false;
	Texture* gameRuleTex;
};

