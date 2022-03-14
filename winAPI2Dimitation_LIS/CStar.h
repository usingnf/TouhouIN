#pragma once
class CStar : public CGameObject
{
private:
	Vec2 pScale = Vec2(33, 33);
	bool isMove = false;
	int wallCount = 0;
public:
	CStar();
	virtual CStar* clone();
	~CStar();
	virtual void update();
	virtual void render(HDC& hDC);

	virtual void onCollisionEnter(CCollider* other);
	virtual void onCollisionStay(CCollider* other);
	virtual void onCollisionExit(CCollider* other);
};

