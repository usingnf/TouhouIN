#include "pch.h"
#include "CBody.h"
#include "CMissile.h"
#include "CPlayer.h"

CBody::CBody()
{
	scale = pScale;
	name = L"Body";
	mode = 0;

	createCollider();
	getCollider()->setColliderScale(Vec2(30, 30));
	createAnimator();
	CAnimation* ani = nullptr;

	image = CResourceManager::getInstance()->loadD2DImage(L"Remilia.png", L"\\texture\\Remilia.png");
	
	getAnimator()->createAnimation(L"stayRemilia", image, Vec2(0, 0), Vec2(48, 48), Vec2(48, 0), 0.08, 4);
	getAnimator()->createAnimation(L"leftRemilia", image, Vec2(0, 48), Vec2(48, 48), Vec2(48, 0), 0.02, 4);
	getAnimator()->createAnimation(L"rightRemilia", image, Vec2(0, 48), Vec2(48, 48), Vec2(48, 0), 0.02, 4);
	getAnimator()->play(L"stayRemilia");

	
	ani = getAnimator()->findAnimation(L"stayRemilia");
	ani->setLoop(true);
	ani->setReverse(true);

	ani = getAnimator()->findAnimation(L"leftRemilia");
	ani->setLoop(false);

	ani = getAnimator()->findAnimation(L"rightRemilia");
	ani->setLoop(false);
	ani->setReverse(true);

	image = CResourceManager::getInstance()->loadD2DImage(L"Sakuya.png", L"\\texture\\Sakuya.png");

	getAnimator()->createAnimation(L"staySakuya", image, Vec2(0, 0), Vec2(32, 48), Vec2(32, 0), 0.08, 4);
	getAnimator()->createAnimation(L"leftSakuya", image, Vec2(0, 48), Vec2(32, 48), Vec2(32, 0), 0.08, 7);
	getAnimator()->createAnimation(L"rightSakuya", image, Vec2(0, 48), Vec2(32, 48), Vec2(32, 0), 0.08, 7);
	getAnimator()->play(L"staySakuya");


	ani = getAnimator()->findAnimation(L"staySakuya");
	ani->setLoop(true);

	ani = getAnimator()->findAnimation(L"leftSakuya");
	ani->setLoop(false);

	ani = getAnimator()->findAnimation(L"rightSakuya");
	ani->setLoop(false);
	ani->setReverse(true);
}

CBody* CBody::clone()
{
	return new CBody(*this);
}

CBody::~CBody()
{
}

void CBody::update()
{
	if (g_player != nullptr)
	{
		this->setPos(g_player->getPos());

		if (g_player->getHp() <= -10)
		{
			if(g_player->getAnimator()->getCurAnimationName() == L"die")
				this->isRender = false;
		}
		else
		{
			this->isRender = true;
		}
	}

	if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
	{
		if (mode == 0)
		{
			if (getAnimator()->getCurAnimationName() != L"leftSakuya")
				getAnimator()->play(L"leftSakuya");
		}
		else
		{
			if (getAnimator()->getCurAnimationName() != L"leftRemilia")
				getAnimator()->play(L"leftRemilia");
		}
	}
	if (KEY(VK_RIGHT) == (UINT)Key_State::Hold)
	{
		if (mode == 0)
		{
			if (getAnimator()->getCurAnimationName() != L"rightSakuya")
				getAnimator()->play(L"rightSakuya");
		}
		else
		{
			if (getAnimator()->getCurAnimationName() != L"rightRemilia")
				getAnimator()->play(L"rightRemilia");
		}
		
	}
	if (KEY(VK_LEFT) == (UINT)Key_State::None && KEY(VK_RIGHT) == (UINT)Key_State::None)
	{
		if (mode == 0)
		{
			if (getAnimator()->getCurAnimationName() != L"staySakuya")
				getAnimator()->play(L"staySakuya");
		}
		else
		{
			if (getAnimator()->getCurAnimationName() != L"stayRemilia")
				getAnimator()->play(L"stayRemilia");
		}
		
	}
	if (KEY(VK_LSHIFT) == (UINT)Key_State::Tap)
	{
		this->scale = Vec2(48, 48);
		mode = 1;
	}

	if (KEY(VK_LSHIFT) == (UINT)Key_State::Off)
	{
		this->scale = Vec2(32, 48);
		mode = 0;
	}
	if (KEY('Z') == (UINT)Key_State::Hold)
	{
		missileTimer += DT();
		if (missileTimer >= 0.1)
		{
			missileTimer = 0;
			if (mode == 0)
			{
				CSoundManager::getInstance()->addSound(L"se_plst00.wav", L"se_plst00.wav", false, false);
				CSoundManager::getInstance()->play(L"se_plst00.wav", 0.5f);
				
				createMissile(L"SakuyaMissile.png", Vec2(0, 0), Vec2(16, 32), this->getPos(), Vec2(16, 32), Vec2(10, 30), 500, 45, 1, Group_GameObj::Missile);
			}
			else if (mode == 1)
			{
				CSoundManager::getInstance()->addSound(L"se_plst00.wav", L"se_plst00.wav", false, false);
				CSoundManager::getInstance()->play(L"se_plst00.wav", 0.5f);
				createMissile(L"RemiliaMissile.png", Vec2(14, 0), Vec2(8, 48), this->getPos(), Vec2(8, 48), Vec2(10, 30), 500, 0, 1, Group_GameObj::Missile);
			}
			
		}
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CBody::render(HDC& hDC)
{
	component_render(hDC);
}

