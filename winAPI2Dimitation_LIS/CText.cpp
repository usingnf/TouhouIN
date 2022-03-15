#include "pch.h"
#include "CText.h"


CText::CText()
{
	color = RGB(255, 255, 255);
	fontSize = 10;
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
	CRenderManager::getInstance()->RenderText(mtext, pos.x, pos.y, scale.x, scale.y, fontSize, color);
}

void CText::setText(const WCHAR* text)
{
	wcscpy_s(mtext, text);
}

void CText::setSize(float size)
{
	this->fontSize = size;
}
