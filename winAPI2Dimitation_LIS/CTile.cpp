#include "pch.h"
#include "CTile.h"

CTile::CTile()
{
	this->scale = Vec2(Tile_Size, Tile_Size);
	texture = CResourceManager::getInstance()->loadTexture(L"Tile", L"tilemap.bmp");
	tileIndex = 0;
}

CTile::~CTile()
{
}

CTile* CTile::clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render(HDC& hDC)
{
	Vec2 p = CCameraManager::getInstance()->getRenderPos(getPos());
	Vec2 s = getScale();

	//Rectangle(hDC, p.x, p.y, p.x + s.x, p.y + s.y);

	int width = texture->getBitmapWidth();
	int height = texture->getBitmapHeight();
	int maxX = width / Tile_Size;
	int maxY = height / Tile_Size;
	int curX = tileIndex % maxX;
	int curY = (tileIndex / maxX) % maxY;

	TransparentBlt(hDC,
		(int)p.x,
		(int)p.y,
		(int)s.x,
		(int)s.y,
		texture->getDC(),
		(int)(curX * Tile_Size),
		(int)(curY * Tile_Size),
		Tile_Size,
		Tile_Size,
		RGB(255, 0, 255));
	
}

void CTile::setTexture(CTexture* tex)
{
	this->texture = tex;
}

void CTile::setTileIndex(int index)
{
	tileIndex = index;
}

void CTile::save(FILE* pFile)
{
	fwrite(&tileIndex, sizeof(int), 1, pFile);
}

void CTile::load(FILE* pFile)
{
	fread(&tileIndex, sizeof(int), 1, pFile);
}