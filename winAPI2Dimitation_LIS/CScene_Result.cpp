#include "pch.h"
#include "CScene_Result.h"
#include "CPanelUI.h"
#include "CText.h"


CScene_Result::CScene_Result()
{
	
}

CScene_Result::~CScene_Result()
{

}

void CScene_Result::update()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			getArrObj()[i][j]->update();
		}
	}
	
	if (KEY('Z') == (UINT)Key_State::Tap)
	{
		CSoundManager::getInstance()->addSound(L"se_ok00.wav", L"se_ok00.wav", false, false);
		CSoundManager::getInstance()->play(L"se_ok00.wav");
		CHANGESCENE(Group_Scene::Start);
	}
}

void CScene_Result::render()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (vector<CGameObject*>::iterator iter = getArrObj()[i].begin(); iter != getArrObj()[i].end(); )
		{
			if ((*iter)->getIsDelete() == false)
			{
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

void CScene_Result::Enter()
{
	saveHighScore();

	CPanelUI* title = new CPanelUI();
	title->setPos(Vec2(0, 0));
	title->setScale(Vec2(WS_WIDTH, WS_HEIGHT));
	title->setImage(L"background.png");
	title->setImagePos(Vec2(704, 578), Vec2(1343, 1057));
	AddObject(title, Group_GameObj::Background);
	title->setIsRender(true);

	int top = 50;
	int space = 28;
	int left = 50;
	CText* result = new CText();
	result->setPos(Vec2(180, top + space * 1));
	result->setScale(Vec2(200, 50));
	result->setText(L"ÇÃ·¹ÀÌ °á°ú");
	result->setSize(25);
	result->setColor(RGB(255, 255, 255));
	title->AddChild(result);

	
	CText* score = new CText();
	score->setPos(Vec2(left, top + space * 2));
	score->setScale(Vec2(100, 50));
	score->setText(L"ÃÖÁ¾ Á¡¼ö");
	score->setSize(18);
	score->setColor(RGB(255, 255, 255));
	title->AddChild(score);
	
	CText* score2 = new CText();
	score2->setPos(Vec2(left + 350, top + space * 2));
	score2->setScale(Vec2(100, 50));
	string str = std::to_string(g_score);
	wstring w;
	w.assign(str.begin(), str.end());
	score2->setText(w.c_str());
	score2->setSize(18);
	score2->setColor(RGB(255, 255, 255));
	title->AddChild(score2);
	
	CText* level = new CText();
	level->setPos(Vec2(left, top + space * 3));
	level->setScale(Vec2(100, 50));
	level->setText(L"³­ÀÌµµ");
	level->setSize(18);
	level->setColor(RGB(255, 255, 255));
	title->AddChild(level);
	CText* level2 = new CText();
	level2->setPos(Vec2(left + 350, top + space * 3));
	level2->setScale(Vec2(100, 50));
	if (g_level == 0)
	{
		level2->setText(L"Easy");
	}
	else if (g_level == 1)
	{
		level2->setText(L"Normal");
	}
	else if (g_level == 2)
	{
		level2->setText(L"Hard");
	}
	else if (g_level == 3)
	{
		level2->setText(L"Lunatic");
	}
	else
	{
		level2->setText(L"None");
	}
	level2->setSize(18);
	level2->setColor(RGB(255, 255, 255));
	title->AddChild(level2);

	CText* progress = new CText();
	progress->setPos(Vec2(left, top + space * 4));
	progress->setScale(Vec2(100, 50));
	progress->setText(L"°ÔÀÓ ÁøÇà·ü");
	progress->setSize(18);
	progress->setColor(RGB(255, 255, 255));
	title->AddChild(progress);
	CText* progress2 = new CText();
	progress2->setPos(Vec2(left + 350, top + space * 4));
	progress2->setScale(Vec2(100, 50));
	str = std::to_string(g_progress) + "%";
	w.assign(str.begin(), str.end());
	progress2->setText(w.c_str());
	progress2->setSize(18);
	progress2->setColor(RGB(255, 255, 255));
	title->AddChild(progress2);

	CText* continue1 = new CText();
	continue1->setPos(Vec2(left, top + space * 5));
	continue1->setScale(Vec2(100, 50));
	continue1->setText(L"ÄÁÆ¼´º È½¼ö");
	continue1->setSize(18);
	continue1->setColor(RGB(255, 255, 255));
	title->AddChild(continue1);
	CText* continue2 = new CText();
	continue2->setPos(Vec2(left + 350, top + space * 5));
	continue2->setScale(Vec2(100, 50));
	str = std::to_string(g_continue);
	w.assign(str.begin(), str.end());
	continue2->setText(w.c_str());
	continue2->setSize(18);
	continue2->setColor(RGB(255, 255, 255));
	title->AddChild(continue2);

	CText* miss = new CText();
	miss->setPos(Vec2(left, top + space * 6));
	miss->setScale(Vec2(100, 50));
	miss->setText(L"¹Ì½º È½¼ö");
	miss->setSize(18);
	miss->setColor(RGB(255, 255, 255));
	title->AddChild(miss);
	CText* miss2 = new CText();
	miss2->setPos(Vec2(left + 350, top + space * 6));
	miss2->setScale(Vec2(100, 50));
	str = std::to_string(g_miss);
	w.assign(str.begin(), str.end());
	miss2->setText(w.c_str());
	miss2->setSize(18);
	miss2->setColor(RGB(255, 255, 255));
	title->AddChild(miss2);

	CText* bomb = new CText();
	bomb->setPos(Vec2(left, top + space * 7));
	bomb->setScale(Vec2(200, 50));
	bomb->setText(L"bomb »ç¿ëÈ½¼ö");
	bomb->setSize(18);
	bomb->setColor(RGB(255, 255, 255));
	title->AddChild(bomb);
	CText* bomb2 = new CText();
	bomb2->setPos(Vec2(left + 350, top + space * 7));
	bomb2->setScale(Vec2(100, 50));
	str = std::to_string(g_bombUse);
	w.assign(str.begin(), str.end());
	bomb2->setText(w.c_str());
	bomb2->setSize(18);
	bomb2->setColor(RGB(255, 255, 255));
	title->AddChild(bomb2);

	CText* bonus = new CText();
	bonus->setPos(Vec2(left, top + space * 8));
	bonus->setScale(Vec2(300, 50));
	bonus->setText(L"½ºÆçÄ«µå º¸³Ê½º È¹µæ È½¼ö");
	bonus->setSize(18);
	bonus->setColor(RGB(255, 255, 255));
	title->AddChild(bonus);
	CText* bonus2 = new CText();
	bonus2->setPos(Vec2(left + 350, top + space * 8));
	bonus2->setScale(Vec2(100, 50));
	str = std::to_string(g_spellBonus);
	w.assign(str.begin(), str.end());
	bonus2->setText(w.c_str());
	bonus2->setSize(18);
	bonus2->setColor(RGB(255, 255, 255));
	title->AddChild(bonus2);

	CText* omittion = new CText();
	omittion->setPos(Vec2(left, top + space * 9));
	omittion->setScale(Vec2(100, 50));
	omittion->setText(L"Ã³¸® ´©¶ô·ü");
	omittion->setSize(18);
	omittion->setColor(RGB(255, 255, 255));
	title->AddChild(omittion);
	CText* omittion2 = new CText();
	omittion2->setPos(Vec2(left + 350, top + space * 9));
	omittion2->setScale(Vec2(100, 50));
	str = std::to_string(g_omission);
	w.assign(str.begin(), str.end());
	omittion2->setText(w.c_str());
	omittion2->setSize(18);
	omittion2->setColor(RGB(255, 255, 255));
	title->AddChild(omittion2);
}

void CScene_Result::Exit()
{
	CSoundManager::getInstance()->stop(L"titlebgm.wav");
	this->clearObject();
}

void CScene_Result::saveHighScore()
{
	wstring filePath = CPathManager::getInstance()->getContentRelativePath();
	filePath += L"\\score.dat";
	FILE* file = nullptr;

	_wfopen_s(&file, filePath.c_str(), L"wb");
	if (file == nullptr)
		return;

	int score = g_highScore;

	fwrite(&score, sizeof(int), 1, file);

	fclose(file);
}