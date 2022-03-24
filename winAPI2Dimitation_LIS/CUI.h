#pragma once



class CUI : public CGameObject
{
	friend class CUIManager;
private:
	vector<CUI*> vecChild;

	Vec2 finalPos;
	Vec2 startImagePos;
	Vec2 endImagePos;

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
	virtual void render();

	void update_child();
	void finalupdate_child();
	void render_child();

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	bool isLbtnDown();
	bool isCameraAffected();
	bool isMouseOn();

	void setCameraAffected(bool b);

	Vec2 getFinalPos();
	vector<CUI*>& getChild();

	void AddChild(CUI* ui);
	virtual void setImage(const wstring& name);
	void setImagePos(Vec2 start, Vec2 end);

private:
	void mouseOnCheck();
};

