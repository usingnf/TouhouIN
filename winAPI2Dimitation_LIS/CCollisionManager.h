#pragma once
#include "CCollider.h"


union ColliderID
{
	struct
	{
		UINT left_id;
		UINT right_id;
	};
	ULONGLONG ID;
};

class CCollisionManager
{
	SINGLETON(CCollisionManager);

private:
	UINT m_arrCheck[(UINT)Group_GameObj::Size];
	map<ULONGLONG, bool> m_mapCollisionInfo;

	void collisionGroupUpdate(Group_GameObj left, Group_GameObj right);
	bool isCollision(CCollider* left, CCollider* right);

public:
	void init();
	void update();
	void checkGroup(Group_GameObj left, Group_GameObj right);
	void unCheckGroup(Group_GameObj left, Group_GameObj right);
	void reset();
};

