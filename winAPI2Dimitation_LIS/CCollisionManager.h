#pragma once
#include "CCollider.h"

//충돌체 exit 안되는 버그 찾기

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

