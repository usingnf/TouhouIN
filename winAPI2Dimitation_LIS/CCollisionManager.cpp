#include "pch.h"
#include "CCollisionManager.h"
#include "CScene.h"


CCollisionManager::CCollisionManager()
{
	m_arrCheck[0] = { 0 };
}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::collisionGroupUpdate(Group_GameObj left, Group_GameObj right)
{
	CScene* curScene = CSceneManager::getInstance()->getCurScene();
	const vector<CGameObject*>& vecLeft = curScene->getGroupObject(left);
	const vector<CGameObject*>& vecRight = curScene->getGroupObject(right);

	for (int i = 0; i < vecLeft.size(); i++)
	{
		if (vecLeft[i]->getCollider() == nullptr)
			continue;

		for (int j = 0; j < vecRight.size(); j++)
		{
			if (vecRight[j]->getCollider() == nullptr)
				continue;
			if (vecLeft[i] == vecRight[j])
				continue;
			//충돌 판정
			ColliderID id;
			id.left_id = vecLeft[i]->getCollider()->getID();
			id.right_id = vecRight[j]->getCollider()->getID();

			map<ULONGLONG, bool>::iterator iter = m_mapCollisionInfo.find(id.ID);
			if (m_mapCollisionInfo.end() == iter)
			{
				m_mapCollisionInfo.insert(std::make_pair(id.ID, false));
				iter = m_mapCollisionInfo.find(id.ID);
			}
			//충돌 처리
			if (isCollision(vecLeft[i]->getCollider(), vecRight[j]->getCollider()) == true)
			{
				// 계속 충돌 하는중
				if (iter->second)
				{
					
					if (vecLeft[i]->getIsDelete() || vecRight[j]->getIsDelete())
					{
						vecLeft[i]->getCollider()->onCollisionExit(vecRight[j]->getCollider());
						vecRight[j]->getCollider()->onCollisionExit(vecLeft[i]->getCollider());
						iter->second = false;
					}
					else
					{
						vecLeft[i]->getCollider()->onCollisionStay(vecRight[j]->getCollider());
						vecRight[j]->getCollider()->onCollisionStay(vecLeft[i]->getCollider());
						iter->second = true;
					}
				}
				// 충돌 시작
				else
				{
					
					if (vecLeft[i]->getIsDelete() || vecRight[j]->getIsDelete())
					{
						//do nothing
						iter->second = false;
					}
					else
					{
						vecLeft[i]->getCollider()->onCollisionEnter(vecRight[j]->getCollider());
						vecRight[j]->getCollider()->onCollisionEnter(vecLeft[i]->getCollider());
						iter->second = true;
					}
					
				}
			}
			else
			{
				// 충돌 끝
				if (iter->second)
				{
					vecRight[j]->getCollider()->onCollisionExit(vecLeft[i]->getCollider());
					vecLeft[i]->getCollider()->onCollisionExit(vecRight[j]->getCollider());
					iter->second = false;
					
				}
				// 충돌 안하는중
				else
				{
					//Do Nothing
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionManager::isCollision(CCollider* left, CCollider* right)
{
	/*if (left->getOwner()->getIsDelete() == true)
	{
		return false;
	}
	if (right->getOwner()->getIsDelete() == true)
	{
		return false;
	}*/

	Vec2 leftPos = left->getColliderPos();
	Vec2 leftScale = left->getColliderScale();

	Vec2 rightPos = right->getColliderPos();
	Vec2 rightScale = right->getColliderScale();

	if (abs(leftPos.x - rightPos.x) < (leftScale.x + rightScale.x) / 2.f
		&& abs(leftPos.y - rightPos.y) < (leftScale.y + rightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionManager::init()
{
	checkGroup(Group_GameObj::Enemy, Group_GameObj::Missile);
	checkGroup(Group_GameObj::Player, Group_GameObj::Enemy);
	checkGroup(Group_GameObj::Player, Group_GameObj::Item);
	checkGroup(Group_GameObj::Player, Group_GameObj::EnemyMissile);
}

void CCollisionManager::update()
{
	for (int row = 0; row < (UINT)Group_GameObj::Size; row++)
	{
		for (int col = row; col < (UINT)Group_GameObj::Size; col++)
		{
			if (m_arrCheck[row] & (1 << col))
			{
 				collisionGroupUpdate((Group_GameObj)row, (Group_GameObj)col);
			}
		}
	}
}

void CCollisionManager::checkGroup(Group_GameObj left, Group_GameObj right)
{
	UINT row = (UINT)right; //열
	UINT col = (UINT)left; //행

	if ((UINT)left < (UINT)right)
	{
		row = (UINT)left;
		col = (UINT)right;
	}

	m_arrCheck[row] |= (1 << col);
}

void CCollisionManager::unCheckGroup(Group_GameObj left, Group_GameObj right)
{
	UINT row = (UINT)right; //열
	UINT col = (UINT)left; //행

	if ((UINT)left > (UINT)right)
	{
		row = (UINT)left;
		col = (UINT)right;
	}

	m_arrCheck[row] &= ~(1 << col);
}

void CCollisionManager::reset()
{
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)Group_GameObj::Size);
	/*for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		m_arrCheck[i] = 0;
	}*/
}
