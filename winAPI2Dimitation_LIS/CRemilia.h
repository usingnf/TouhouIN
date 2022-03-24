#pragma once
class CRemilia : public CGameObject
{
private:
	Vec2 pScale = Vec2(50, 50);
	double pSpeed = 300;
public:
	CRemilia();
	virtual CRemilia* clone();
	~CRemilia();

	virtual void update();
	virtual void render();
};

