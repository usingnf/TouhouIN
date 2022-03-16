#include "pch.h"
#include "CPlayer.h"



CPlayer::CPlayer()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Player";

	createCollider();
	getCollider()->setColliderScale(Vec2(30, 30));


	image = CResourceManager::getInstance()->loadD2DImage(L"Missile", L"\\texture\\Missile.png");

	createAnimator();
	getAnimator()->createAnimation(L"stay", image, Vec2(312-32, 149-32), Vec2(64, 64), Vec2(64, 0), 1, 1);
	getAnimator()->play(L"stay");
}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

CPlayer::~CPlayer()
{
}

void CPlayer::update()
{
	Vec2 vec = Vec2(0, 0);

	if (KEY(VK_UP) == (UINT)Key_State::Hold)
	{
		if(pos.y > 10 + 10)
			vec.y += -1;
	}
	if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
	{
		if(pos.x > 20 + 10)
		vec.x += -1;
	}
	if (KEY(VK_DOWN) == (UINT)Key_State::Hold)
	{
		if (pos.y < STAGE_HEIGHT + 10 - 10)
			vec.y += 1;
	}
	if (KEY(VK_RIGHT) == (UINT)Key_State::Hold)
	{
		if (pos.x < STAGE_WIDTH + 20 - 10)
			vec.x += 1;
	}

	vec.normalized();

	this->pos.x += speed * DT() * vec.x;
	this->pos.y += speed * DT() * vec.y;

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CPlayer::render(HDC& hDC)
{
	component_render(hDC);
}
