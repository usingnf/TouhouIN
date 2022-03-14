#pragma once



class CGameObject;

class CScene
{
private:
	vector<CGameObject*> m_arrObj[(UINT)Group_GameObj::Size];
	wstring strName;

	UINT tileX;
	UINT tileY;

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

protected:
	void clearObject();

};

