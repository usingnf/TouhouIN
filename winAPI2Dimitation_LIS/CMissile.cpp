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
	if (g_gameState != Group_GameState::Play)
	{
		return;
	}

	if (isUse)
	{
		if (m_pFunc1 != nullptr)
		{
			m_pFunc1((DWORD_PTR)this);
		}
		else
		{
			if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
			{
				hp = 0;
			}
			if (hp > 0)
			{
				pos.x += speed * DT() * cos((angle - 90) * RADIAN);
				pos.y += speed * DT() * sin((angle - 90) * RADIAN);
			}
			else if( hp > -10)
			{
				recycleMissile();
			}
			else
			{
				hp = -10;
			}
		}
	}
}

void CMissile::render()
{
	if(isUse)
		component_render();
}

void CMissile::setDamage(double damage)
{
	this->damage = damage;
}

void CMissile::onCollisionEnter(CCollider* other)
{	
	if (g_gameState != Group_GameState::Play)
	{
		return;
	}
	CGameObject* obj = other->getOwner();
	if (obj->getIsInvincible() == false)
	{
		if (obj->getHp() > 0)
		{
			if (obj->getName() == L"Player")
			{
				obj->setHp(obj->getHp() - damage);
			}
			else
			{
				if (obj->getHp() < 10 * damage)
				{
					g_score += 10 * obj->getHp();
				}
				else
				{
					g_score += 10 * damage;
				}
				
				obj->setHp(obj->getHp() - damage);
			}

			if (obj->getHp() <= 0)
			{
				if(g_boss != (CEnemy*)obj)
					obj->die();
			}
			recycleMissile();
		}
	}
	
}

void CMissile::setIsUse(bool use)
{
	this->isUse = use;
}

bool CMissile::getIsUse()
{
	return isUse;
}

void CMissile::recycleMissile()
{
	timer = 0;
	timer2 = 0;
	timerCount = 0;
	m_pFunc1 = nullptr;
	isUse = false;
	this->pos = Vec2(-49, -49);

	if (this->name == L"PMissile")
	{
		DELETEOBJECT(this);
	}
	else
	{
		DELETECOMPONENT(this);
	}
}
