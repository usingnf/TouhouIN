#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CSpell.h"
#include "CMissile.h"

bool CPlayer::isSpell = false;

CPlayer::CPlayer()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Player";
	timer = 0;

	createCollider();
	getCollider()->setColliderScale(Vec2(10, 10));

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

	if (g_gameState != Group_GameState::Play)
	{
		return;
	}

	if (hp > 0)
	{
		Vec2 vec = Vec2(0, 0);

		if (KEY(VK_UP) == (UINT)Key_State::Hold)
		{
			if (pos.y-DT()*speed > 10 + 10)
				vec.y += -1;
		}
		if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
		{
			if (pos.x-DT() * speed > 20 + 10)
				vec.x += -1;
		}
		if (KEY(VK_DOWN) == (UINT)Key_State::Hold)
		{
			if (pos.y + DT() * speed < STAGE_HEIGHT + 10 - 10)
				vec.y += 1;
		}
		if (KEY(VK_RIGHT) == (UINT)Key_State::Hold)
		{
			if (pos.x + DT() * speed < STAGE_WIDTH + 20 - 10)
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
			hp = -100;
			CSoundManager::getInstance()->addSound(L"se_pldead00.wav", L"se_pldead00.wav", false, false);
			CSoundManager::getInstance()->play(L"se_pldead00.wav", 0.5f);
		}
	}
	else
	{
		if (getAnimator()->getCurAnimationName() == L"die")
		{
			if(this->isInvincible == false)
				this->isInvincible = true;
			timer2 += DT();
			double t = DT();
			if (timer2 <= 0.5)
			{
				this->setScale(this->getScale() + Vec2(300 * t, 300 * t));

			}
			else
			{
				this->timer2 = 0;
				if (g_life > 0)
				{
					setIsRender(false);
					g_life += -1;
					this->setPos(Vec2(PL_STARTPOSX, PL_STARTPOSY));
					this->setScale(Vec2(64, 64));
					this->hp = 1;
					
					if ((UINT)g_mode % 2 == 1)
						g_mode = (Group_CharacterMode)((UINT)g_mode - 1);
					getAnimator()->play(L"stay");
				}
				else
				{
					g_player = nullptr;
					//DELETEOBJECT(this);
					CEventManager::getInstance()->changeScene(Group_Scene::Result);
				}
			}
		}
	}

	if (isInvincible == true)
	{
		timer2 += DT();
		if (timer2 >= 2)
		{
			timer2 = 0;
			isInvincible = false;
		}
	}

	if (KEY(VK_LSHIFT) == (UINT)Key_State::Tap)
	{
		this->setIsRender(true);
	}
	else if (KEY(VK_LSHIFT) == (UINT)Key_State::Off)
	{
		this->setIsRender(false);
	}

	if (KEY('X') == (UINT)Key_State::Tap)
	{
		if (g_spell > 0 && CPlayer::isSpell == false)
		{
			getAnimator()->play(L"stay");
			this->setScale(Vec2(64, 64));
			
			CPlayer::isSpell = true;
			g_spell += -1;
			g_bombUse += 1;

			this->hp = 1;

			CSoundManager::getInstance()->addSound(L"se_cat00.wav", L"se_cat00.wav", false, false);
			CSoundManager::getInstance()->play(L"se_cat00.wav", 0.5f);

			CSpell* spell = new CSpell();
			spell->setPos(pos);
			if (g_mode == Group_CharacterMode::Sakuya)
			{
				spell->setHp(3);
				spell->setScale(Vec2(100, 100));
				spell->getAnimator()->play(L"sakuyaspell");
			}
			else if (g_mode == Group_CharacterMode::Remilia)
			{
				spell->setHp(3);
				spell->setScale(Vec2(100, 100));
				spell->getAnimator()->play(L"remiliaspell");
			}

			CREATEOBJECT(spell, Group_GameObj::Spell);

			if ((UINT)g_mode % 2 == 1)
			{
				g_mode = (Group_CharacterMode)((UINT)g_mode - 1);
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
	this->setIsRender(true);
	getAnimator()->play(L"die");
	g_miss += 1;
	this->setScale(Vec2(1,1));
}

CMissile* CPlayer::createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type)
{
	CMissile* missile = new CMissile();
	missile->setPos(pos);
	missile->setScale(size);
	missile->getCollider()->setColliderScale(colSize);
	missile->setSpeed(speed);
	missile->setAngle(angle);
	missile->setDamage(damage);
	missile->setImage(image, leftTop, imageSize);
	missile->setIsUse(true);
	CREATEOBJECT(missile, type);

	return missile;
}