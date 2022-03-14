#include "pch.h"
#include "CMario.h"
//몬스터 밟기랑, 카메라 이동

CMario::CMario()
{
	speed = pSpeed;
	scale = pScale;
	name = L"Mario";
	gravity = 2000;
	wallCount = 0;
	isJump = false;
	maxJump = 200;
	jumpPower = 500;
	hp = 1;


	createCollider();
	getCollider()->setColliderScale(Vec2(36, 54));

	//texture = CResourceManager::getInstance()->loadTexture(L"Mario", L"Mario_Player2.bmp");
	image = CResourceManager::getInstance()->loadD2DImage(L"Mario", L"\\texture\\Mario_Player2.bmp");
	
	createAnimator();
	
	getAnimator()->createAnimation(L"Stand", image, Vec2(8, 8), Vec2(36, 64), Vec2(36, 0), 0.2, 1);
	getAnimator()->createAnimation(L"Walk", image, Vec2(44, 8), Vec2(36, 64), Vec2(36, 0), 0.2, 3);
	getAnimator()->createAnimation(L"Run", image, Vec2(44, 8), Vec2(36, 64), Vec2(36, 0), 0.05, 3);
	getAnimator()->createAnimation(L"Jump", image, Vec2(188, 8), Vec2(36, 64), Vec2(36, 0), 0.2, 1);
	getAnimator()->createAnimation(L"Die", image, Vec2(512, 72), Vec2(36, 32), Vec2(36, 0), 0.2, 1);
	getAnimator()->play(L"Stand");

	CAnimation* ani;
	ani = getAnimator()->findAnimation(L"Stand");
	ani->GetFrame(0).fptOffset = Vec2(0, 0);
	//ani->GetFrame(0).duration = 1;
	ani->setLoop(true);
	
}

CMario* CMario::clone()
{
	return new CMario(*this);
}

CMario::~CMario()
{
}

void CMario::update()
{
	
	if (this->pos.x < WS_WIDTH / 2)
	{
		CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));
	}
	else if (this->pos.x > 1000)
	{
		CCameraManager::getInstance()->setLookAt(Vec2(1000, WS_HEIGHT / 2));
	}
	else
	{
		CCameraManager::getInstance()->setLookAt(Vec2(this->pos.x, WS_HEIGHT / 2));
	}
	Vec2 vec(0, 0);

	if (hp > 0)
	{
		bool lShift = false;
		if (KEY(VK_LSHIFT) == (UINT)Key_State::Hold)
		{
			lShift = true;
		}

		if (KEY('D') == (UINT)Key_State::Hold || KEY(VK_RIGHT) == (UINT)Key_State::Hold)
		{
			angle = 0;
			if (lrWall <= 0.1)
			{
				vec.x += 1;
			}

			if (wallCount > 0)
			{
				if (lShift == false)
				{
					if (getAnimator()->getCurAnimationName() != L"Walk")
					{
						getAnimator()->play(L"Walk");
					}
				}
				else
				{
					if (getAnimator()->getCurAnimationName() != L"Run")
					{
						getAnimator()->play(L"Run");
					}
				}
			}


		}
		if (KEY('A') == (UINT)Key_State::Hold || KEY(VK_LEFT) == (UINT)Key_State::Hold)
		{
			angle = 180;
			if (lrWall >= -0.1)
			{
				vec.x += -1;
			}

			if (wallCount > 0)
			{
				if (lShift == false)
				{
					if (getAnimator()->getCurAnimationName() != L"Walk")
					{
						getAnimator()->play(L"Walk");
					}
				}
				else
				{
					if (getAnimator()->getCurAnimationName() != L"Run")
					{
						getAnimator()->play(L"Run");
					}
				}
			}
		}

		if (isJump == false)
		{
			if (KEY('Z') == (UINT)Key_State::Tap || KEY(VK_SPACE) == (UINT)Key_State::Tap)
			{
				if (wallCount > 0)
				{
					isJump = true;
				}
			}
		}


		if (KEY('Z') == (UINT)Key_State::None && KEY(VK_SPACE) == (UINT)Key_State::None)
		{
			isJump = false;
		}


		if (vec.length() == 0 && wallCount > 0)
		{
			getAnimator()->play(L"Stand");
		}

		Vec2::normalize(vec);

		if (isJump == true)
		{
			if (maxJump > jumpHeight)
			{
				jumpHeight += jumpPower * DT();
				this->pos.y += -jumpPower * DT();
			}
			else
			{
				isJump = false;
			}
		}

		if (lrWall != 0)
		{
			if (lrWall < 0)
			{
				lrWall += DT();
			}
			else
			{
				lrWall += -DT();
			}
		}

		if (wallCount > 0)
		{
			jumpHeight = 0;
			velocity.y = 0;
		}
		else
		{
			//공중에 있을 때

			if (getAnimator()->getCurAnimationName() != L"Jump")
			{
				getAnimator()->play(L"Jump");
			}
			if (isJump == false)
			{
				if (velocity.y > -500)
				{
					velocity.y += -gravity * DT();
				}
			}

		}
		//velocity.y += -gravity * DT();
		//pos.x += velocity.x * DT();
		pos.y += -velocity.y * DT();

		if (lShift == false)
		{
			this->pos.x += speed * DT() * vec.x;
			this->pos.y += speed * DT() * vec.y;
		}
		else
		{
			this->pos.x += speed * DT() * vec.x * 2;
			this->pos.y += speed * DT() * vec.y * 2;
		}

		if (KEY(VK_SPACE) == (UINT)Key_State::Tap)
		{
			CreateMissile();
		}
	}
	else
	{
		if (getAnimator()->getCurAnimationName() != L"Die")
		{
			getAnimator()->play(L"Die");
		}
		if (timer == 0)
		{
			timer = 1;
		}
		else if (timer < 0)
		{
			CEventManager::getInstance()->changeScene(Group_Scene::Start);
		}
		else
		{
			timer += -DT();
		}
	}
	

	CAnimator* ani = getAnimator();
	if (ani != nullptr)
		ani->update();
		
}

void CMario::render(HDC& hDC)
{
	component_render(hDC);
}

void CMario::CreateMissile()
{
	/*
	Vec2 missilePos = pos;
	CMissile* missile = new CMissile();
	missile->setPos(missilePos);
	missile->setAngle(Vec2::getAngle(Vec2(0, 0), Vec2(1, 0)));

	//CEventManager::getInstance()->createGameObject(missile);
	CREATEOBJECT(missile, Group_GameObj::Missile);
	*/
}

void CMario::onCollisionEnter(CCollider* other)
{
	if (hp > 0 )
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2 - 4;
			double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
			if (colScale > posDiff)
			{
				if (other->getOwner()->getPos().x > this->pos.x)
				{
					this->pos.x += -1;
					lrWall = 0.25;
				}
				else
				{
					this->pos.x += 1;
					lrWall = -0.25;
				}
			}

			if (other->getOwner()->getPos().y > this->pos.y)
			{
				wallCount++;
			}
			else
			{
				isJump = false;
			}
		}
		else if (other->getOwner()->getName() == L"Monster")
		{
			
			if (other->getOwner()->getHp() > 0)
			{
				double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2;
				double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
				if (colScale < posDiff + 5)
				{
					other->getOwner()->setHp(0);
					this->velocity.y = 150;
				}
				else
				{
					hp = 0;
				}
			}
			
		}
	}
}

void CMario::onCollisionStay(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			double colScale = (getCollider()->getColliderScale().y + other->getColliderScale().y) / 2 - 2;
			double posDiff = abs(this->pos.y - other->getOwner()->getPos().y);
			if (colScale > posDiff)
			{
				if (other->getOwner()->getPos().x > this->pos.x)
				{
					this->pos.x += -1;
					lrWall = 0.2;
				}
				else
				{
					this->pos.x += 1;
					lrWall = -0.2;
				}
			}
			velocity.y = 0;
		}
	}
	
}

void CMario::onCollisionExit(CCollider* other)
{
	if (hp > 0)
	{
		if (other->getOwner()->getName() == L"Wall")
		{
			if (other->getOwner()->getPos().y > this->pos.y)
			{
				wallCount--;
			}
		}
	}

}
