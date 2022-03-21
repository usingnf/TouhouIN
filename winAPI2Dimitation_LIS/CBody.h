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

	virtual CMissile* createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type);
};

