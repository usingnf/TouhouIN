#include "pch.h"
#include "CButtonUI.h"

CButtonUI::CButtonUI()
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

CButtonUI::~CButtonUI()
{
}

void CButtonUI::mouseOn()
{
	
}

void CButtonUI::mouseLbtnDown()
{
	image = CResourceManager::getInstance()->loadD2DImage(L"Mario", L"Mario_Player2.bmp");
}

void CButtonUI::mouseLbtnUp()
{
	image = CResourceManager::getInstance()->loadD2DImage(L"Star", L"Mario_Item2.bmp");
}

void CButtonUI::mouseLbtnClicked()
{
	if(m_pFunc != nullptr)
		m_pFunc(m_pParam1, m_pParam2);
}

void CButtonUI::setClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}
