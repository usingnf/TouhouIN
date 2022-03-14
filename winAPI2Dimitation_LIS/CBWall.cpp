#include "pch.h"
#include "CBWall.h"
#include "CStar.h"
#include "CScene.h"	

CBWall::CBWall()
{
	scale = pScale;
	name = L"Wall";

	createCollider();
	getCollider()->setColliderScale(scale);

	//texture = CResourceManager::getInstance()->loadTexture(L"BWall", L"Mario_Wall2.bmp");

	//createAnimator();
	//getAnimator()->createAnimation(L"Stand", texture, Vec2(480, 0), Vec2(32, 32), Vec2(32, 0), 0.5, 3);
	//getAnimator()->createAnimation(L"Die", texture, Vec2(96, 0), Vec2(32, 32), Vec2(32, 0), 1, 1);
	//getAnimator()->play(L"Stand");
}

CBWall* CBWall::clone()
{
	return new CBWall(*this);
}

CBWall::~CBWall()
{

}

void CBWall::update()
{
	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CBWall::render(HDC& hDC)
{
	component_render(hDC);
}

void CBWall::onCollisionEnter(CCollider* other)
{
	if (isBroken == false)
	{
		if (other->getOwner()->getName() == L"Mario")
		{
			if (other->getOwner()->getPos().y - (other->getColliderScale().y/2) > this->pos.y)
			{
				double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2;
				double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
				if (colScale > posDiff)
				{
					isBroken = true;
					getAnimator()->play(L"Die");

					CStar* star = new CStar();
					star->setPos(this->getPos());
					CSceneManager::getInstance()->getCurScene()->AddObject(star, Group_GameObj::Item);
				}
			}
		}
	}
	
}

void CBWall::onCollisionStay(CCollider* other)
{

}

void CBWall::onCollisionExit(CCollider* other)
{

}
