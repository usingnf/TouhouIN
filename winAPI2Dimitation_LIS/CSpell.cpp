#include "pch.h"
#include "CSpell.h"
#include "CPlayer.h"
#include "CScene.h"

CSpell::CSpell()
{
	name = L"Spell";

	createCollider();
	getCollider()->setColliderScale(Vec2(30, 30));
	CAnimation* ani;

	image = CResourceManager::getInstance()->loadD2DImage(L"Enemy.png", L"\\texture\\Enemy.png");

	createAnimator();
	getAnimator()->createAnimation(L"sakuyaspell", image, Vec2(0, 128), Vec2(64, 64), Vec2(64, 0), 1, 1);
	getAnimator()->createAnimation(L"remiliaspell", image, Vec2(0, 128), Vec2(64, 64), Vec2(64, 0), 1, 1);
	getAnimator()->play(L"sakuyaspell");

	ani = getAnimator()->findAnimation(L"sakuyaspell");
	ani->setLoop(false);
}

CSpell* CSpell::clone()
{
	return new CSpell(*this);
}

CSpell::~CSpell()
{

}

void CSpell::update()
{
	wstring tname = getAnimator()->getCurAnimationName();
	double t = DT();

	if (g_player != nullptr)
	{
		if (tname == L"sakuyaspell")
		{
			timer += DT();
			hp += -DT();
			this->pos = g_player->getPos();
			if (timerCount == 0)
			{
				this->scale = Vec2(50, 50);
			}
			if (timerCount < 5)
			{
				this->scale += Vec2(400 * t, 400 * t);
			}
			this->angle += t * 360;

			vector<CGameObject*> vec = CSceneManager::getInstance()->getCurScene()->getGroupObject(Group_GameObj::EnemyMissile);
			for (int i = 0; i < vec.size(); i++)
			{
				if (Vec2::distance(vec[i]->getPos(), pos) < this->scale.length() / 2 - 10)
				{
					vec[i]->setHp(0);
					/*
					if (vec[i]->getIsDelete() == false)
						DELETEOBJECT(vec[i]);
						*/
				}
			}
		}
		else if (tname == L"remiliaspell")
		{
			timer += DT();
			hp += -DT();
			this->pos = g_player->getPos();
			if (timerCount == 0)
			{
				this->scale = Vec2(50, 50);
			}
			if (timerCount < 5)
			{
				this->scale += Vec2(400 * t, 400 * t);
			}
			this->angle += t * 360;

			vector<CGameObject*> vec = CSceneManager::getInstance()->getCurScene()->getGroupObject(Group_GameObj::EnemyMissile);
			for (int i = 0; i < vec.size(); i++)
			{
				if (Vec2::distance(vec[i]->getPos(), pos) < (this->scale.length() / 2) - 10)
				{
					vec[i]->setHp(0);
					/*
					if (vec[i]->getIsDelete() == false)
						DELETEOBJECT(vec[i]);
						*/
				}
			}
		}
	}

	

	if (timer >= 0.1)
	{
		timerCount += 1;
		timer = 0;
	}

	if (hp <= 0)
	{
		CPlayer::isSpell = false;
		DELETEOBJECT(this);
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CSpell::render(HDC& hDC)
{
	component_render(hDC);
}

void CSpell::die()
{
	getAnimator()->play(L"die");
	this->setScale(Vec2(1, 1));
}