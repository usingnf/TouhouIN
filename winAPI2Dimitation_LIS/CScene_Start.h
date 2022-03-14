#pragma once
#include "CScene.h"
class CScene_Start : public CScene
{

public:
	CScene_Start();
	~CScene_Start();
	virtual void update();
	virtual void render(HDC& hDC);
	virtual void Enter();
	virtual void Exit();
};


