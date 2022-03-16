#pragma once
class CPlayer : public CGameObject
{
private:
	Vec2 pScale = Vec2(50, 50);
	double pSpeed = 300;
public:
	CPlayer();
	virtual CPlayer* clone();
	~CPlayer();

	virtual void update();
	virtual void render(HDC& hDC);
};

