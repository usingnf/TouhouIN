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

	virtual CMissile* createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type);
};

