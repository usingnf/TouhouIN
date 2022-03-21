#pragma once

struct tEvent
{
	Type_Event type;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
};


class CEventManager
{
	SINGLETON(CEventManager);
private:
	vector<tEvent> m_vecEvent;
	vector<CGameObject*> m_vecDelete;
	vector<CGameObject*> m_vecComponentDelete;
	bool isSceneChange = false;
public:
	void update();
	void execute(const tEvent& _event);
	void addEvent(const tEvent& _event);
	void createGameObject(const CGameObject* obj, Group_GameObj type);
	void deleteGameObject(CGameObject* obj);
	void changeScene(Group_Scene scene);
	void deleteComponent(CGameObject* obj);
};

