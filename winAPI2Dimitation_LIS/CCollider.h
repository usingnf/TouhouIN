#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;
private:
	static UINT static_ID;

	Vec2 colliderPos;
	Vec2 offSet;
	Vec2 colliderScale;
	CGameObject* owner;
	UINT ID;
	int collCount;

public:
	CCollider();
	CCollider(CGameObject* obj);
	CCollider(const CCollider& other);
	~CCollider();

	CCollider& operator=(CCollider& other) = delete;

	void finalupdate();
	void render(HDC& hDC);

	Vec2 getOffSet();
	Vec2 getColliderPos();
	Vec2 getColliderScale();
	CGameObject* getOwner();

	void setOffSet(Vec2 vec);
	void setColliderPos(Vec2 vec);
	void setColliderScale(Vec2 vec);

	UINT getID();

	virtual void onCollisionEnter(CCollider* other);
	virtual void onCollisionStay(CCollider* other);
	virtual void onCollisionExit(CCollider* other);
};

