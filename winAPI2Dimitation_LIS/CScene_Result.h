#pragma once
#include "CScene.h"

class CScene_Result : public CScene
{
private:

public:
	CScene_Result();
	~CScene_Result();
	virtual void update();
	virtual void render(HDC& hDC);
	virtual void Enter();
	virtual void Exit();
	void saveHighScore();
};

