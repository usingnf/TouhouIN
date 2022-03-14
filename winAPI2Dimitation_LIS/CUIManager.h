#pragma once
#include "CUI.h"
class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI* focusedUI;
public:
	void update();
	void setFocusedUI(CUI* ui);
private:
	CUI* getTargetUI(CUI* parentUI);
	CUI* getFocusedUI();
	
};

