#include "pch.h"
#include "CRemilia.h"

CRemilia::CRemilia()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Remilia";

	createCollider();
	getCollider()->setColliderScale(Vec2(50, 50));

	//texture = CResourceManager::getInstance()->loadTexture(L"Remilia", L"Remilia.bmp");
	image = CResourceManager::getInstance()->loadD2DImage(L"Remilia", L"\\texture\\Remilia.bmp");

	createAnimator();
	getAnimator()->createAnimation(L"stay", image, Vec2(0,48), Vec2(48,48), Vec2(48,0), 0.08, 4);
	getAnimator()->play(L"stay");

	CAnimation* ani;
	ani = getAnimator()->findAnimation(L"stay");
	ani->setLoop(true);
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
	if (KEY('W') == (UINT)Key_State::Hold)
	{
		this->pos.y += -speed * DT();
	}
	if (KEY('A') == (UINT)Key_State::Hold)
	{
		this->pos.x += -speed * DT();
	}
	if (KEY('S') == (UINT)Key_State::Hold)
	{
		this->pos.y += speed * DT();
	}
	if (KEY('D') == (UINT)Key_State::Hold)
	{
		this->pos.x += speed * DT();
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CRemilia::render(HDC& hDC)
{
	component_render(hDC);
}
