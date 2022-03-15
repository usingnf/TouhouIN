#include "pch.h"
#include "CRemilia.h"

CRemilia::CRemilia()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Remilia";

	createCollider();
	getCollider()->setColliderScale(Vec2(50, 50));

	
	image = CResourceManager::getInstance()->loadD2DImage(L"Remilia", L"\\texture\\Remilia.png");

	createAnimator();
	getAnimator()->createAnimation(L"stay", image, Vec2(0,0), Vec2(48,48), Vec2(48,0), 0.08, 4);
	getAnimator()->createAnimation(L"left", image, Vec2(0, 48), Vec2(48, 48), Vec2(48, 0), 0.02, 4);
	getAnimator()->createAnimation(L"right", image, Vec2(0, 48), Vec2(48, 48), Vec2(48, 0), 0.02, 4);
	getAnimator()->play(L"stay");

	CAnimation* ani;
	ani = getAnimator()->findAnimation(L"stay");
	ani->setLoop(true);
	ani->setReverse(true);

	ani = getAnimator()->findAnimation(L"left");
	ani->setLoop(false);

	ani = getAnimator()->findAnimation(L"right");
	ani->setLoop(false);
	ani->setReverse(true);
	
	/*
	image = CResourceManager::getInstance()->loadD2DImage(L"Sakuya", L"\\texture\\Sakuya.png");
	createAnimator();
	getAnimator()->createAnimation(L"stay", image, Vec2(0, 0), Vec2(32, 48), Vec2(32, 0), 0.08, 4);
	getAnimator()->createAnimation(L"left", image, Vec2(0, 48), Vec2(32, 48), Vec2(32, 0), 0.08, 7);
	getAnimator()->createAnimation(L"right", image, Vec2(0, 48), Vec2(32, 48), Vec2(32, 0), 0.08, 7);
	getAnimator()->play(L"stay");

	CAnimation* ani;
	ani = getAnimator()->findAnimation(L"stay");
	ani->setLoop(true);

	ani = getAnimator()->findAnimation(L"right");
	ani->setReverse(true);
	*/
}

CRemilia* CRemilia::clone()
{
	return new CRemilia(*this);
}

CRemilia::~CRemilia()
{
}

void CRemilia::update()
{
	if (KEY(VK_UP) == (UINT)Key_State::Hold)
	{
		this->pos.y += -speed * DT();
	}
	if (KEY(VK_LEFT) == (UINT)Key_State::Tap)
	{
		getAnimator()->play(L"left");
	}
	if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
	{
		this->pos.x += -speed * DT();
	}
	if (KEY(VK_DOWN) == (UINT)Key_State::Hold)
	{
		this->pos.y += speed * DT();
	}
	if (KEY(VK_RIGHT) == (UINT)Key_State::Tap)
	{
		getAnimator()->play(L"right");
	}
	if (KEY(VK_RIGHT) == (UINT)Key_State::Hold)
	{
		this->pos.x += speed * DT();
	}
	if (KEY(VK_LEFT) == (UINT)Key_State::None && KEY(VK_RIGHT) == (UINT)Key_State::None)
	{
		if(getAnimator()->getCurAnimationName() != L"stay")
			getAnimator()->play(L"stay");
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CRemilia::render(HDC& hDC)
{
	component_render(hDC);
}
