#pragma once
class CPanelUI : public CUI
{
private:
	Vec2 dragStart;
public:
	CPanelUI();
	virtual CPanelUI* clone();
	~CPanelUI();

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
};

