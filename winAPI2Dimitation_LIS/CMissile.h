#pragma once
class CMissile : public CGameObject
{
private:
	double mSpeed = 400;
	Vec2 mScale = Vec2(30,30);
public:
	CMissile();
	virtual CMissile* clone();
	~CMissile();
	virtual void update();
	virtual void render(HDC& hDC);

	virtual void onCollisionEnter(CCollider* other);
};

