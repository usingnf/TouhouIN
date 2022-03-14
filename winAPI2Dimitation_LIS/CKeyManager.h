#pragma once
#define VK_SIZE 255




class CKeyManager
{
	SINGLETON(CKeyManager);
private:
	bool m_arrPrevKey[VK_SIZE];
	int m_arrCurKey[VK_SIZE];
	Vec2 m_curMousePos;
	Vec2 m_CameraMousePos;
public:
	void update();
	void init();

	int getButtonState(const int& key);


	Vec2 getMousePos();
	Vec2 getCameraMousePos();

};

