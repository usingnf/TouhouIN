#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"


CPlayer::CPlayer()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Player";
	timer = 0;

	createCollider();
	getCollider()->setColliderScale(Vec2(30, 30));

	image = CResourceManager::getInstance()->loadD2DImage(L"Missile.png", L"\\texture\\Missile.png");

	createAnimator();
	getAnimator()->createAnimation(L"stay", image, Vec2(280, 117), Vec2(64, 64), Vec2(64, 0), 1, 1);
	getAnimator()->createAnimation(L"die", image, Vec2(281, 182), Vec2(64, 64), Vec2(64, 0), 1, 1);
	getAnimator()->play(L"stay");

	CAnimation* ani = getAnimator()->findAnimation(L"die");
	ani->setLoop(false);
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
	if (hp > 0)
	{
		Vec2 vec = Vec2(0, 0);

		if (KEY(VK_UP) == (UINT)Key_State::Hold)
		{
			if (pos.y > 10 + 10)
				vec.y += -1;
		}
		if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
		{
			if (pos.x > 20 + 10)
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
		if (KEY(VK_LSHIFT) == (UINT)Key_State::Tap)
		{
			if (pos.y < 120)
			{
				vector<CGameObject*> v = CSceneManager::getInstance()->getCurScene()->getGroupObject(Group_GameObj::Item);
				for (int i = 0; i < v.size(); i++)
				{
					v[i]->setDestPos(pos);
				}
			}
		}
		vec.normalized();

		this->pos.x += speed * DT() * vec.x;
		this->pos.y += speed * DT() * vec.y;
	}
	else if( hp > -10)
	{
		timer += DT();
		if (timer >= 1)
		{
			timer = 0;
			hp = -10;
			CSoundManager::getInstance()->addSound(L"se_pldead00.wav", L"se_pldead00.wav", false, false);
			CSoundManager::getInstance()->play(L"se_pldead00.wav", 0.5f);
			this->die();
		}
	}
	else
	{
		if (getAnimator()->getCurAnimationName() == L"die")
		{
			timer += DT();
			double t = DT();
			if (timer <= 0.5)
			{
				this->setScale(this->getScale() + Vec2(300 * t, 300 * t));

			}
			else
			{
				g_player = nullptr;
				//DELETEOBJECT(this);
				CEventManager::getInstance()->changeScene(Group_Scene::Start);
			}
		}
	}

	


	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CPlayer::render(HDC& hDC)
{
	component_render(hDC);
}

void CPlayer::die()
{
	getAnimator()->play(L"die");
	this->setScale(Vec2(1,1));
}