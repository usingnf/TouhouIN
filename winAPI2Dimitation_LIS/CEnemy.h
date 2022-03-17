#pragma once
class CEnemy : public CGameObject
{
private:
	double maxSpeed;
	double accSpeed = 0;
public:
	CEnemy();
	virtual CEnemy* clone();
	~CEnemy();
	virtual void update();
	virtual void render(HDC& hDC);

	void setMaxSpeed(double speed);
	void setDestPos(Vec2 pos);
	void accMove(double startSpeed, double accSpeed);

	virtual void die();

	void onCollisionEnter(CCollider* other);
	void onCollisionStay(CCollider* other);
	void onCollisionExit(CCollider* other);
};

