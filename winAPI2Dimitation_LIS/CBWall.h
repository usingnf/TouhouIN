#pragma once
class CBWall : public CGameObject
{
private:
	Vec2 pScale = Vec2(33, 33);
	bool isBroken = false;
public:
	CBWall();
	virtual CBWall* clone();
	~CBWall();
	virtual void update();
	virtual void render(HDC& hDC);

	virtual void onCollisionEnter(CCollider* other);
	virtual void onCollisionStay(CCollider* other);
	virtual void onCollisionExit(CCollider* other);
};

