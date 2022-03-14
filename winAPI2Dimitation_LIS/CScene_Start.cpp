#include "pch.h"
#include "CScene_Start.h"

CScene_Start::CScene_Start()
{
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

	if (KEY('R') == (UINT)Key_State::Tap)
	{
		CHANGESCENE(Group_Scene::Stage_01);
		//CSceneManager::getInstance()->changeScene(Group_Scene::Stage_01);
	}
	if (KEY('T') == (UINT)Key_State::Tap)
	{
		CHANGESCENE(Group_Scene::Stage_Tile);
	}
}

void CScene_Start::render(HDC& hDC)
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			getArrObj()[i][j]->render(hDC);
		}
	}
}

void CScene_Start::Enter()
{
	//loadTile(L"tile\\test.tile");
}

void CScene_Start::Exit()
{
	//clearObject();
}
