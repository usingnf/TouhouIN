#pragma once
class CMissile2 : public CGameObject
{
public:
	CMissile2();
	virtual CMissile2* clone();
	~CMissile2();
	virtual void update();
	virtual void render(HDC& hDC);
};

