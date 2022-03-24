#pragma once
class CTile : public CGameObject
{
private:
	int tileIndex;

public:
	const static int Tile_Size = 32;

	CTile();
	virtual ~CTile();
	virtual CTile* clone();
	virtual void update();
	virtual void render(HDC& hDC);

	void setImage(CD2DImage* image);
	void setTileIndex(int index);

	void save(FILE* pFile);
	void load(FILE* pFile);
};

