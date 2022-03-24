#pragma once
#include "CScene.h"

class CText;
class CPanelUI;

class CScene_Start : public CScene
{
private:
	int menuIndex = 0;
	vector<CText*> vecMenu = { };
	vector<CText*> vecOption = { };
	vector<CText*> vecLevel = { };
	CPanelUI* title;
	CPanelUI* level;
	CUI* textGroup = nullptr;
	CUI* optionGroup = nullptr;

	double timer = 0;
	double timerCount = 0;
	bool left = false;
	
public:
	CScene_Start();
	~CScene_Start();
	virtual void update();
	virtual void render();
	virtual void Enter();
	virtual void Exit();

	int loadHighScore();
	float loadOption();
	void saveOption();
};


