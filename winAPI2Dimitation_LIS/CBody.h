#pragma once
class CBody : public CGameObject
{
private:
	Vec2 pScale = Vec2(50, 50);
	double missileTimer = 0;
public:
	CBody();
	virtual CBody* clone();
	~CBody();

	virtual void update();
	virtual void render(HDC& hDC);
};

