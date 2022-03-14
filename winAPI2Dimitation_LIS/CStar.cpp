#include "pch.h"
#include "CStar.h"


CStar::CStar()
{
	scale = pScale;
	name = L"Item";
	gravity = 1000;

	createCollider();
	getCollider()->setColliderScale(scale);

	//texture = CResourceManager::getInstance()->loadTexture(L"Star", L"Mario_Item2.bmp");

	/*
	createAnimator();
	getAnimator()->createAnimation(L"Stand", texture, Vec2(4, 556), Vec2(32, 32), Vec2(32, 0), 1, 1);
	getAnimator()->play(L"Stand");
	*/
}

CStar* CStar::clone()
{
	return new CStar(*this);
}

CStar::~CStar()
{

}

void CStar::update()
{
	Vec2 vec = Vec2(0, 0);
	if (isMove == true)
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

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CStar::render(HDC& hDC)
{
	component_render(hDC);
}

void CStar::onCollisionEnter(CCollider* other)
{
	if (isMove == true)
	{
		if (other->getOwner()->getName() == L"Mario")
		{
			CEventManager::getInstance()->deleteGameObject(this);
		}

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

void CStar::onCollisionStay(CCollider* other)
{
	if (other->getOwner()->getName() == L"Wall")
	{
		if (isMove == true)
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
			velocity.y = 0;
		}
		this->pos.y += -100 * DT();
	}
}

void CStar::onCollisionExit(CCollider* other)
{
	if (other->getOwner()->getName() == L"Wall")
	{
		if (isMove == true)
		{
			if (other->getOwner()->getPos().y > this->pos.y)
			{
				wallCount--;
			}
		}
		isMove = true;
	}	

}
