#pragma once
#include "CCore.h"

class SelectGDI
{
private:
	HDC m_hDC;
	HPEN m_hOldPen;
	HBRUSH m_hOldBrush;

public:
	SelectGDI(HDC hDC, Group_Pen pen)
	{
		m_hDC = hDC;
		m_hOldBrush = 0;
		HPEN hPen = CCore::getInstance()->getPen(pen);
		m_hOldPen = (HPEN)SelectObject(hDC, hPen);
	}

	SelectGDI(HDC hDC, Group_Brush brush)
	{
		m_hDC = hDC;
		m_hOldPen = 0;
		HBRUSH hBrush = CCore::getInstance()->getBrush(brush);
		m_hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	}

	~SelectGDI()
	{
		SelectObject(m_hDC, m_hOldPen);
		SelectObject(m_hDC, m_hOldBrush);
	}
		
};