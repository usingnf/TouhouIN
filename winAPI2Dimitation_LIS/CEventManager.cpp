#include "pch.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::update()
{
	for (int i = 0; i < m_vecDelete.size(); i++)
	{
		if (nullptr != m_vecDelete[i])
		{
			delete m_vecDelete[i];
			m_vecDelete[i] = nullptr;
		}
			
	}
	m_vecDelete.clear();

	for (int i = 0; i < m_vecEvent.size(); i++)
	{
		execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventManager::execute(const tEvent& _event)
{

	switch (_event.type)
	{
	case Type_Event::Create_Object:
	{
		CGameObject* obj = (CGameObject*)_event.lParam;
		Group_GameObj group = (Group_GameObj)_event.wParam;

		CSceneManager::getInstance()->getCurScene()->AddObject(obj, group);
		break;
	}
	case Type_Event::Delete_Object:
	{
		CGameObject* obj = (CGameObject*)_event.lParam;
		if (obj->getIsDelete() == true)
		{
			return;
		}
		obj->setIsDelete(true);
		m_vecDelete.push_back(obj);
		break;
	}
	case Type_Event::Change_Scene:
	{
		Group_Scene group = (Group_Scene)_event.lParam;
		CUIManager::getInstance()->setFocusedUI(nullptr);
		CSceneManager::getInstance()->changeScene(group);
		break;
	}
	}
}

void CEventManager::addEvent(const tEvent& _event)
{
	m_vecEvent.push_back(_event);
}

void CEventManager::createGameObject(const CGameObject* obj, Group_GameObj type)
{
	tEvent _event;
	_event.type = Type_Event::Create_Object;
	_event.lParam = (DWORD_PTR)obj;
	_event.wParam = (DWORD_PTR)type;

	addEvent(_event);
}

void CEventManager::deleteGameObject(CGameObject* obj)
{
	tEvent _event;
	_event.type = Type_Event::Delete_Object;
	_event.lParam = (DWORD_PTR)obj;
	addEvent(_event);
}

void CEventManager::changeScene(Group_Scene scene)
{
	tEvent _event;
	_event.type = Type_Event::Change_Scene;
	_event.lParam = (DWORD_PTR)scene;
	addEvent(_event);
}

