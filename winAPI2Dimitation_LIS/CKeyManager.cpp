#include "pch.h"

CKeyManager::CKeyManager()
{
	for (int i = 0; i < VK_SIZE; i++)
	{
		m_arrPrevKey[i] = false;
		m_arrCurKey[i] = (UINT)Key_State::None;
	}
}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::update()
{
	

	//창 비활성화시 키 입력 해제.
	HWND curWnd = GetFocus();
	if (hWnd != curWnd)
	{
		for (int i = 0; i < VK_SIZE; i++)
		{
			if (m_arrPrevKey[i] == true)
			{
				m_arrCurKey[i] = (UINT)Key_State::Off;
			}
			m_arrPrevKey[i] = false;
			m_arrCurKey[i] = (UINT)Key_State::None;
		}
		
		return;
	}

	//모든 키의 입력 상태 확인
	//0x0000 : 이전에 누른 적이 없고 호출 시점에도 눌려있지 않은 상태
	//0x0001 : 이전에 누른 적이 있고 호출 시점에는 눌려있지 않은 상태
	//0x8000 : 이전에 누른 적이 없고 호출 시점에는 눌려있는 상태
	//0x8001 : 이전에 누른 적이 있고 호출 시점에도 눌려있는 상태
	for (int i = 0; i < VK_SIZE; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			if (m_arrPrevKey[i] == true)
			{
				m_arrCurKey[i] = (UINT)Key_State::Hold;
			}
			else
			{
				m_arrCurKey[i] = (UINT)Key_State::Tap;
			}
			m_arrPrevKey[i] = true;
		}
		else
		{
			if (m_arrPrevKey[i] == true)
			{
				m_arrCurKey[i] = (UINT)Key_State::Off;
			}
			else
			{
				m_arrCurKey[i] = (UINT)Key_State::None;
			}
			m_arrPrevKey[i] = false;
		}
	}
	
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);
	m_curMousePos.x = p.x;
	m_curMousePos.y = p.y;
	m_CameraMousePos.x = CCameraManager::getInstance()->getRealPos(m_curMousePos).x;
	m_CameraMousePos.y = CCameraManager::getInstance()->getRealPos(m_curMousePos).y;
}

void CKeyManager::init()
{
	
}

int CKeyManager::getButtonState(const int& key)
{
	return m_arrCurKey[key];
}

Vec2 CKeyManager::getMousePos()
{
	return m_curMousePos;
}

Vec2 CKeyManager::getCameraMousePos()
{
	return m_CameraMousePos;
}

