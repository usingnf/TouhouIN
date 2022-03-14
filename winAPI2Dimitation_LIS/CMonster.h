#pragma once
class CMonster : public CGameObject
{
private:
	Vec2 mScale = Vec2(50,50);
	double mSpeed = 100;
	int wallCount = 0;
public:
	CMonster();
	virtual CMonster* clone();
	~CMonster();
	virtual void update();
	virtual void render(HDC& hDC);

	void onCollisionEnter(CCollider* other);
	void onCollisionStay(CCollider* other);
	void onCollisionExit(CCollider* other);
};

