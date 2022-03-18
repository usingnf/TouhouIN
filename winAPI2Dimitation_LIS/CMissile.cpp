#include "pch.h"
#include "CMissile.h"
#include "CCollider.h"

CMissile::CMissile()
{
	speed = 100;
	scale = Vec2(50,50);
	damage = 0;
	name = L"Missile";

	createCollider();
	getCollider()->setColliderScale(Vec2(30, 30));
}

CMissile* CMissile::clone()
{
	return new CMissile(*this);
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	if (m_pFunc1 != nullptr)
	{
		m_pFunc1((DWORD_PTR)this);
	}
	else
	{
		if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
		{
			DELETEOBJECT(this);
			return;
			//object 파괴 작업 필요.
		}
		pos.x += speed * DT() * cos((angle - 90) * RADIAN);
		pos.y += speed * DT() * sin((angle - 90) * RADIAN);
	}
	
}

void CMissile::render(HDC& hDC)
{
	

	component_render(hDC);
}

void CMissile::setDamage(double damage)
{
	this->damage = damage;
}

void CMissile::onCollisionEnter(CCollider* other)
{	
	if (other->getOwner()->getHp() > 0)
	{
		if (other->getOwner()->getName() != L"Player")
		{
			g_score += 10 * damage;
		}
		other->getOwner()->setHp(other->getOwner()->getHp() - damage);
		if (other->getOwner()->getHp() <= 0)
		{
			other->getOwner()->die();
		}
		DELETEOBJECT(this);
	}
}