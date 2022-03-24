#pragma once
#include "CScene.h"

class CPlayer;
class CBody;
class CText;
class hpBar;

class CScene_Stage01 : public CScene
{
private:
	int level = 0;
	CPlayer* player = nullptr;
	CBody* body = nullptr;
	vector<CText*> vecMenu;
	CText* exitText = nullptr;
	CText* returnText = nullptr;
	CUI* hpBar = nullptr;
	int menuNum = 0;
public:
	CScene_Stage01();
	~CScene_Stage01();
	virtual void update();
	virtual void render();
	virtual void Enter();
	virtual void Exit();

	int getLevel();
	void setLevel(int level);
};

