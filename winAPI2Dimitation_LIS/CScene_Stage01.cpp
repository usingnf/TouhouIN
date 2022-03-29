#include "pch.h"
#include "CScene_Stage01.h"
#include "CRemilia.h"
#include "CPanelUI.h"
#include "CPlayer.h"
#include "CBody.h"
#include "CEnemy.h"
#include "CText.h"

int getRandomInt(int start, int end)
{
	int dis = end - start;
	int random = rand() % dis;
	return random + start;
}

double getToPlayerAngle(CGameObject* obj)
{
	if (g_player == nullptr)
		return 180;

	return Vec2::getAngle(g_player->getPos() - obj->getPos());
}


CScene_Stage01::CScene_Stage01()
{
	for (int i = 0; i < sizeof(g_missile) / sizeof(CMissile*); i++)
	{
		g_missile[i] = nullptr;
	}
}

CScene_Stage01::~CScene_Stage01()
{
}

//테스트용 ai
void enemyAi01(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 2)
	{
		obj->setTimer(0);
		//action
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f);
		CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), obj->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, 180, 1, Group_GameObj::EnemyMissile);
		missile->getCollider()->setType(Type_Collider::Circle);
	}
}

//좌측에서 한마리 이동 + 유도 공격
void enemyAi02(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (obj->getTimerCount() % 5 == 1)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );

		double angle = getToPlayerAngle(obj);

		CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), obj->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, angle + getRandomInt(-10, 10), 1, Group_GameObj::EnemyMissile);
		missile->getCollider()->setType(Type_Collider::Circle);
	}

	if (obj->getTimerCount() == 8)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		obj->setDestPos(obj->getPos() + Vec2(-50, -500));
		((CEnemy*)self)->accMove(10, 50);
	}	
}

//우측에서 한마리 이동 + 유도 공격
void enemyAi03(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (obj->getTimerCount() % 5 == 1)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );

		double angle = getToPlayerAngle(obj);

		CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), obj->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, angle + getRandomInt(-10, 10), 1, Group_GameObj::EnemyMissile);
		missile->getCollider()->setType(Type_Collider::Circle);
	}

	if (obj->getTimerCount() == 8)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		obj->setDestPos(obj->getPos() + Vec2(50, -500));
		((CEnemy*)self)->accMove(10, 50);
	}
}

//원형 공격
void enemyAi04(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (obj->getTimerCount() % 30 == 1)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );

		for (int i = 0; i < 30; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
				Vec2(28, 28), obj->getPos(),
				Vec2(15, 15), Vec2(15, 15), 100, 12*i, 1, Group_GameObj::EnemyMissile);
			missile->getCollider()->setType(Type_Collider::Circle);
		}	
	}

	if (obj->getTimerCount() == 60)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		obj->setDestPos(obj->getPos() + Vec2(0, -500));
		((CEnemy*)self)->accMove(100, 0);
	}
}

//원형 공격
void enemyAi05(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (timerCount % 33 == 1)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );

		for (int i = 0; i < 30; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
				Vec2(28, 28), obj->getPos(),
				Vec2(15, 15), Vec2(15, 15), 100, 12 * i, 1, Group_GameObj::EnemyMissile);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	if (timerCount == 1 || timerCount == 8 || timerCount == 15)
	{
		double ang = getToPlayerAngle(obj);
		obj->setAngle(ang);
	}
	
	if (timerCount % 7 == 1 && timerCount < 16)
	{
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		obj->setTimerCount(obj->getTimerCount() + 1);
		double ang2 = obj->getAngle();
		for (int i = 0; i < 3; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(108, 118),
				Vec2(28, 28), obj->getPos(),
				Vec2(15, 15), Vec2(15, 15), 50, ang2 + 15 * (i - 1), 1, Group_GameObj::EnemyMissile);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	

	if (obj->getTimerCount() == 65)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		obj->setDestPos(obj->getPos() + Vec2(0, -500));
		((CEnemy*)self)->accMove(100, 0);
	}
}

void WriggleMissileAi01(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	Vec2 pos = obj->getPos();

	if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		((CMissile*)obj)->recycleMissile();
	}

	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 0.1)
	{
		obj->setTimer(0);
		obj->setTimerCount(obj->getTimerCount() + 1);
	}

	if (timerCount < 3)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}
	
	if (timerCount == 7)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setAngle(angle + 100);
		obj->setSpeed(30 + speed / 5);
	}
	if (timerCount > 8)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	obj = nullptr;
}

void WriggleMissileAi02(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	Vec2 pos = obj->getPos();

	if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		((CMissile*)obj)->recycleMissile();
	}

	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 0.1)
	{
		obj->setTimer(0);
		obj->setTimerCount(obj->getTimerCount() + 1);
	}

	if (timerCount < 3)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	if (timerCount == 7)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setAngle(angle - 100);
		obj->setSpeed(30 + speed / 5);
	}
	if (timerCount > 8)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	obj = nullptr;
}

void WriggleMissileAi03(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	Vec2 pos = obj->getPos();

	if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		((CMissile*)obj)->recycleMissile();
	}

	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 0.1)
	{
		obj->setTimer(0);
		obj->setTimerCount(obj->getTimerCount() + 1);
	}

	double speed = obj->getSpeed();
	double angle = obj->getAngle();
	obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));

	if (timerCount == 5)
	{
		obj->setSpeed(60);
	}

	obj = nullptr;
}

void WriggleMissileAi04(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	Vec2 pos = obj->getPos();

	if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		((CMissile*)obj)->recycleMissile();
	}

	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 0.1)
	{
		obj->setTimer(0);
		obj->setTimerCount(obj->getTimerCount() + 1);
	}

	if (timerCount < 5)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	if (timerCount == 7)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setAngle(angle - 100);
		obj->setSpeed(30 + speed / 5);
	}
	if (timerCount > 8)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	obj = nullptr;
}

void WriggleMissileAi05(DWORD_PTR self)
{
	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();
	Vec2 pos = obj->getPos();

	if (pos.x < 0 || pos.x > STAGE_WIDTH + 21 || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		((CMissile*)obj)->recycleMissile();
	}

	obj->setTimer(obj->getTimer() + DT());
	if (obj->getTimer() >= 0.1)
	{
		obj->setTimer(0);
		obj->setTimerCount(obj->getTimerCount() + 1);
	}

	if (timerCount < 5)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	if (timerCount == 7)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setAngle(angle + 100);
		obj->setSpeed(30 + speed / 5);
	}
	if (timerCount > 8)
	{
		double speed = obj->getSpeed();
		double angle = obj->getAngle();
		obj->setPos(pos + Vec2(speed * DT() * cos((angle - 90) * RADIAN), speed * DT() * sin((angle - 90) * RADIAN)));
	}

	obj = nullptr;
}


void WriggleAi02(DWORD_PTR self)
{
	if (g_gameState != Group_GameState::Play)
	{
		return;
	}

	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();

	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (timerCount == 1)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		int random1 = getRandomInt(0 + 100, STAGE_WIDTH - 100);
		int random2 = getRandomInt(100, STAGE_HEIGHT / 3);
		obj->setDestPos(Vec2(random1, random2));
	}

	if (timerCount == 10)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(50);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(50);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 12)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(100);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(100);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 14)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(125);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(125);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 16)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(150);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(150);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 20)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(50);
			missile->setAngle(105 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(50);
			missile->setAngle(75 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 22)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(100);
			missile->setAngle(105 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(100);
			missile->setAngle(75 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 24)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(125);
			missile->setAngle(105 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(125);
			missile->setAngle(75 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 26)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(150);
			missile->setAngle(105 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi05);
			missile->setSpeed(150);
			missile->setAngle(75 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	if (timerCount == 30)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(50);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(50);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 32)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(100);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(100);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 34)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(125);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(125);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 36)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(150);
			missile->setAngle(285 + i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
		for (int i = 0; i < 4; i++)
		{
			CMissile* missile = obj->createMissile(L"Missile.png", Vec2(124, 68),
				Vec2(12, 16), obj->getPos(),
				Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
			missile->setUpdateCallBack(WriggleMissileAi04);
			missile->setSpeed(150);
			missile->setAngle(255 - i * 10);
			missile->getCollider()->setType(Type_Collider::Circle);
		}
	}
	else if (timerCount == 37)
	{
		obj->setTimerCount(0);
	}
	if (g_boss->getHp() <= 0)
	{
		timerCount += 1;
		CSceneManager::getInstance()->getCurScene()->startDialog();
	}

	obj = nullptr;
}

void WriggleAi01(DWORD_PTR self)
{
	if (g_gameState != Group_GameState::Play)
	{
		return;
	}

	CGameObject* obj = (CGameObject*)self;
	int timerCount = obj->getTimerCount();

	if (obj->getDestPos() == obj->getPos())
	{
		obj->setTimer(obj->getTimer() + DT());
		if (obj->getTimer() >= 0.1)
		{
			obj->setTimer(0);
			obj->setTimerCount(obj->getTimerCount() + 1);
		}
	}

	if (timerCount == 10)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				CMissile* missile = obj->createMissile(L"Missile.png", Vec2(220, 68),
					Vec2(12, 16), obj->getPos(),
					Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
				missile->setUpdateCallBack(WriggleMissileAi01);
				missile->setAngle(15 + j * 15);
				missile->setSpeed(50 + i * 75);
				missile->getCollider()->setType(Type_Collider::Circle);
			}
		}
	}

	if (timerCount == 18)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				CMissile* missile = obj->createMissile(L"Missile.png", Vec2(139, 68),
					Vec2(12, 16), obj->getPos(),
					Vec2(12, 16), Vec2(12, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
				missile->setUpdateCallBack(WriggleMissileAi02);
				missile->setAngle(180 + j * 15);
				missile->setSpeed(50 + i * 75);
				missile->getCollider()->setType(Type_Collider::Circle);
			}
		}
	}

	if (timerCount == 23)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		int random1 = getRandomInt(-100, 100);
		int random2 = getRandomInt(-100, 10);
		obj->setDestPos(obj->getPos() + Vec2(random1, random2));
	}

	if (timerCount == 29)
	{
		obj->setTimerCount(obj->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.2f );
		
		double angle = getToPlayerAngle(obj);
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 6; i++)
			{
				CMissile* missile = obj->createMissile(L"Missile.png", Vec2(138, 52),
					Vec2(16, 16), obj->getPos(),
					Vec2(16, 16), Vec2(16, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
				missile->setUpdateCallBack(WriggleMissileAi03);
				missile->setAngle(angle - 20 + j * 20);
				missile->setSpeed(10 + i * 60);
				missile->getCollider()->setType(Type_Collider::Circle);

				CMissile* missile2 = obj->createMissile(L"Missile.png", Vec2(138, 52),
					Vec2(16, 16), obj->getPos(),
					Vec2(16, 16), Vec2(16, 16), 0, 180, 1, Group_GameObj::EnemyMissile);
				missile2->setUpdateCallBack(WriggleMissileAi03);
				missile2->setAngle(angle - 15 + j * 20);
				missile2->setSpeed(10 + i * 60);
				missile2->getCollider()->setType(Type_Collider::Circle);
			}
		}
	}

	if (timerCount == 85 || g_boss->getHp() <= 0)
	{
		timerCount += 1;
		CSceneManager::getInstance()->getCurScene()->startDialog();
		g_boss->setUpdateCallBack(WriggleAi02);
		g_boss->setHp(200);
		g_boss->setMaxHp(200);
		g_boss->setTimer(0);
		g_boss->setTimerCount(0);
	}
	
	obj = nullptr;
}


#pragma region update

void CScene_Stage01::update()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			if (getArrObj()[i][j]->getIsDelete() == false)
				getArrObj()[i][j]->update();
		}
	}

	if (KEY('E') == (UINT)Key_State::Tap)
	{
		g_isDeveloperMode = !g_isDeveloperMode;
	}

	if (KEY(VK_ESCAPE) == (UINT)Key_State::Tap)
	{
		if (g_gameState == Group_GameState::Play)
		{
			menuNum = 1;
			exitText->setIsRender(true);
			exitText->setColor(RGB(150, 150, 150));
			returnText->setIsRender(true);
			returnText->setColor(RGB(255, 255, 255));
			g_gameState = Group_GameState::Stop;
		}
			
		else if (g_gameState == Group_GameState::Stop)
		{
			exitText->setIsRender(false);
			returnText->setIsRender(false);
			g_gameState = Group_GameState::Play;
		}
	}

	if (g_gameState == Group_GameState::Stop)
	{
		if (KEY(VK_DOWN) == (UINT)Key_State::Tap)
		{
			vecMenu[menuNum]->setColor(RGB(150, 150, 150));
			menuNum += 1;
			if (menuNum >= 2)
				menuNum = 0;
			vecMenu[menuNum]->setColor(RGB(255, 255, 255));
		}
		else if (KEY(VK_UP) == (UINT)Key_State::Tap)
		{
			vecMenu[menuNum]->setColor(RGB(150, 150, 150));
			menuNum += -1;
			if (menuNum < 0)
				menuNum = 1;
			vecMenu[menuNum]->setColor(RGB(255, 255, 255));
		}

		if (KEY('Z') == (UINT)Key_State::Tap)
		{
			if (menuNum == 0)
			{
				CEventManager::getInstance()->changeScene(Group_Scene::Start);
			}
			else if (menuNum == 1)
			{
				exitText->setIsRender(false);
				returnText->setIsRender(false);
				g_gameState = Group_GameState::Play;
			}
		}
		else if (KEY('X') == (UINT)Key_State::Tap)
		{
			exitText->setIsRender(false);
			returnText->setIsRender(false);
			g_gameState = Group_GameState::Play;
		}
	}
	else if (g_gameState == Group_GameState::Dialog)
	{
		if (KEY('Z') == (UINT)Key_State::Tap)
		{
			nextDialog();
		}
	}

	if (g_gameState != Group_GameState::Play)
	{
		return;
	}

	timer += DT();
	if (timer >= 0.1)
	{
		timer = 0;
		timerCount += 1;
	}
	
	int random1 = 0;
	int random2 = 0;
	int random3 = 0;
	int random4 = 0;
	
	CEnemy* enemy = nullptr;
	//왼쪽 등장
	if (timerCount >= 1 && timerCount <= 20 && timerCount%8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(0 + random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi02);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//오른쪽 등장
	else if (timerCount >= 31 && timerCount <= 50 && timerCount % 8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		
		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH /2 + STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi03);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//좌측 원형공격
	else if (timerCount == 61)
	{
		timerCount += 1;
		random1 = getRandomInt(-30, 30);
		random4 = getRandomInt(0, 30);

		
		enemy = new CEnemy();
		enemy->setPos(Vec2(100 + random1, -10));
		enemy->setDestPos(Vec2(100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi04);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}

	//우측 원형공격
	else if (timerCount == 91)
	{
		timerCount += 1;
		random1 = getRandomInt(-30, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - 100 + random1, -10));
		enemy->setDestPos(Vec2(STAGE_WIDTH - 100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi04);
		enemy->setItemDrop(Group_Item::Life, 1);
		AddObject(enemy, Group_GameObj::Enemy);

	}
	//좌측 등장
	else if (timerCount >= 110 && timerCount <= 140 && timerCount % 8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(0 + random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi02);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//오른쪽 등장
	else if (timerCount >= 151 && timerCount <= 180 && timerCount % 8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 2 + STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi03);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//양쪽 원형 공격
	else if (timerCount == 190)
	{
		timerCount += 1;
		random1 = getRandomInt(-30, 30);
		random4 = getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(100 + random1, -10));
		enemy->setDestPos(Vec2(100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi04);
		enemy->setItemDrop(Group_Item::Spell, 2);
		AddObject(enemy, Group_GameObj::Enemy);

		random1 = getRandomInt(-30, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - 100 + random1, -10));
		enemy->setDestPos(Vec2(STAGE_WIDTH - 100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi04);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//양쪽 원형 공격 + 유도공격
	else if (timerCount == 225)
	{
		timerCount += 1;
		random1 = getRandomInt(-30, 30);
		random4 = getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(100 + random1, -10));
		enemy->setDestPos(Vec2(100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi05);
		enemy->setFixed(true);
		enemy->setItemDrop(Group_Item::Power, 1);
		AddObject(enemy, Group_GameObj::Enemy);

		random1 = getRandomInt(-30, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - 100 + random1, -10));
		enemy->setDestPos(Vec2(STAGE_WIDTH - 100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setFixed(true);
		enemy->setUpdateCallBack(enemyAi05);
		enemy->setItemDrop(Group_Item::Power, 1);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//좌측 등장
	else if (timerCount >= 235 && timerCount <= 265 && timerCount % 8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(0 + random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi02);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//오른쪽 등장
	else if (timerCount >= 266 && timerCount <= 296 && timerCount % 8 == 1)
	{
		timerCount += 1;
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 2 + STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi03);
		enemy->setItemDrop(Group_Item::Score, 2);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//좌우 등장
	else if (timerCount >= 297 && timerCount <= 315 && timerCount % 4 == 1)
	{
		timerCount += 1;

		if (timerCount == 302)
		{
			random1 = getRandomInt(-30, 30);
			random4 = getRandomInt(0, 30);

			enemy = new CEnemy();
			enemy->setPos(Vec2(100 + random1, -10));
			enemy->setDestPos(Vec2(100 + random1, STAGE_HEIGHT / 3 + random4));
			enemy->setMaxSpeed(300);
			enemy->setSpeed(100);
			enemy->setHp(10);
			enemy->setScale(Vec2(32, 32));
			enemy->setUpdateCallBack(enemyAi05);
			enemy->setFixed(true);
			AddObject(enemy, Group_GameObj::Enemy);

			random1 = getRandomInt(-30, 30);

			enemy = new CEnemy();
			enemy->setPos(Vec2(STAGE_WIDTH - 100 + random1, -10));
			enemy->setDestPos(Vec2(STAGE_WIDTH - 100 + random1, STAGE_HEIGHT / 3 + random4));
			enemy->setMaxSpeed(300);
			enemy->setSpeed(100);
			enemy->setHp(10);
			enemy->setScale(Vec2(32, 32));
			enemy->setFixed(true);
			enemy->setUpdateCallBack(enemyAi05);
			AddObject(enemy, Group_GameObj::Enemy);
		}
		
		random1 = getRandomInt(0, 10);
		random2 = getRandomInt(0, 200);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(-30 + random1, 50 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH + 150 + random1, 50 + random2));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(200);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		AddObject(enemy, Group_GameObj::Enemy);

		random1 = getRandomInt(0, 10);
		random2 = getRandomInt(0, 200);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH + 30 - random1, 50 + random2));
		enemy->setDestPos(Vec2(-100 + random1, 50 + random2));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(200);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		AddObject(enemy, Group_GameObj::Enemy);
	}
	//리글 등장
	else if (timerCount == 370)
	{
		hpBar->setIsRender(true);
		timerCount += 1;
		g_boss = new CEnemy();
		g_boss->setPos(Vec2(30, -30));
		g_boss->setDestPos(Vec2(STAGE_WIDTH / 2, STAGE_HEIGHT / 3));
		g_boss->setMaxSpeed(300);
		g_boss->setSpeed(200);
		g_boss->setHp(200);
		g_boss->setMaxHp(200);
		g_boss->setScale(Vec2(48, 64));
		g_boss->getCollider()->setColliderScale(Vec2(48, 64));
		g_boss->setImage(L"Boss.png");
		g_boss->addAnimation(L"stay", Vec2(560, 12), Vec2(48, 64), 0.2, 5, true);
		g_boss->addAnimation(L"moveleft", Vec2(560, 12), Vec2(48, 64), 0.2, 5, true);
		g_boss->addAnimation(L"moveright", Vec2(560, 12), Vec2(48, 64), 0.2, 5, true, true);
		g_boss->setUpdateCallBack(WriggleAi01);
		AddObject(g_boss, Group_GameObj::Enemy);
	}
}
#pragma endregion

void CScene_Stage01::render()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (vector<CGameObject*>::iterator iter = getArrObj()[i].begin(); iter != getArrObj()[i].end(); )
		{
			if ((*iter)->getIsDelete() == false)
			{
				if (g_isDeveloperMode == true)
				{
					if (i == (UINT)Group_GameObj::Enemy ||
						i == (UINT)Group_GameObj::Player || 
						i == (UINT)Group_GameObj::Item)
					{
						(*iter)->viewData();
					}
				}
				
				
				if ((*iter)->getIsRender() == true)
				{
					(*iter)->render();
				}
				iter++;
			}
			else
			{
				iter = getArrObj()[i].erase(iter);
			}
		}
	}
}

#pragma region textUpdate

void updateHighScore(DWORD_PTR self)
{
	if (g_highScore <= g_score)
	{
		string str = std::to_string(g_highScore);
		wstring w;
		w.assign(str.begin(), str.end());
		((CText*)self)->setText(w.c_str());
		g_highScore = g_score;
	}
}

void updateScore(DWORD_PTR self)
{
	string str = std::to_string(g_score);
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void updateLife(DWORD_PTR self)
{
	vector<CUI*> vec = ((CText*)self)->getChild();
	if (vec.size() < g_life)
	{
		CUI* life = new CUI();
		life->setPos(Vec2(((CText*)self)->getChild().size() * 30 + 50, 5));
		life->setScale(Vec2(30, 30));
		life->setImage(L"text2.png");
		life->setImagePos(Vec2(362, 89), Vec2(376, 103));

		((CText*)self)->AddChild(life);
	}
	else if (vec.size() > g_life)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			DELETEOBJECT(vec[i]);
		}
		((CText*)self)->getChild().clear();
	}
}

void updateSpell(DWORD_PTR self)
{
	vector<CUI*> vec = ((CText*)self)->getChild();
	if (vec.size() < g_spell)
	{
		CUI* spell = new CUI();
		spell->setPos(Vec2(((CText*)self)->getChild().size() * 30 + 50, 5));
		spell->setScale(Vec2(30, 30));
		spell->setImage(L"text2.png");
		spell->setImagePos(Vec2(378, 89), Vec2(392, 103));
		((CText*)self)->AddChild(spell);
	}
	else if( vec.size() > g_spell)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			DELETEOBJECT(vec[i]);
		}
		((CText*)self)->getChild().clear();
	}
}

void updatePower(DWORD_PTR self)
{
	string str = std::to_string(g_power);
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void updateGraze(DWORD_PTR self)
{
	string str = std::to_string(g_graze);
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void updatePoint(DWORD_PTR self)
{
	string str = std::to_string(g_point) + "/100";
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void updateTime(DWORD_PTR self)
{
	string str = std::to_string(g_time) + "/2500";
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void updateHpBar(DWORD_PTR self)
{
	if (g_boss == nullptr)
	{
		((CUI*)self)->setIsRender(false);
		return;
	}
		
	if (g_boss->getMaxHp() == 0)
	{
		((CUI*)self)->setIsRender(false);
		return;
	}
		
	CUI* ui = (CUI*)self;
	
	double per = g_boss->getHp() / g_boss->getMaxHp();
	string str = std::to_string(per);
	wstring w;
	w.assign(str.begin(), str.end());
	Logger::debug(w.c_str());
	ui->setScale(Vec2(STAGE_WIDTH * per, 10));
}
#pragma endregion

#pragma region Enter

void CScene_Stage01::Enter()
{
	for (int i = 0; i < sizeof(g_missile) / sizeof(CMissile*); i++)
	{
		if (g_missile[i] == nullptr)
		{
			g_missile[i] = new CMissile();
			g_missile[i]->setPos(Vec2(-49, -49));
			g_missile[i]->setScale(Vec2(0, 0));
			g_missile[i]->createCollider();
			g_missile[i]->getCollider()->setColliderScale(Vec2(0, 0));

			g_missile[i]->setSpeed(0);
			g_missile[i]->setAngle(0);
			g_missile[i]->setDamage(0);
			g_missile[i]->setIsUse(false);
			CREATEOBJECT(g_missile[i], Group_GameObj::EnemyMissile);
		}
	}

	timer = 0;
	timerCount = 0;

	g_gameState = Group_GameState::Play;
	dialogNum = 0;
	level = g_level;
	g_score = 0;
	g_life = 2;
	g_spell = 2;
	g_power = 0;
	g_graze = 0;
	g_point = 0;
	g_time = 0;
	g_bombUse = false;
	CPlayer::isSpell = false;
	CResourceManager::getInstance()->loadD2DImage(L"Boss.png", L"\\texture\\Boss.png");
	string str;
	wstring w;

	hpBar = new CUI();
	hpBar->setIsRender(true);
	hpBar->setPos(Vec2(20, 0));
	hpBar->setScale(Vec2(STAGE_WIDTH, 10));
	hpBar->setImage(L"background.png");
	hpBar->setImagePos(Vec2(160, 1400), Vec2(170, 1500));
	hpBar->setAlpha(0.9f);
	hpBar->setUpdateCallBack(updateHpBar);
	AddObject(hpBar, Group_GameObj::UI);


	exitText = new CText();
	exitText->setIsRender(false);
	exitText->setPos(Vec2(STAGE_WIDTH / 2, STAGE_HEIGHT / 2 - 20));
	exitText->setScale(Vec2(100, 50));
	exitText->setText(L"타이틀로");
	exitText->setSize(20);
	exitText->setColor(RGB(150, 150, 150));
	AddObject(exitText, Group_GameObj::UI);
	vecMenu.push_back(exitText);

	returnText = new CText();
	returnText->setIsRender(false);
	returnText->setPos(Vec2(STAGE_WIDTH / 2, STAGE_HEIGHT / 2 + 20));
	returnText->setScale(Vec2(100, 50));
	returnText->setText(L"계속");
	returnText->setSize(20);
	returnText->setColor(RGB(150, 150, 150));
	AddObject(returnText, Group_GameObj::UI);
	vecMenu.push_back(returnText);

	dialogPanel = new CPanelUI();
	dialogPanel->setIsRender(false);
	dialogPanel->setPos(Vec2(30 , STAGE_WIDTH - 50));
	dialogPanel->setScale(Vec2(STAGE_WIDTH - 20, STAGE_HEIGHT / 4));
	dialogPanel->setImage(L"background.png");
	dialogPanel->setImagePos(Vec2(730, 1540), Vec2(800, 1600));
	dialogPanel->setAlpha(0.5);
	AddObject(dialogPanel, Group_GameObj::UI);

	dialogText = new CText();
	dialogText->setIsRender(true);
	dialogText->setPos(Vec2(20, 0));
	dialogText->setScale(Vec2(STAGE_WIDTH - 50, 200));
	dialogText->setHeightAlignment(Type_TextHeightAlignment::Top);
	dialogText->setText(L"null");
	dialogText->setSize(30);
	dialogText->setColor(RGB(255, 255, 255));
	dialogPanel->AddChild(dialogText);

	dialogLeftChr = new CUI();
	dialogLeftChr->setIsRender(true);
	dialogLeftChr->setPos(Vec2(0, -100));
	dialogLeftChr->setScale(Vec2(100, 100));
	dialogLeftChr->setImage(L"RemiliaPortrait.png");
	dialogLeftChr->setImagePos(Vec2(0, 0), Vec2(0, 0));
	dialogLeftChr->setAlpha(1.0f);
	dialogPanel->AddChild(dialogLeftChr);
	

	dialogRightChr = new CUI();
	dialogRightChr->setIsRender(true);
	dialogRightChr->setPos(Vec2(STAGE_WIDTH - 20 - 100, -100));
	dialogRightChr->setScale(Vec2(100, 100));
	dialogRightChr->setImage(L"WrigglePortrait.png");
	dialogRightChr->setImagePos(Vec2(0, 0), Vec2(0, 0));
	dialogRightChr->setAlpha(1.0f);
	dialogPanel->AddChild(dialogRightChr);


	CSoundManager::getInstance()->addSound(L"stage1-1bgm.wav", L"stage1-1bgm.wav", true, true);
	CSoundManager::getInstance()->playMusic(L"stage1-1bgm.wav");

	CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));

	/*
	CEnemy* enemy = new CEnemy();
	enemy->setPos(Vec2(STAGE_WIDTH - 200, 200));
	enemy->setDestPos(Vec2(STAGE_WIDTH - 200, 200));
	enemy->setMaxSpeed(300);
	enemy->setSpeed(100);
	enemy->setHp(10000);
	enemy->setScale(Vec2(32, 32));
	AddObject(enemy, Group_GameObj::Enemy);
	enemy->setUpdateCallBack(enemyAi01);
	*/
	
	g_player = new CPlayer();
	g_player->setPos(Vec2(PL_STARTPOSX, PL_STARTPOSY));
	g_player->setScale(Vec2(64, 64));
	g_player->setIsRender(false);
	g_player->setHp(1);
	AddObject(g_player, Group_GameObj::Player);

	body = new CBody();
	body->setPos(Vec2(200, WS_HEIGHT - 50));
	body->setScale(Vec2(32, 48));
	AddObject(body, Group_GameObj::Body);

	CPanelUI* UIBackground = new CPanelUI();
	UIBackground->setPos(Vec2(0, 0));
	UIBackground->setScale(Vec2(WS_WIDTH, WS_HEIGHT));
	UIBackground->setImage(L"stagebackground.png");
	UIBackground->setImagePos(Vec2(255, 5125), Vec2(516, 5350));
	AddObject(UIBackground, Group_GameObj::Background);

	CPanelUI* stageBackground = new CPanelUI();
	stageBackground->setPos(Vec2(20, 10));
	stageBackground->setScale(Vec2(STAGE_WIDTH, STAGE_HEIGHT));
	stageBackground->setImage(L"stagebackground.png");
	stageBackground->setImagePos(Vec2(18, 38), Vec2(274, 294));
	UIBackground->AddChild(stageBackground);

	CUI* gname = new CPanelUI();
	gname->setPos(Vec2(500, 280));
	gname->setScale(Vec2(60, 150));
	gname->setImage(L"text2.png");
	gname->setImagePos(Vec2(420, 22), Vec2(540, 260));
	UIBackground->AddChild(gname);

	CPanelUI* nameBackground = new CPanelUI();
	nameBackground->setPos(Vec2(20, 10));
	nameBackground->setScale(Vec2(STAGE_WIDTH, STAGE_HEIGHT));
	nameBackground->setImage(L"stagebackground.png");
	nameBackground->setImagePos(Vec2(18, 38), Vec2(274, 294));
	UIBackground->AddChild(nameBackground);

	CUI* highScoreImage = new CUI();
	highScoreImage->setPos(Vec2(STAGE_WIDTH + 40, 20));
	highScoreImage->setScale(Vec2(40, 40));
	highScoreImage->setImage(L"text2.png");
	highScoreImage->setImagePos(Vec2(300, 88), Vec2(348, 104));
	UIBackground->AddChild(highScoreImage);

	str = std::to_string(g_highScore);
	w.assign(str.begin(), str.end());
	CText* highScoreText = new CText();
	highScoreText->setPos(Vec2(STAGE_WIDTH + 100, 25));
	highScoreText->setScale(Vec2(200, 30));
	highScoreText->setText(w.c_str());
	highScoreText->setSize(30);
	highScoreText->setUpdateCallBack(updateHighScore);
	highScoreText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(highScoreText);

	CUI* scoreImage = new CUI();
	scoreImage->setPos(Vec2(STAGE_WIDTH + 40, 50));
	scoreImage->setScale(Vec2(40, 40));
	scoreImage->setImage(L"text2.png");
	scoreImage->setImagePos(Vec2(300, 104), Vec2(348, 120));
	UIBackground->AddChild(scoreImage);

	CText* scoreText = new CText();
	scoreText->setPos(Vec2(STAGE_WIDTH + 100, 55));
	scoreText->setScale(Vec2(200, 30));
	scoreText->setText(L"0");
	scoreText->setSize(30);
	scoreText->setUpdateCallBack(updateScore);
	scoreText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(scoreText);

	CUI* lifeImage = new CUI();									//오브젝트 생성
	lifeImage->setPos(Vec2(STAGE_WIDTH + 40, 80));				//위치 설정
	lifeImage->setScale(Vec2(40, 40));							//크기 설정
	lifeImage->setImage(L"text2.png");							//이미지 설정
	lifeImage->setImagePos(Vec2(300, 120), Vec2(348, 136));		//이미지 크기 설정
	lifeImage->setUpdateCallBack(updateLife);					//update 내용 설정(ai, 동적연출)
	UIBackground->AddChild(lifeImage);							

	CUI* spellImage = new CUI();
	spellImage->setPos(Vec2(STAGE_WIDTH + 40, 110));
	spellImage->setScale(Vec2(40, 40));
	spellImage->setImage(L"text2.png");
	spellImage->setImagePos(Vec2(300, 136), Vec2(348, 152));
	spellImage->setUpdateCallBack(updateSpell);
	UIBackground->AddChild(spellImage);

	CUI* powerImage = new CUI();
	powerImage->setPos(Vec2(STAGE_WIDTH + 40, 140));
	powerImage->setScale(Vec2(40, 40));
	powerImage->setImage(L"text2.png");
	powerImage->setImagePos(Vec2(300, 152), Vec2(348, 168));
	UIBackground->AddChild(powerImage);

	CText* powerText = new CText();
	powerText->setPos(Vec2(STAGE_WIDTH + 100, 145));
	powerText->setScale(Vec2(200, 30));
	powerText->setText(L"0");
	powerText->setSize(30);
	powerText->setUpdateCallBack(updatePower);
	powerText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(powerText);

	CUI* grazeImage = new CUI();
	grazeImage->setPos(Vec2(STAGE_WIDTH + 40, 170));
	grazeImage->setScale(Vec2(40, 40));
	grazeImage->setImage(L"text2.png");
	grazeImage->setImagePos(Vec2(300, 168), Vec2(348, 184));
	UIBackground->AddChild(grazeImage);

	CText* grazeText = new CText();
	grazeText->setPos(Vec2(STAGE_WIDTH + 100, 175));
	grazeText->setScale(Vec2(200, 30));
	grazeText->setText(L"0");
	grazeText->setSize(30);
	grazeText->setUpdateCallBack(updateGraze);
	grazeText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(grazeText);

	CUI* pointImage = new CUI();
	pointImage->setPos(Vec2(STAGE_WIDTH + 40, 200));
	pointImage->setScale(Vec2(40, 40));
	pointImage->setImage(L"text2.png");
	pointImage->setImagePos(Vec2(300, 184), Vec2(348, 200));
	UIBackground->AddChild(pointImage);

	CText* pointText = new CText();
	pointText->setPos(Vec2(STAGE_WIDTH + 100, 205));
	pointText->setScale(Vec2(200, 30));
	pointText->setText(L"0");
	pointText->setSize(30);
	pointText->setUpdateCallBack(updatePoint);
	pointText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(pointText);

	CUI* timeImage = new CUI();
	timeImage->setPos(Vec2(STAGE_WIDTH + 40, 230));
	timeImage->setScale(Vec2(40, 40));
	timeImage->setImage(L"text2.png");
	timeImage->setImagePos(Vec2(300, 200), Vec2(348, 216));
	UIBackground->AddChild(timeImage);

	CText* timeText = new CText();
	timeText->setPos(Vec2(STAGE_WIDTH + 100, 235));
	timeText->setScale(Vec2(200, 30));
	timeText->setText(L"0");
	timeText->setSize(30);
	timeText->setUpdateCallBack(updateTime);
	timeText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(timeText);

	
	CUI* levelImage = new CUI();
	levelImage->setPos(Vec2(STAGE_WIDTH + 150, 260));
	levelImage->setScale(Vec2(80, 50));
	levelImage->setImage(L"text1.png");
	levelImage->setImagePos(Vec2(130 * ((g_level % 2) + 1) - 130, 194 + (48*(g_level/2))), Vec2(130*((g_level % 2) + 1), 194 + (48 * (g_level / 2 + 1))));
	UIBackground->AddChild(levelImage);
	
}
#pragma endregion

void CScene_Stage01::Exit()
{
	CSoundManager::getInstance()->stop(L"stage1-1bgm.wav");
	for (int i = 0; i < sizeof(g_missile) / sizeof(CMissile*); i++)
	{
		g_missile[i]->recycleMissile();
	}
	this->clearObject();
	g_boss = nullptr;
	exitText = nullptr;
	returnText = nullptr;
	hpBar = nullptr;
	vecMenu.clear();
}

int CScene_Stage01::getLevel()
{
	return level;
}

void CScene_Stage01::setLevel(int level)
{
	this->level = level;
}
