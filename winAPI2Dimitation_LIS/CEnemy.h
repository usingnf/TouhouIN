#pragma once
class CEnemy : public CGameObject
{
private:
	double maxSpeed;
	double accSpeed = 0;
	int ai = 0;
	int powerItem = 0;
	int lifeItem = 0;
	int spellItem = 0;
	int scoreItem = 0;
public:
	CEnemy();
	virtual CEnemy* clone();
	~CEnemy();
	virtual void update();
	virtual void render(HDC& hDC);

	void setMaxSpeed(double speed);
	void setDestPos(Vec2 pos);
	void accMove(double startSpeed, double accSpeed);

	void setItemDrop(Group_Item type, int count);

	virtual void die();

	void onCollisionEnter(CCollider* other);
	void onCollisionStay(CCollider* other);
	void onCollisionExit(CCollider* other);
};

