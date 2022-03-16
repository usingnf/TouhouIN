#include "pch.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	name = L"Enemy";

	createCollider();
	getCollider()->setColliderScale(Vec2(28, 28));

	createAnimator();
	CAnimation* ani = nullptr;

	image = CResourceManager::getInstance()->loadD2DImage(L"Enemy", L"\\texture\\Enemy.png");
	//image = CResourceManager::getInstance()->loadD2DImage(L"Remilia", L"\\texture\\Remilia.png");

	getAnimator()->createAnimation(L"stay", image, Vec2(0, 0), Vec2(32, 32), Vec2(32, 0), 0.08, 4);
	getAnimator()->createAnimation(L"moveleft", image, Vec2(224, 0), Vec2(32, 32), Vec2(-32, 0), 0.1, 4);
	getAnimator()->createAnimation(L"moveright", image, Vec2(224, 0), Vec2(32, 32), Vec2(-32, 0), 0.1, 4);
	getAnimator()->play(L"stay");


	ani = getAnimator()->findAnimation(L"stay");
	ani->setLoop(true);

	ani = getAnimator()->findAnimation(L"moveleft");
	ani->setLoop(false);

	ani = getAnimator()->findAnimation(L"moveright");
	ani->setLoop(false);
	ani->setReverse(true);
}

CEnemy* CEnemy::clone()
{
	return new CEnemy(*this);
}

CEnemy::~CEnemy()
{
}


void CEnemy::update()
{
	if (KEY(VK_LBUTTON) == (UINT)Key_State::Tap)
	{
		accMove(maxSpeed, -100);
		destPos = GETMOUSEPOS();
	}

	if (Vec2::distance(destPos, pos) < speed * DT() + 1)
	{
		accSpeed = 0;
		destPos = pos;
		if (getAnimator()->getCurAnimationName() != L"stay")
			getAnimator()->play(L"stay");
	}
	else
	{
		if (speed < 0)
		{
			speed = 0;
			destPos = pos;
		}
		else if (speed <= maxSpeed)
			speed += accSpeed * DT();
		else
			speed = maxSpeed;

		if (destPos.x < pos.x)
		{
			if (getAnimator()->getCurAnimationName() != L"moveleft")
				getAnimator()->play(L"moveleft");
		}
		else
		{
			if (getAnimator()->getCurAnimationName() != L"moveright")
				getAnimator()->play(L"moveright");
		}

		Vec2 vec = (destPos - pos).normalized();
		pos.x += vec.x * speed * DT();
		pos.y += vec.y * speed * DT();
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CEnemy::render(HDC& hDC)
{
	component_render(hDC);
}

void CEnemy::setMaxSpeed(double speed)
{
	this->maxSpeed = speed;
}

void CEnemy::setDestPos(Vec2 pos)
{
	this->destPos = pos;
}

void CEnemy::accMove(double startSpeed, double accSpeed)
{
	this->speed = startSpeed;
	this->accSpeed = accSpeed;
}

void CEnemy::onCollisionEnter(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			
		}
	}

}

void CEnemy::onCollisionStay(CCollider* other)
{
	
}

void CEnemy::onCollisionExit(CCollider* other)
{

}
