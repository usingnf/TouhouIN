#include "pch.h"
#include "CScene_Stage01.h"
#include "CRemilia.h"
#include "CPanelUI.h"
#include "CPlayer.h"
#include "CBody.h"
#include "CEnemy.h"
#include "CText.h"



CScene_Stage01::CScene_Stage01()
{
}

CScene_Stage01::~CScene_Stage01()
{
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

	if (body != nullptr && player != nullptr)
	{
		this->body->setPos(this->player->getPos());
	}

	if (KEY('R') == (UINT)Key_State::Tap)
	{
		CHANGESCENE(Group_Scene::Start);
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

void updateScore(DWORD_PTR self)
{
	string str = std::to_string(g_score);
	wstring w;
	w.assign(str.begin(), str.end());
	((CText*)self)->setText(w.c_str());
}

void CScene_Stage01::Enter()
{
	level = g_level;
	g_score = 0;

	CSoundManager::getInstance()->addSound(L"stage1-1bgm", L"stage1-1bgm.wav", true, true);
	CSoundManager::getInstance()->play(L"stage1-1bgm");

	CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));

	player = new CPlayer();
	player->setPos(Vec2(200, WS_HEIGHT - 50));
	AddObject(player, Group_GameObj::Player);
	body = new CBody();
	body->setPos(Vec2(200, WS_HEIGHT - 50));
	AddObject(body, Group_GameObj::Body);

	CEnemy* enemy = new CEnemy();
	enemy->setPos(Vec2(200, 200));
	enemy->setDestPos(Vec2(200, 200));
	enemy->setMaxSpeed(300);
	enemy->setHp(2);
	enemy->setScale(Vec2(WS_WIDTH, WS_HEIGHT));
	AddObject(enemy, Group_GameObj::Enemy);

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

	CUI* highScoreImage = new CUI();
	highScoreImage->setPos(Vec2(STAGE_WIDTH + 40, 20));
	highScoreImage->setScale(Vec2(40, 40));
	highScoreImage->setImage(L"text2.png");
	highScoreImage->setImagePos(Vec2(300, 88), Vec2(348, 104));
	UIBackground->AddChild(highScoreImage);

	CText* highScoreText = new CText();
	highScoreText->setPos(Vec2(STAGE_WIDTH + 100, 25));
	highScoreText->setScale(Vec2(200, 30));
	highScoreText->setText(L"0");
	highScoreText->setSize(30);
	highScoreText->setUpdateCallBack(updateScore);
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
	UIBackground->AddChild(lifeImage);

	CText* lifeText = new CText();
	lifeText->setPos(Vec2(STAGE_WIDTH + 100, 85));
	lifeText->setScale(Vec2(200, 30));
	lifeText->setText(L"0");
	lifeText->setSize(30);
	lifeText->setUpdateCallBack(updateScore);
	lifeText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(lifeText);

	CUI* spellImage = new CUI();
	spellImage->setPos(Vec2(STAGE_WIDTH + 40, 110));
	spellImage->setScale(Vec2(40, 40));
	spellImage->setImage(L"text2.png");
	spellImage->setImagePos(Vec2(300, 136), Vec2(348, 152));
	UIBackground->AddChild(spellImage);

	CText* spellText = new CText();
	spellText->setPos(Vec2(STAGE_WIDTH + 100, 115));
	spellText->setScale(Vec2(200, 30));
	spellText->setText(L"0");
	spellText->setSize(30);
	spellText->setUpdateCallBack(updateScore);
	spellText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(spellText);

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
	powerText->setUpdateCallBack(updateScore);
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
	grazeText->setUpdateCallBack(updateScore);
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
	pointText->setUpdateCallBack(updateScore);
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
	timeText->setUpdateCallBack(updateScore);
	timeText->setColor(RGB(255, 255, 255));
	UIBackground->AddChild(timeText);
	
}

void CScene_Stage01::Exit()
{
	CSoundManager::getInstance()->stop(L"stage1-1bgm");
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
