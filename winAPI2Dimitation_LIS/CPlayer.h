#pragma once

class CSpell;
class CPlayer : public CGameObject
{
private:
	Vec2 pScale = Vec2(50, 50);
	double pSpeed = 300;
	
public:
	static bool isSpell;
	CPlayer();
	virtual CPlayer* clone();
	virtual ~CPlayer();

	virtual void update();
	virtual void render();

	virtual void die();
};

