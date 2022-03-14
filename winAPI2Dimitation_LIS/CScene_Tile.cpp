#include "pch.h"
#include "CScene_Tile.h"
#include "resource.h"
#include "CTile.h"
#include "CUI.h"
#include "CButtonUI.h"
#include "CPanelUI.h"
#include "CSound.h"
#include <commdlg.h>

INT_PTR CALLBACK tileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tile::CScene_Tile()
{
	m_hWnd = nullptr;
	m_index = 0;
}

CScene_Tile::~CScene_Tile()
{
}

void CScene_Tile::update()
{
	if (KEY(VK_LEFT) == (UINT)Key_State::Hold)
	{
		CCameraManager::getInstance()->move(Vec2(-100 * DT(), 0));
	}
	if (KEY(VK_RIGHT) == (UINT)Key_State::Hold)
	{
		CCameraManager::getInstance()->move(Vec2(100 * DT(), 0));
	}
	if (KEY(VK_UP) == (UINT)Key_State::Hold)
	{
		CCameraManager::getInstance()->move(Vec2(0, -100*DT()));
	}
	if (KEY(VK_DOWN) == (UINT)Key_State::Hold)
	{
		CCameraManager::getInstance()->move(Vec2(0, 100*DT()));
	}

	for (int i = 0; i < (UINT)Group_GameObj::Size; i++)
	{
		for (int j = 0; j < getArrObj()[i].size(); j++)
		{
			if (getArrObj()[i][j]->getIsDelete() == false)
				getArrObj()[i][j]->update();
		}
	}

	setTileIndex();

	if (KEY('T') == (UINT)Key_State::Tap)
	{
		CHANGESCENE(Group_Scene::Start);
	}

}

void buttonFunc(DWORD_PTR param1, DWORD_PTR param2)
{
	//CEventManager::getInstance()->changeScene(Group_Scene::Start);
	CSoundManager::getInstance()->addSound(L"testsound", L"testsound.wav", false, false);
	CSoundManager::getInstance()->play(L"testsound");
}

void CScene_Tile::Enter()
{
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_Tile), hWnd, tileProc);

	CPanelUI* ui = new CPanelUI();
	ui->setPos(Vec2(200,100));
	ui->setScale(Vec2(100, 100));
	AddObject(ui, Group_GameObj::UI);

	CButtonUI* uiChild = new CButtonUI();
	uiChild->setPos(Vec2(50, 50));
	uiChild->setScale(Vec2(40, 40));
	ui->AddChild(uiChild);

	CPanelUI* ui2 = ui->clone();
	ui2->setPos(Vec2(600, 100));
	ui2->setScale(Vec2(100, 100));
	AddObject(ui2, Group_GameObj::UI);

	CButtonUI* uiChild2 = new CButtonUI();
	uiChild2->setPos(Vec2(50, 50));
	uiChild2->setScale(Vec2(40, 40));
	ui2->AddChild(uiChild2);

	uiChild->setClickedCallBack(buttonFunc ,0,0);

	ShowWindow(m_hWnd, SW_SHOW);
}



void CScene_Tile::Exit()
{
	EndDialog(m_hWnd, IDOK);
	clearObject();
}

void CScene_Tile::setIndex(UINT index)
{
	m_index = index;
}

void CScene_Tile::setTileIndex()
{
	if (KEY(VK_LBUTTON) == (UINT)Key_State::Hold)
	{
		Vec2 mousePos = GETMOUSEPOS();
		mousePos = CCameraManager::getInstance()->getRealPos(mousePos);
		int iTileX = (int)getTileX();
		int iTileY = (int)getTileY();
		
		int x = (int)mousePos.x / CTile::Tile_Size;
		int y = (int)mousePos.y / CTile::Tile_Size;

		if (mousePos.x < 0.f || iTileX <= x ||
			mousePos.y < 0.f || iTileY <=y)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = y * iTileX + x;
		const vector<CGameObject*>& vecTile = getGroupObject(Group_GameObj::Tile);
		((CTile*)vecTile[iIdx])->setTileIndex(m_index);
	}	
}

void CScene_Tile::saveTile(const wstring& path)
{
	//wstring filePath = CPathManager::getInstance()->getContentPath();
	wstring filePath = path;
	FILE* file = nullptr;
	
	_wfopen_s(&file, filePath.c_str(), L"wb");
	if (file == nullptr)
		return;

	UINT x = getTileX();
	UINT y = getTileY();

	fwrite(&x, sizeof(UINT), 1, file);
	fwrite(&y, sizeof(UINT), 1, file);

	const vector<CGameObject*>& vecTile = getGroupObject(Group_GameObj::Tile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->save(file);
	}

	fclose(file);
}

void CScene_Tile::saveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd;					// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::getInstance()->getContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		saveTile(szName);
	}
}

void CScene_Tile::loadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::getInstance()->getContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		loadTile(szName);
	}
}

INT_PTR CALLBACK tileProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			CScene* curScene = CSceneManager::getInstance()->getCurScene();

			CScene_Tile* tileScene = dynamic_cast<CScene_Tile*>(curScene);
			if (tileScene != nullptr)
			{
				tileScene->saveTileData();
				//tileScene->saveTile(L"\\content\\tile\\test.tile");
			}
			
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			CScene* pCurScene = CSceneManager::getInstance()->getCurScene();

			CScene_Tile* pToolScene = dynamic_cast<CScene_Tile*>(pCurScene);
			assert(pToolScene);

			pToolScene->loadTileData();

			return (INT_PTR)TRUE;
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) == IDC_Apply)
		{
			int x = GetDlgItemInt(hDlg, IDC_InputX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_InputY, nullptr, false);
			CScene* curScene = CSceneManager::getInstance()->getCurScene();

			CScene_Tile* tileScene = dynamic_cast<CScene_Tile*>(curScene);
			if (tileScene != nullptr)
			{
				curScene->createTile(x, y);
			}
			
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_Apply2)
		{
			int m_iIdx = GetDlgItemInt(hDlg, IDC_InputIndex, nullptr, false);
			
			CScene* curScene = CSceneManager::getInstance()->getCurScene();

			CScene_Tile* tileScene = dynamic_cast<CScene_Tile*>(curScene);
			if (tileScene != nullptr)
			{
				CTexture* pTex = CResourceManager::getInstance()->findTexture(L"Tile");
				if (pTex == nullptr)
				{
					pTex = CResourceManager::getInstance()->loadTexture(L"Tile", L"tilemap.bmp");
				}

				UINT iWidth = pTex->getBitmapWidth();
				UINT iHeight = pTex->getBitmapHeight();

				UINT iMaxRow = iHeight / CTile::Tile_Size;
				UINT iMaxCol = iWidth / CTile::Tile_Size;

				UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
				UINT iCurCol = (m_iIdx % iMaxCol);

				
				StretchBlt(GetDC(hDlg),
					(int)(150),
					(int)(200),
					(int)(CTile::Tile_Size),
					(int)(CTile::Tile_Size),
					pTex->getDC(),
					(int)(iCurCol * CTile::Tile_Size),
					(int)(iCurRow * CTile::Tile_Size),
					(int)CTile::Tile_Size,
					(int)CTile::Tile_Size,
					SRCCOPY);
				/*BitBlt(GetDC(hDlg),
					(int)(150),
					(int)(200),
					(int)(CTile::Tile_Size),
					(int)(CTile::Tile_Size),
					pTex->getDC(),
					(int)(iCurCol * CTile::Tile_Size),
					(int)(iCurRow * CTile::Tile_Size),
					SRCCOPY);
					*/

				tileScene->setIndex(m_iIdx);
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}
