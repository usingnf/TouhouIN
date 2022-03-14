#include "pch.h"
#include "CScene_Stage01.h"
#include "CRemilia.h"




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
				(*iter)->render(hDC);
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
	//loadTile(L"test.tile");
	CCameraManager::getInstance()->setLookAt(Vec2(WS_WIDTH / 2, WS_HEIGHT / 2));

	
	CRemilia* remilia = new CRemilia();
	remilia->setPos(Vec2(500, 500));
	AddObject(remilia, Group_GameObj::Monster);
	
}

void CScene_Stage01::Exit()
{
	this->clearObject();
}