#pragma once
#include "CSingleton.h"
#include "CTimeManager.h"

enum class Group_Pen
{
	Red,
	Green,
	Blue,
	White,
	Black,

	Size,
};

enum class Group_Brush
{
	Hollow,
	Red,
	Green,
	Blue,
	White,
	Black,
	

	Size,
};

class CTexture;

class CCore
{
	SINGLETON(CCore);
private:
	
public:
	void init();
	void update();
	void render();
};

