#include "pch.h"

CTimeManager::CTimeManager()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
	m_uiFPS = 0;
	m_dDeltaTime = 0;
}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::update()
{
	static unsigned int updateCount = 0;
	static double updateOneSecond = 0;

	QueryPerformanceCounter(&m_llCurCount);
	//이전 업데이트의 카운팅과 현재 업데이트의 카운트 값의 차이로 
	//1초당 카운트수로 나누어지면 업데이트 사이에 몇초가 지났는지 알 수 있다.
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;
	m_llPrevCount = m_llCurCount;
	
	++updateCount;
	updateOneSecond += m_dDeltaTime;
	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;
		updateOneSecond = 0;
		updateCount = 0;
	}
}

void CTimeManager::render()
{

}

void CTimeManager::init()
{
	QueryPerformanceCounter(&m_llCurCount);
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

unsigned int CTimeManager::getFPS()
{
	return m_uiFPS;
}

double CTimeManager::getDeltaTime()
{
	return m_dDeltaTime;
}
