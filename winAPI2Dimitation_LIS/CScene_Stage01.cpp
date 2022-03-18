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
}

CScene_Stage01::~CScene_Stage01()
{
}

void enemyAi01(DWORD_PTR self)
{
	((CGameObject*)self)->setTimer(((CGameObject*)self)->getTimer() + DT());
	if (((CGameObject*)self)->getTimer() >= 3)
	{
		((CGameObject*)self)->setTimer(0);
		//action
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.5f);
		((CGameObject*)self)->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), ((CGameObject*)self)->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, 170 + rand() % 20, 1, Group_GameObj::EnemyMissile);
	}
}

void enemyAi02(DWORD_PTR self)
{
	if (((CGameObject*)self)->getDestPos() == ((CGameObject*)self)->getPos())
	{
		((CGameObject*)self)->setTimer(((CGameObject*)self)->getTimer() + DT());
		if (((CGameObject*)self)->getTimer() >= 0.1)
		{
			((CGameObject*)self)->setTimer(0);
			((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		}
	}

	if (((CGameObject*)self)->getTimerCount() % 5 == 1)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.5f);

		double angle = getToPlayerAngle((CGameObject*)self);

		((CGameObject*)self)->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), ((CGameObject*)self)->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, angle + getRandomInt(-10, 10), 1, Group_GameObj::EnemyMissile);
	}

	if (((CGameObject*)self)->getTimerCount() == 8)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		((CGameObject*)self)->setDestPos(((CGameObject*)self)->getPos() + Vec2(-50, -500));
		((CEnemy*)self)->accMove(10, 50);
	}	
}

void enemyAi03(DWORD_PTR self)
{
	if (((CGameObject*)self)->getDestPos() == ((CGameObject*)self)->getPos())
	{
		((CGameObject*)self)->setTimer(((CGameObject*)self)->getTimer() + DT());
		if (((CGameObject*)self)->getTimer() >= 0.1)
		{
			((CGameObject*)self)->setTimer(0);
			((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		}
	}

	if (((CGameObject*)self)->getTimerCount() % 5 == 1)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.5f);

		double angle = getToPlayerAngle((CGameObject*)self);

		((CGameObject*)self)->createMissile(L"Missile.png", Vec2(108, 118),
			Vec2(28, 28), ((CGameObject*)self)->getPos(),
			Vec2(30, 30), Vec2(30, 30), 200, angle + getRandomInt(-10, 10), 1, Group_GameObj::EnemyMissile);
	}

	if (((CGameObject*)self)->getTimerCount() == 8)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		((CGameObject*)self)->setDestPos(((CGameObject*)self)->getPos() + Vec2(50, -500));
		((CEnemy*)self)->accMove(10, 50);
	}
}

void enemyAi04(DWORD_PTR self)
{
	if (((CGameObject*)self)->getDestPos() == ((CGameObject*)self)->getPos())
	{
		((CGameObject*)self)->setTimer(((CGameObject*)self)->getTimer() + DT());
		if (((CGameObject*)self)->getTimer() >= 0.1)
		{
			((CGameObject*)self)->setTimer(0);
			((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		}
	}

	if (((CGameObject*)self)->getTimerCount() % 30 == 1)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		CSoundManager::getInstance()->addSound(L"se_tan00.wav", L"se_tan00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_tan00.wav", 0.5f);

		for (int i = 0; i < 36; i++)
		{
			((CGameObject*)self)->createMissile(L"Missile.png", Vec2(108, 118),
				Vec2(28, 28), ((CGameObject*)self)->getPos(),
				Vec2(20, 20), Vec2(20, 20), 200, 10*i, 1, Group_GameObj::EnemyMissile);
		}	
	}

	if (((CGameObject*)self)->getTimerCount() == 60)
	{
		((CGameObject*)self)->setTimerCount(((CGameObject*)self)->getTimerCount() + 1);
		((CGameObject*)self)->setDestPos(((CGameObject*)self)->getPos() + Vec2(0, -500));
		((CEnemy*)self)->accMove(100, 0);
	}
}

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

	if (KEY('R') == (UINT)Key_State::Tap)
	{
		CHANGESCENE(Group_Scene::Start);
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
	if (timerCount >= 1 && timerCount <= 20 && timerCount%8 == 1)
	{
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		timerCount += 1;
		enemy = new CEnemy();
		enemy->setPos(Vec2(0 + random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi02);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	else if (timerCount >= 31 && timerCount <= 50 && timerCount % 8 == 1)
	{
		random1 = getRandomInt(0, 50);
		random2 = getRandomInt(0, 20);
		random3 = -getRandomInt(0, 30);
		random4 = -getRandomInt(0, 30);

		timerCount += 1;
		enemy = new CEnemy();
		enemy->setPos(Vec2(STAGE_WIDTH - random1, -10 + random2));
		enemy->setDestPos(Vec2(STAGE_WIDTH /2 + STAGE_WIDTH / 3 + random3, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi03);
		AddObject(enemy, Group_GameObj::Enemy);
	}
	else if (timerCount == 61)
	{
		random1 = getRandomInt(-30, 30);
		random4 = getRandomInt(0, 30);

		timerCount += 1;
		enemy = new CEnemy();
		enemy->setPos(Vec2(100 + random1, -10));
		enemy->setDestPos(Vec2(100 + random1, STAGE_HEIGHT / 3 + random4));
		enemy->setMaxSpeed(300);
		enemy->setSpeed(100);
		enemy->setHp(10);
		enemy->setScale(Vec2(32, 32));
		enemy->setUpdateCallBack(enemyAi04);
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
		AddObject(enemy, Group_GameObj::Enemy);
	}

}

void CScene_Stage01::render(HDC& hDC)
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (vector<CGameObject*>::iterator iter = getArrObj()[i].begin(); iter != getArrObj()[i].end(); )
		{
			if ((*iter)->getIsDelete() == false)
			{
				if ((*iter)->getIsRender() == true)
				{
					(*iter)->render(hDC);
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

void CScene_Stage01::Enter()
{
	timer = 0;
	timerCount = 0;

	level = g_level;
	g_highScore = 100;
	g_score = 0;
	g_life = 2;
	g_spell = 2;
	g_power = 0;
	g_graze = 0;
	g_point = 0;
	g_time = 0;

	CSoundManager::getInstance()->addSound(L"stage1-1bgm.wav", L"stage1-1bgm.wav", true, true);
	CSoundManager::getInstance()->play(L"stage1-1bgm.wav");

	CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));

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

	CText* highScoreText = new CText();
	highScoreText->setPos(Vec2(STAGE_WIDTH + 100, 25));
	highScoreText->setScale(Vec2(200, 30));
	string str = std::to_string(g_highScore);
	wstring w;
	w.assign(str.begin(), str.end());
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

	CUI* lifeImage = new CUI();
	lifeImage->setPos(Vec2(STAGE_WIDTH + 40, 80));
	lifeImage->setScale(Vec2(40, 40));
	lifeImage->setImage(L"text2.png");
	lifeImage->setImagePos(Vec2(300, 120), Vec2(348, 136));
	lifeImage->setUpdateCallBack(updateLife);
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

void CScene_Stage01::Exit()
{
	CSoundManager::getInstance()->stop(L"stage1-1bgm.wav");
	this->clearObject();
}

int CScene_Stage01::getLevel()
{
	return level;
}

void CScene_Stage01::setLevel(int level)
{
	this->level = level;
}
