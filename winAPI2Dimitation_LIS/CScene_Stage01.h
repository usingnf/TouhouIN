#pragma once
#include "CScene.h"
class CScene_Stage01 : public CScene
{
private:
	int level = 0;
public:
	CScene_Stage01();
	~CScene_Stage01();
	virtual void update();
	virtual void render(HDC& hDC);
	virtual void Enter();
	virtual void Exit();

	int getLevel();
	void setLevel(int level);
};

