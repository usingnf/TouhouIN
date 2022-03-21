#pragma once



class CGameObject;

class CPanelUI;
class CText;
class CUI;

class CScene
{
private:
	vector<CGameObject*> m_arrObj[(UINT)Group_GameObj::Size];
	wstring strName;

	UINT tileX;
	UINT tileY;

	vector<wstring> text;
	

protected:
	double timer = 0;
	int timerCount = 0;

	CPanelUI* dialogPanel = nullptr;
	CText* dialogText = nullptr;
	CUI* dialogLeftChr = nullptr;
	CUI* dialogRightChr = nullptr;
	int dialogNum = 0;

public:
	CScene();
	virtual ~CScene();

	
	vector<CGameObject*>* getArrObj();
	void setName(std::wstring name);
	wstring getName();
	void AddObject(CGameObject* pObj, Group_GameObj type);

	const vector<CGameObject*>& getGroupObject(Group_GameObj type);
	void deleteGroup(Group_GameObj group);
	void deleteAll();

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC& hDC);
	void render_tile(HDC& hDC);

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void createTile(UINT x, UINT y);
	void loadTile(const wstring& path);
	UINT getTileX();
	UINT getTileY();

	void startDialog();
	void nextDialog();
	void endDialog();

protected:
	void clearObject();

};

