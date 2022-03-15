#include "pch.h"
#include "CScene_Stage01.h"
#include "CRemilia.h"
#include "CPanelUI.h"



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


void CScene_Stage01::Enter()
{
	CSoundManager::getInstance()->addSound(L"stage1-1bgm", L"stage1-1bgm.wav", true, true);
	CSoundManager::getInstance()->play(L"stage1-1bgm");

	CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));

	CRemilia* remilia = new CRemilia();
	remilia->setPos(Vec2(200, WS_HEIGHT - 50));
	AddObject(remilia, Group_GameObj::Monster);

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
	//AddObject(stageBackground, Group_GameObj::Background);

	/*
	CText* start = new CText();
	start->setPos(Vec2(0, 0));
	start->setScale(Vec2(500, 300));
	start->setImage(L"titlebackground.png");
	AddObject(start, Group_GameObj::Monster);
	*/
	
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
