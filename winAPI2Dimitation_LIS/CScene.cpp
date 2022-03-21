#include "pch.h"
#include "CScene.h"
#include "CTile.h"

CScene::CScene()
{
	strName = L"Noname";
	tileX = 0;
	tileY = 0;
}

CScene::~CScene()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			if (m_arrObj[i][j] != nullptr)
			{
				delete m_arrObj[i][j];
				m_arrObj[i][j] = nullptr;
			}
		}
	}
}

vector<CGameObject*>* CScene::getArrObj()
{
	return m_arrObj;
}

void CScene::setName(wstring name)
{
	this->strName = name;
}

wstring CScene::getName()
{
	return strName;
}

void CScene::AddObject(CGameObject* pObj, Group_GameObj type)
{
	m_arrObj[(UINT)type].push_back(pObj);
}

const vector<CGameObject*>& CScene::getGroupObject(Group_GameObj type)
{
	return m_arrObj[(UINT)type];
}

void CScene::deleteGroup(Group_GameObj group)
{
	for (int i = 0; i < m_arrObj[(UINT)group].size(); i++)
	{
		delete m_arrObj[(UINT)group][i];
		m_arrObj[(UINT)group][i] = nullptr;
	}
	m_arrObj[(UINT)group].clear();
}

void CScene::deleteAll()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		deleteGroup((Group_GameObj)i);
	}
}


void CScene::update()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			if (getArrObj()[i][j]->getIsDelete() == false)
				getArrObj()[i][j]->update();
		}
	}
}

void CScene::finalupdate()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			getArrObj()[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC& hDC)
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		/*for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			getArrObj()[i][j]->render(hDC);
		}*/

		if (i == (UINT)Group_GameObj::Tile)
		{
			render_tile(hDC);
			continue;
		}

		for (vector<CGameObject*>::iterator iter = m_arrObj[i].begin(); iter != m_arrObj[i].end(); )
		{
			if ((*iter)->getIsDelete() == false)
			{
				(*iter)->render(hDC);
				iter++;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::render_tile(HDC& hDC)
{
	const vector<CGameObject*>& vecTile = getGroupObject(Group_GameObj::Tile);

	Vec2 fptCamLook = CCameraManager::getInstance()->getPos();
	Vec2 fptLeftTop = fptCamLook - Vec2(WS_WIDTH, WS_HEIGHT) / 2.f;

	int x = (int)fptLeftTop.x / CTile::Tile_Size;
	int y = (int)fptLeftTop.y / CTile::Tile_Size;
	int iLTIdx = tileX * y + x;

	int a = 0;
	

	int width = (int)WS_WIDTH / CTile::Tile_Size;
	int height = (int)WS_HEIGHT / CTile::Tile_Size;
	for (int iCurRow = y; iCurRow <= (y + height); ++iCurRow)
	{
		for (int iCurCol = x; iCurCol <= (x + width + 10); ++iCurCol)
		{
			if (iCurCol < 0 || tileX <= iCurCol || iCurRow < 0 || tileY <= iCurRow)
			{
				continue;
			}
			int iIdx = (tileX * iCurRow) + iCurCol;

			
			a++;
			vecTile[iIdx]->render(hDC);
			
		}
	}
	if (x > 0)
	{
		int b = 0;
	}
}

void CScene::createTile(UINT x, UINT y)
{
	for (int j = 0; j < m_arrObj[(UINT)Group_GameObj::Tile].size(); j++)
	{
		CEventManager::getInstance()->deleteGameObject(m_arrObj[(UINT)Group_GameObj::Tile][j]);
	}
	m_arrObj[(UINT)Group_GameObj::Tile].clear();
	tileX = x;
	tileY = y;

	for (int i = 0; i < tileY; i++)
	{
		for (int j = 0; j < tileX; j++)
		{
			CTile* tile = new CTile();
			tile->setPos(Vec2(j * CTile::Tile_Size, i * CTile::Tile_Size));
			tile->setTexture(CResourceManager::getInstance()->loadTexture(L"Tile", L"tilemap.bmp"));
			tile->setTileIndex(3);
			AddObject(tile, Group_GameObj::Tile);
		}
	}
}

void CScene::loadTile(const wstring& path)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, path.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	createTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = getGroupObject(Group_GameObj::Tile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->load(pFile);
	}

	fclose(pFile);
}

UINT CScene::getTileX()
{
	return tileX;
}

UINT CScene::getTileY()
{
	return tileY;
}

void CScene::startDialog()
{
	g_gameState = Group_GameState::Dialog;
}

void CScene::nextDialog()
{
}

void CScene::endDialog()
{
}

void CScene::clearObject()
{
	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		if (i == (UINT)Group_GameObj::EnemyMissile)
			continue;

		while (!m_arrObj[i].empty())
		{
			delete m_arrObj[i][m_arrObj[i].size() - 1];
			m_arrObj[i][m_arrObj[i].size() - 1] = nullptr;
			m_arrObj[i].pop_back();
		}
		
	}
}
