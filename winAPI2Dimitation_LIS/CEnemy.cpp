#include "pch.h"
#include "CEnemy.h"
#include "CItem.h"

CEnemy::CEnemy()
{
	name = L"Enemy";

	createCollider();
	getCollider()->setColliderScale(Vec2(28, 28));

	createAnimator();
	CAnimation* ani = nullptr;

	image = CResourceManager::getInstance()->loadD2DImage(L"Enemy.png", L"\\texture\\Enemy.png");

	getAnimator()->createAnimation(L"stay", image, Vec2(0, 0), Vec2(32, 32), Vec2(32, 0), 0.08, 4);
	getAnimator()->createAnimation(L"moveleft", image, Vec2(224, 0), Vec2(32, 32), Vec2(-32, 0), 0.1, 4);
	getAnimator()->createAnimation(L"moveright", image, Vec2(224, 0), Vec2(32, 32), Vec2(-32, 0), 0.1, 4);
	getAnimator()->createAnimation(L"die", image, Vec2(0, 128), Vec2(64, 64), Vec2(64, 0), 1, 1);
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
	if (pos.x < -50 || pos.y < -50 || pos.x > STAGE_WIDTH + 50 || pos.y > WS_HEIGHT + 50)
	{
		DELETEOBJECT(this);
	}

	if (hp > 0)
	{
		if (m_pFunc1 != nullptr)
		{
			m_pFunc1((DWORD_PTR)this);
		}

		if (ai == 1)
		{
			if (destPos != pos)
			{
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
			}
		}
	}
	else
	{
		if (this->timer == 0)
		{
			this->setScale(Vec2(1, 1));
		}
		else if (this->timer >= 0.5)
		{
			DELETEOBJECT(this);
		}
		else
		{
			double t = DT();
			this->setScale(getScale() + Vec2(t*200, t*200));
		}
		this->timer += DT();
		
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
	this->ai = 1;
}

void CEnemy::accMove(double startSpeed, double accSpeed)
{
	this->speed = startSpeed;
	this->accSpeed = accSpeed;
}

void CEnemy::setItemDrop(Group_Item type, int count)
{
	if (type == Group_Item::Life)
	{
		this->lifeItem = count;
	}
	else if (type == Group_Item::Power)
	{
		this->powerItem = count;
	}
	else if (type == Group_Item::Score)
	{
		this->scoreItem = count;
	}
	else if (type == Group_Item::Spell)
	{
		this->spellItem = count;
	}
}

void CEnemy::die()
{
	CSoundManager::getInstance()->addSound(L"se_enep00.wav", L"se_enep00.wav", false, false);
	CSoundManager::getInstance()->play(L"se_enep00.wav");
	getAnimator()->play(L"die");
	for (int i = 0; i < lifeItem; i++)
	{
		CItem* item = new CItem();
		item->setPos(pos);
		item->setScale(Vec2(20, 20));
		item->setAngle(rand() % 360);
		item->setHp(10);
		item->setItemType(Group_Item::Life);
		CREATEOBJECT(item, Group_GameObj::Item);
	}
	for (int i = 0; i < powerItem; i++)
	{
		CItem* item2 = new CItem();
		item2->setPos(pos);
		item2->setScale(Vec2(20, 20));
		item2->setAngle(rand() % 360);
		item2->setHp(10);
		item2->setItemType(Group_Item::Power);
		CREATEOBJECT(item2, Group_GameObj::Item);
	}
	for (int i = 0; i < scoreItem; i++)
	{
		CItem* item3 = new CItem();
		item3->setPos(pos);
		item3->setScale(Vec2(20, 20));
		item3->setAngle(rand() % 360);
		item3->setHp(10);
		item3->setItemType(Group_Item::Score);
		CREATEOBJECT(item3, Group_GameObj::Item);
	}
	
	for (int i = 0; i < spellItem; i++)
	{
		CItem* item4 = new CItem();
		item4->setPos(pos);
		item4->setScale(Vec2(20, 20));
		item4->setAngle(rand() % 360);
		item4->setHp(10);
		item4->setItemType(Group_Item::Spell);
		CREATEOBJECT(item4, Group_GameObj::Item);
	}

}

void CEnemy::onCollisionEnter(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Player")
		{
			other->getOwner()->setHp(0);
		}
	}

}

void CEnemy::onCollisionStay(CCollider* other)
{
	
}

void CEnemy::onCollisionExit(CCollider* other)
{

}
