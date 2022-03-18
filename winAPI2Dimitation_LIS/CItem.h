#pragma once

class CItem : public CGameObject
{
private:
	bool isNearPlayer;
	Group_Item itemType = Group_Item::Score;
public:
	CItem();
	virtual CItem* clone();
	~CItem();
	virtual void update();
	virtual void render(HDC& hDC);

	void onCollisionEnter(CCollider* other);
	void onCollisionStay(CCollider* other);
	void onCollisionExit(CCollider* other);

	void setItemType(Group_Item type);
};

