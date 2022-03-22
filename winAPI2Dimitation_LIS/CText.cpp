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
	int a = 0;
}

void CText::update()
{
	if (m_pFunc1 != nullptr)
		m_pFunc1((DWORD_PTR)this);
}

void CText::render(HDC& hDC)
{
	if(getParent() == nullptr)
		CRenderManager::getInstance()->RenderText(mtext, pos.x, pos.y, scale.x, scale.y, 
			fontSize, color, Vec2(0,0), 0, (int)widthAlign, (int)heightAlign);
	else
		CRenderManager::getInstance()->RenderText(mtext, getParent()->getPos().x + pos.x, getParent()->getPos().y + pos.y, scale.x, scale.y, 
			fontSize, color, Vec2(0, 0), 0, (int)widthAlign, (int)heightAlign);
}

void CText::setText(const WCHAR* text)
{
	wcscpy_s(mtext, text);
}

void CText::setSize(float size)
{
	this->fontSize = size;
}

void CText::setHeightAlignment(Type_TextHeightAlignment align)
{
	this->heightAlign = align;
}

void CText::setWidthAlignment(Type_TextWidthAlignment align)
{
	this->widthAlign = align;
}
