#include "pch.h"
#include "CTile.h"

CTile::CTile()
{
	this->scale = Vec2(Tile_Size, Tile_Size);
	image = CResourceManager::getInstance()->loadD2DImage(L"Tile", L"\\texture\\tilemap.bmp");
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

	int width = image->getWidth();
	int height = image->getHeight();
	int maxX = width / Tile_Size;
	int maxY = height / Tile_Size;
	int curX = tileIndex % maxX;
	int curY = (tileIndex / maxX) % maxY;

	CRenderManager::getInstance()->RenderFrame(
		image,
		p.x - (s.x / 2.f),
		p.y - (s.y / 2.f),
		p.x + (s.x / 2.f),
		p.y + (s.y / 2.f),
		(int)(curX * Tile_Size),
		(int)(curY * Tile_Size),
		Tile_Size,
		Tile_Size,
		alpha, pos, angle
	);	
}

void CTile::setImage(CD2DImage* image)
{
	this->image = image;
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