#pragma once
#include "CGameObject.h"
class CWall : public CGameObject
{
private:
	Vec2 pScale = Vec2(65, 33);
public:
	CWall();
	virtual CWall* clone();
	~CWall();
	virtual void update();
	virtual void render(HDC& hDC);
};

