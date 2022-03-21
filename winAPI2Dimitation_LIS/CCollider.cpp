#include "pch.h"
#include "CCollider.h"

UINT CCollider::static_ID = 1;

CCollider::CCollider()
{
	colliderPos = Vec2(0,0);
	offSet = Vec2(0, 0);
	colliderScale = Vec2(0, 0);
	owner = nullptr;
	collCount = 0;

	ID = static_ID++;
}

CCollider::CCollider(CGameObject* obj)
{
	this->owner = obj;
	ID = static_ID++;
	collCount = 0;
}

CCollider::CCollider(const CCollider& other)
{
	owner = nullptr;
	offSet = other.offSet;
	colliderPos = other.colliderPos;
	colliderScale = other.colliderScale;
	ID = static_ID++;
	collCount = other.collCount;
}

CCollider::~CCollider()
{
}

void CCollider::finalupdate()
{
	Vec2 objPos = owner->getPos();
	colliderPos = objPos + offSet;
}

void CCollider::render(HDC& hDC)
{
	if (g_isDeveloperMode == false)
		return;
	Group_Pen pType;
	COLORREF color = RGB(0, 0, 0);
	if (collCount)
	{
		color = RGB(255, 0, 0);
		pType = Group_Pen::Red;
	}
	else
	{
		color = RGB(0, 255, 0);
		pType = Group_Pen::Green;
	}
		

	SelectGDI brush(hDC, Group_Brush::Hollow);
	SelectGDI pen(hDC, pType);

	Vec2 camPos = CCameraManager::getInstance()->getRenderPos(colliderPos);

	CRenderManager::getInstance()->RenderRectangle(
		camPos.x - (colliderScale.x / 2), camPos.y - (colliderScale.y / 2),
		camPos.x + (colliderScale.x / 2), camPos.y + (colliderScale.y / 2), color);

}

Vec2 CCollider::getOffSet()
{
	return offSet;
}

Vec2 CCollider::getColliderPos()
{
	return colliderPos;
}

Vec2 CCollider::getColliderScale()
{
	return colliderScale;
}

CGameObject* CCollider::getOwner()
{
	return owner;
}

void CCollider::setOffSet(Vec2 vec)
{
	this->offSet = vec;
}

void CCollider::setColliderPos(Vec2 vec)
{
	this->colliderPos = vec;
}

void CCollider::setColliderScale(Vec2 vec)
{
	this->colliderScale = vec;
}

UINT CCollider::getID()
{
	return ID;
}

void CCollider::onCollisionEnter(CCollider* other)
{
	owner->onCollisionEnter(other);
	collCount++;
}

void CCollider::onCollisionStay(CCollider* other)
{
	owner->onCollisionStay(other);
}

void CCollider::onCollisionExit(CCollider* other)
{
	owner->onCollisionExit(other);
	collCount--;
}
