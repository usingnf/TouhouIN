#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
	speed = mSpeed;
	scale = mScale;
	name = L"Monster";
	gravity = 2000;
	wallCount = 0;
	hp = 1;
	angle = 180;

	createCollider();
	getCollider()->setColliderScale(Vec2(28, 28));

	//texture = CResourceManager::getInstance()->loadTexture(L"Gumba", L"Mario_Monster2.bmp");

	/*
	createAnimator();
	getAnimator()->createAnimation(L"Walk", texture, Vec2(0, 0), Vec2(28, 28), Vec2(28, 0), 0.2, 2);
	getAnimator()->createAnimation(L"Die", texture, Vec2(56, 0), Vec2(28, 28), Vec2(28, 0), 0.2, 1);
	getAnimator()->play(L"Walk");
	*/
}

CMonster* CMonster::clone()
{
	return new CMonster(*this);
}

CMonster::~CMonster()
{
}


void CMonster::update()
{
	Vec2 vec = Vec2(0, 0);
	if (hp > 0)
	{
		if (angle == 0)
		{
			vec.x = 1;
		}
		else
		{
			vec.x = -1;
		}

		if (velocity.y > -500)
		{
			velocity.y += -gravity * DT();
		}

		if (wallCount > 0)
		{
			velocity.y = 0;
		}

		pos.y += -velocity.y * DT();

		vec = vec.normalized();

		this->pos.x += speed * DT() * vec.x;
		this->pos.y += speed * DT() * vec.y;
	}
	else
	{
		if (getAnimator()->getCurAnimationName() != L"Die")
		{
			getAnimator()->play(L"Die");
		}
		if (timer == 0)
		{
			timer = 1;
		}
		else if (timer < 0)
		{
			CEventManager::getInstance()->deleteGameObject(this);
		}
		else
		{
			timer += -DT();
		}
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CMonster::render(HDC& hDC)
{
	component_render(hDC);
}

void CMonster::onCollisionEnter(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2 - 4;
			double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
			if (colScale > posDiff)
			{
				if (other->getOwner()->getPos().x > this->pos.x)
				{
					this->pos.x += -1;
					angle = 180;
				}
				else
				{
					this->pos.x += 1;
					angle = 0;
				}
			}
			if (other->getOwner()->getPos().y > this->pos.y)
			{
				wallCount++;
			}
			velocity.y = 0;
		}

	}

}

void CMonster::onCollisionStay(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2 - 2;
			double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
			if (colScale > posDiff)
			{
				if (other->getOwner()->getPos().x > this->pos.x)
				{
					this->pos.x += -1;
					angle = 180;
				}
				else
				{
					this->pos.x += 1;
					angle = 0;
				}
			}
			velocity.y = 0;
		}
	}
}

void CMonster::onCollisionExit(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			if (other->getOwner()->getPos().y > this->pos.y)
			{
				wallCount--;
			}
		}
	}
}
