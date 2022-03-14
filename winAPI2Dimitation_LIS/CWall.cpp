#include "pch.h"
#include "CWall.h"


CWall::CWall()
{
	scale = pScale;
	name = L"Wall";

	createCollider();
	getCollider()->setColliderScale(scale);

	//texture = CResourceManager::getInstance()->loadTexture(L"Wall", L"Mario_Wall2.bmp");

	/*
	createAnimator();
	getAnimator()->createAnimation(L"Stand", texture, Vec2(32, 0), Vec2(64, 32), Vec2(64, 0), 1, 1);
	getAnimator()->play(L"Stand");
	*/
}

CWall* CWall::clone()
{
	return new CWall(*this);
}

CWall::~CWall()
{
}

void CWall::update()
{
	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CWall::render(HDC& hDC)
{
	component_render(hDC);
}