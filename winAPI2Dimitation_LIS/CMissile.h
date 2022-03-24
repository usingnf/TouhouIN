#pragma once
class CMissile : public CGameObject
{
private:
	double damage = 0;
	bool isUse = true;
public:
	CMissile();
	virtual CMissile* clone();
	~CMissile();
	virtual void update();
	virtual void render();

	void setDamage(double damage);

	virtual void onCollisionEnter(CCollider* other);

	void setIsUse(bool use);
	bool getIsUse();
	void recycleMissile();
};

