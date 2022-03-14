#pragma once
class CUI : public CGameObject
{
	friend class CUIManager;
private:
	vector<CUI*> vecChild;
	CUI* parent;

	Vec2 finalPos;

	bool bCameraAffected = false;
	bool bMouseOn = false;
	bool bLbtnDown = false;
public:
	CUI();
	CUI(const CUI& other);
	virtual CUI* clone();
	virtual ~CUI();

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC& hDC);

	void update_child();
	void finalupdate_child();
	void render_child(HDC& hDC);

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	bool isLbtnDown();
	bool isCameraAffected();
	bool isMouseOn();

	void setCameraAffected(bool b);

	Vec2 getFinalPos();
	CUI* getParent();
	const vector<CUI*>& getChild();

	void AddChild(CUI* ui);

private:
	void mouseOnCheck();
};

