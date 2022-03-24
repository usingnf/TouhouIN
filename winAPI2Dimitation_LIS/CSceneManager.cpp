#include "pch.h"
#include "CScene_Start.h"
#include "CScene_Stage01.h"
#include "CScene_Tile.h"
#include "CScene_Result.h"

CSceneManager::CSceneManager()
{
	for (int i = 0; i < (UINT)Group_Scene::Size; i++)
	{
		arrScene[i] = nullptr;
	}
	curScene = nullptr;
}

CSceneManager::~CSceneManager()
{
	for (int i = 0; i < (UINT)Group_Scene::Size; i++)
	{
		if (arrScene[i] != nullptr)
		{
			delete arrScene[i];
			arrScene[i] = nullptr;
		}	
	}
}

void CSceneManager::init()
{
	arrScene[(UINT)Group_Scene::Stage_Tile] = new CScene_Tile();
	arrScene[(UINT)Group_Scene::Stage_Tile]->setName(L"Stage_Tile");

	arrScene[(UINT)Group_Scene::Start] = new CScene_Start();
	arrScene[(UINT)Group_Scene::Start]->setName(L"Start_Scene");

	arrScene[(UINT)Group_Scene::Stage_01] = new CScene_Stage01();
	arrScene[(UINT)Group_Scene::Stage_01]->setName(L"Start_Stage_01");

	arrScene[(UINT)Group_Scene::Result] = new CScene_Result();
	arrScene[(UINT)Group_Scene::Result]->setName(L"Result");
	
	curScene = arrScene[(UINT)Group_Scene::Start];
	curScene->Enter();
}

void CSceneManager::changeScene(Group_Scene type)
{
	curScene->Exit();
	curScene = arrScene[(UINT)type];
	curScene->Enter();
}

void CSceneManager::update()
{
	curScene->update();
	curScene->finalupdate();
}

void CSceneManager::render()
{
	curScene->render();
}

CScene* CSceneManager::getCurScene()
{
	return curScene;
}
