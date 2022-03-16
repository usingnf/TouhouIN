#pragma once
class CMissile : public CGameObject
{
private:
	double damage = 0;
public:
	CMissile();
	virtual CMissile* clone();
	~CMissile();
	virtual void update();
	virtual void render(HDC& hDC);

	void setDamage(double damage);

	virtual void onCollisionEnter(CCollider* other);
};

