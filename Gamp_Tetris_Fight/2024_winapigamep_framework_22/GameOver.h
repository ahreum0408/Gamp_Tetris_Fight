#pragma once
#include "Object.h"
#include "Texture.h"
class GameOver :
    public Object
{
public:
	GameOver();
	~GameOver();

	void Update() override;
	void Render(HDC _hdc) override;
public:
	int curIndex;
private:
	int index = 0;

	Texture* m_pTex;
	Texture* retryTextTex;
	Texture* exitTextTex;
};

