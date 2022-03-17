#include "pch.h"
#include "CItem.h"
#include "CPlayer.h"

CItem::CItem()
{
	name = L"Item";
	this->speed = 100;
	isNearPlayer = false;

	createCollider();
	getCollider()->setColliderScale(Vec2(100, 100));

	isFixed = true;

	createAnimator();
	CAnimation* ani = nullptr;

	image = CResourceManager::getInstance()->loadD2DImage(L"Missile.png", L"\\texture\\Missile.png");

	getAnimator()->createAnimation(L"stay", image, Vec2(281, 72), Vec2(12, 12), Vec2(12, 0), 1, 1);
	getAnimator()->play(L"stay");


	ani = getAnimator()->findAnimation(L"stay");
	ani->setLoop(true);
}

CItem* CItem::clone()
{
	return new CItem(*this);
}

CItem::~CItem()
{

}


void CItem::update()
{
	if (pos.x < -50 || pos.y < -50 || pos.x > STAGE_WIDTH + 50 || pos.y > WS_HEIGHT + 50)
	{
		DELETEOBJECT(this);
	}

	if (pos.y < 10 + 10)
	{
		angle = 150 + rand() % 60;
	}
		
	if (pos.x < 20 + 10)
	{
		angle = 60 + rand() % 60;
	}

	if (pos.y > STAGE_HEIGHT + 10 - 10)
	{
		angle = -30 + rand() % 60;
	}
		
	if (pos.x > STAGE_WIDTH + 20 - 10)
	{
		angle = 240 + rand() % 60;
	}		
	

	if (hp > 0)
	{
		if (destPos.length() > 0)
		{
			destPos = g_player->getPos();
			Vec2 vec = (destPos - pos).normalized();
			pos.x += vec.x * speed * 4 * DT();
			pos.y += vec.y * speed * 4 * DT();
		}
		else
		{
			if (isNearPlayer == false)
			{
				pos.x += speed * DT() * cos((angle - 90) * RADIAN);
				pos.y += speed * DT() * sin((angle - 90) * RADIAN);
			}
			hp += -DT();
		}
		
	}
	else
	{
		DELETEOBJECT(this);
	}

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
}

void CItem::render(HDC& hDC)
{
	component_render(hDC);
}

void CItem::onCollisionEnter(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			isNearPlayer = true;
		}
	}
}

void CItem::onCollisionStay(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			Vec2 destPos2 = other->getOwner()->getPos();
			Vec2 vec = (destPos2 - pos).normalized();
			if (destPos.length() == 0)
			{
				pos.x += vec.x * speed * 2 * DT();
				pos.y += vec.y * speed * 2 * DT();
			}
			if (Vec2::distance(destPos2, pos) < 20)
			{
				CSoundManager::getInstance()->addSound(L"se_item00.wav", L"se_item00.WAV", false, false);
				CSoundManager::getInstance()->play(L"se_item00.wav", 0.5f);
				g_power += 1;
				DELETEOBJECT(this);
			}
		}
	}
}

void CItem::onCollisionExit(CCollider* other)
{
	if (getIsDelete() == true)
	{
		int a = 0;
	}
	else
	{
		int b = 0;
	}

	int c = 0;
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			isNearPlayer = false;
		}
	}
}
