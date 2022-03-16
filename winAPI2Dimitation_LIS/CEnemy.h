#pragma once
class CEnemy : public CGameObject
{
private:
	double maxSpeed;
	double accSpeed = 0;
	Vec2 destPos = Vec2(0, 0);
public:
	CEnemy();
	virtual CEnemy* clone();
	~CEnemy();
	virtual void update();
	virtual void render(HDC& hDC);

	void setMaxSpeed(double speed);
	void setDestPos(Vec2 pos);
	void accMove(double startSpeed, double accSpeed);

	void onCollisionEnter(CCollider* other);
	void onCollisionStay(CCollider* other);
	void onCollisionExit(CCollider* other);
};

