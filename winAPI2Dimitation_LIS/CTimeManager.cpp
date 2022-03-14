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
	//���� ������Ʈ�� ī���ð� ���� ������Ʈ�� ī��Ʈ ���� ���̷� 
	//1�ʴ� ī��Ʈ���� ���������� ������Ʈ ���̿� ���ʰ� �������� �� �� �ִ�.
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