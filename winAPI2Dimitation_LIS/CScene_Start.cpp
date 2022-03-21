#include "pch.h"
#include "CScene_Start.h"
#include "CPanelUI.h"
#include "CText.h"

CScene_Start::CScene_Start()
{
	title = nullptr;
	level = nullptr;
}

CScene_Start::~CScene_Start()
{

}

void CScene_Start::update()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			getArrObj()[i][j]->update();
		}
	}
	timer += DT();
	if (timerCount == 0)
	{
		if (timer >= 4)
		{
			timer = 0;
			timerCount = 30;
			if (left == true)
				left = false;
			else
				left = true;
		}
	}
	else
	{
		if (timer >= 0.05)
		{
			timer = 0;
			timerCount += -1;
			if (left == true)
			{
				vecMenu[0]->setPos(Vec2(vecMenu[0]->getPos().x - 1, vecMenu[0]->getPos().y));
				vecMenu[1]->setPos(Vec2(vecMenu[1]->getPos().x + 0.5, vecMenu[1]->getPos().y));
				vecMenu[3]->setPos(Vec2(vecMenu[3]->getPos().x + 0.1, vecMenu[3]->getPos().y));
				vecMenu[4]->setPos(Vec2(vecMenu[4]->getPos().x + 1, vecMenu[4]->getPos().y));
				vecMenu[5]->setPos(Vec2(vecMenu[5]->getPos().x - 0.5, vecMenu[5]->getPos().y));
				vecMenu[6]->setPos(Vec2(vecMenu[6]->getPos().x - 0.3, vecMenu[6]->getPos().y));
				vecMenu[7]->setPos(Vec2(vecMenu[7]->getPos().x + 0.1, vecMenu[7]->getPos().y));
				vecMenu[8]->setPos(Vec2(vecMenu[8]->getPos().x + 0.08, vecMenu[8]->getPos().y));
			}
			else
			{
				vecMenu[0]->setPos(Vec2(vecMenu[0]->getPos().x + 1, vecMenu[0]->getPos().y));
				vecMenu[1]->setPos(Vec2(vecMenu[1]->getPos().x - 0.5, vecMenu[1]->getPos().y));
				vecMenu[3]->setPos(Vec2(vecMenu[3]->getPos().x - 0.1, vecMenu[3]->getPos().y));
				vecMenu[4]->setPos(Vec2(vecMenu[4]->getPos().x - 1, vecMenu[4]->getPos().y));
				vecMenu[5]->setPos(Vec2(vecMenu[5]->getPos().x + 0.5, vecMenu[5]->getPos().y));
				vecMenu[6]->setPos(Vec2(vecMenu[6]->getPos().x + 0.3, vecMenu[6]->getPos().y));
				vecMenu[7]->setPos(Vec2(vecMenu[7]->getPos().x - 0.1, vecMenu[7]->getPos().y));
				vecMenu[8]->setPos(Vec2(vecMenu[8]->getPos().x - 0.08, vecMenu[8]->getPos().y));
			}
			
		}
	}

	if (g_isDeveloperMode == true)
	{
		if (KEY('R') == (UINT)Key_State::Tap)
		{
			CHANGESCENE(Group_Scene::Stage_01);
		}
		if (KEY('Y') == (UINT)Key_State::Tap)
		{
			CHANGESCENE(Group_Scene::Result);
		}
	}

	if (KEY('T') == (UINT)Key_State::Tap)
	{
		g_isDeveloperMode = !g_isDeveloperMode;
	}


	if (KEY(VK_DOWN) == (UINT)Key_State::Tap)
	{
		if (title->getIsRender() == true)
		{
			vecMenu[menuIndex]->setColor(RGB(150, 150, 150));
			menuIndex += 1;
			if (menuIndex == 1)
				menuIndex += 1;
			if (menuIndex == 2)
				menuIndex += 1;
			if (menuIndex >= vecMenu.size())
				menuIndex = 0;
			vecMenu[menuIndex]->setColor(RGB(255, 255, 255));
		}
		else
		{
			vecLevel[menuIndex]->setColor(RGB(150, 150, 150));
			menuIndex += 1;
			if (menuIndex >= vecLevel.size())
				menuIndex = 0;
			vecLevel[menuIndex]->setColor(RGB(255, 255, 255));
		}
		
	}
	if (KEY(VK_UP) == (UINT)Key_State::Tap)
	{
		if (title->getIsRender() == true)
		{
			vecMenu[menuIndex]->setColor(RGB(150, 150, 150));
			menuIndex += -1;
			if (menuIndex < 0)
				menuIndex = vecMenu.size() - 1;
			if (menuIndex == 2)
				menuIndex += -1;
			if (menuIndex == 1)
				menuIndex += -1;
			vecMenu[menuIndex]->setColor(RGB(255, 255, 255));
		}
		else
		{
			vecLevel[menuIndex]->setColor(RGB(150, 150, 150));
			menuIndex += -1;
			if (menuIndex < 0)
				menuIndex = vecLevel.size() - 1;
			vecLevel[menuIndex]->setColor(RGB(255, 255, 255));
		}
		
	}

	if (KEY('Z') == (UINT)Key_State::Tap)
	{
		CSoundManager::getInstance()->addSound(L"se_ok00.wav", L"se_ok00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_ok00.wav");
		if (title->getIsRender() == true)
		{
			if (menuIndex == 0)
			{
				title->setIsRender(false);
				level->setIsRender(true);
				menuIndex = 1;
				//CHANGESCENE(Group_Scene::Stage_01);
			}
			else if (menuIndex == 1)
			{

			}
			else if (menuIndex == 8)
			{
				PostQuitMessage(0);
			}
		}
		else
		{
			g_level = menuIndex;
			CHANGESCENE(Group_Scene::Stage_01);
		}
	}

	if (KEY('X') == (UINT)Key_State::Tap)
	{
		CSoundManager::getInstance()->addSound(L"se_cancel00.wav", L"se_cancel00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_cancel00.wav");
		if (title->getIsRender() == true)
		{
			
		}
		else
		{
			title->setIsRender(true);
			level->setIsRender(false);
			menuIndex = 0;
		}
	}
}

void CScene_Start::render(HDC& hDC)
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (vector<CGameObject*>::iterator iter = getArrObj()[i].begin(); iter != getArrObj()[i].end(); )
		{
			if ((*iter)->getIsDelete() == false )
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

void CScene_Start::Enter()
{
	timer = 0;
	menuIndex = 0;
	vecMenu.clear();

	CSoundManager::getInstance()->addSound(L"titlebgm.wav", L"titlebgm.wav", true, true);
	CSoundManager::getInstance()->play(L"titlebgm.wav");

	title = new CPanelUI();
	title->setPos(Vec2(0, 0));
	title->setScale(Vec2(WS_WIDTH, WS_HEIGHT));
	title->setImage(L"titlebackground.png");
	AddObject(title, Group_GameObj::Background);
	title->setIsRender(true);

	CPanelUI* gname = new CPanelUI();
	gname->setPos(Vec2(480, 20));
	gname->setScale(Vec2(130, 400));
	gname->setImage(L"text2.png");
	gname->setImagePos(Vec2(420, 22), Vec2(540, 260));
	title->AddChild(gname);

	int top = 120;
	int space = 28;
	CText* start = new CText();
	start->setPos(Vec2(100, top + space * 1));
	start->setScale(Vec2(300, 100));
	start->setText(L"Start");
	start->setSize(30);
	start->setColor(RGB(255,255,255));
	title->AddChild(start);
	vecMenu.push_back(start);
	
	CText* extraStart = new CText();
	extraStart->setPos(Vec2(60, top + space * 2));
	extraStart->setScale(Vec2(300, 100));
	extraStart->setText(L"Extra Start");
	extraStart->setSize(30);
	extraStart->setColor(RGB(50, 50, 50));
	title->AddChild(extraStart);
	vecMenu.push_back(extraStart);
	
	CText* spellPractice = new CText();
	spellPractice->setPos(Vec2(70, top + space * 3));
	spellPractice->setScale(Vec2(300, 100));
	spellPractice->setText(L"Spell Practice");
	spellPractice->setSize(30);
	spellPractice->setColor(RGB(50, 50, 50));
	title->AddChild(spellPractice);
	vecMenu.push_back(spellPractice);
	
	CText* practiceStart = new CText();
	practiceStart->setPos(Vec2(65, top + space * 4));
	practiceStart->setScale(Vec2(300, 100));
	practiceStart->setText(L"Practice Start");
	practiceStart->setSize(30);
	practiceStart->setColor(RGB(150, 150, 150));
	title->AddChild(practiceStart);
	vecMenu.push_back(practiceStart);
	
	CText* replay = new CText();
	replay->setPos(Vec2(40, top + space * 5));
	replay->setScale(Vec2(300, 100));
	replay->setText(L"Replay");
	replay->setSize(30);
	replay->setColor(RGB(150, 150, 150));
	title->AddChild(replay);
	vecMenu.push_back(replay);
	
	CText* result = new CText();
	result->setPos(Vec2(110, top + space * 6));
	result->setScale(Vec2(300, 100));
	result->setText(L"Result");
	result->setSize(30);
	result->setColor(RGB(150, 150, 150));
	title->AddChild(result);
	vecMenu.push_back(result);

	CText* musicRoom = new CText();
	musicRoom->setPos(Vec2(100, top + space * 7));
	musicRoom->setScale(Vec2(300, 100));
	musicRoom->setText(L"Music Room");
	musicRoom->setSize(30);
	musicRoom->setColor(RGB(150, 150, 150));
	title->AddChild(musicRoom);
	vecMenu.push_back(musicRoom);

	CText* option = new CText();
	option->setPos(Vec2(40, top + space * 8));
	option->setScale(Vec2(300, 100));
	option->setText(L"Option");
	option->setSize(30);
	option->setColor(RGB(150, 150, 150));
	title->AddChild(option);
	vecMenu.push_back(option);

	CText* quit = new CText();
	quit->setPos(Vec2(55, top + space * 9));
	quit->setScale(Vec2(300, 100));
	quit->setText(L"Quit");
	quit->setSize(30);
	quit->setColor(RGB(150, 150, 150));
	title->AddChild(quit);
	vecMenu.push_back(quit);
	
	level = new CPanelUI();
	level->setPos(Vec2(0, 0));
	level->setScale(Vec2(WS_WIDTH, WS_HEIGHT));
	level->setImage(L"levelbackground.png");
	AddObject(level, Group_GameObj::Background);
	level->setIsRender(false);

	top = -20;
	space = 90;
	CText* levelText = new CText();
	levelText->setPos(Vec2(WS_WIDTH / 2 - 100, 10));
	levelText->setScale(Vec2(500, 50));
	levelText->setText(L"Level Choose");
	levelText->setSize(40);
	levelText->setColor(RGB(50, 255, 255));
	level->AddChild(levelText);

	CText* easy = new CText();
	easy->setPos(Vec2(WS_WIDTH/2 - 50, top + space * 1));
	easy->setScale(Vec2(300, 60));
	easy->setText(L"Easy");
	easy->setSize(60);
	easy->setColor(RGB(150, 150, 150));
	level->AddChild(easy);
	vecLevel.push_back(easy);

	CText* normal = new CText();
	normal->setPos(Vec2(WS_WIDTH / 2 - 50, top + space * 2));
	normal->setScale(Vec2(300, 60));
	normal->setText(L"Normal");
	normal->setSize(60);
	normal->setColor(RGB(255, 255, 255));
	level->AddChild(normal);
	vecLevel.push_back(normal);

	CText* hard = new CText();
	hard->setPos(Vec2(WS_WIDTH / 2 - 50, top + space * 3));
	hard->setScale(Vec2(300, 60));
	hard->setText(L"Hard");
	hard->setSize(60);
	hard->setColor(RGB(150, 150, 150));
	level->AddChild(hard);
	vecLevel.push_back(hard);

	CText* lunatic = new CText();
	lunatic->setPos(Vec2(WS_WIDTH / 2 - 50, top + space * 4));
	lunatic->setScale(Vec2(300, 100));
	lunatic->setText(L"Lunatic");
	lunatic->setSize(60);
	lunatic->setColor(RGB(150, 150, 150));
	level->AddChild(lunatic);
	vecLevel.push_back(lunatic);
}

void CScene_Start::Exit()
{
	CSoundManager::getInstance()->stop(L"titlebgm.wav");
	this->clearObject();
}
