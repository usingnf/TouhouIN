#pragma once
#include "CScene.h"
class CScene_Tile : public CScene
{
private:
	HWND m_hWnd;
	UINT m_index;
public:
	CScene_Tile();
	~CScene_Tile();
	virtual void update();
	virtual void Enter();
	virtual void Exit();

	void setIndex(UINT index);
	void setTileIndex();

	void saveTile(const wstring& path);
	void saveTileData();

	void loadTileData();
};

