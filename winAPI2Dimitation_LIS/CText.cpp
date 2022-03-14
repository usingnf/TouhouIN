#include "pch.h"
#include "CText.h"


CText::CText()
{
	wcscpy_s(mtext, L"123");
}

CText* CText::clone()
{
	return new CText(*this);
}

CText::~CText()
{
}

void CText::update()
{
	
}

void CText::render(HDC& hDC)
{
	TextOutW(hDC, pos.x, pos.y, mtext, sizeof(mtext) / sizeof(WCHAR));
}

void CText::setText(const WCHAR* text)
{
	wcscpy_s(mtext, text);
}
