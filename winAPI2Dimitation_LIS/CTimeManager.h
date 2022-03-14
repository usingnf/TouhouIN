#pragma once
#include "pch.h"

class CTimeManager
{
	SINGLETON(CTimeManager);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;
	unsigned int m_uiFPS;
	double m_dDeltaTime;
public:
	void update();
	void render();
	void init();
	unsigned int getFPS();
	double getDeltaTime();
};

