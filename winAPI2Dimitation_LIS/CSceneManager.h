#pragma once
#include "CSingleton.h"

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);
private:
	CScene* arrScene[(UINT)Group_Scene::Size];
	CScene* curScene;
public:
	void init();
	void update();
	void render();
	CScene* getCurScene();
	void changeScene(Group_Scene type);
};

