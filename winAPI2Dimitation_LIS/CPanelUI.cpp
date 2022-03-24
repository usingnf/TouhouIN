#include "pch.h"
#include "CPanelUI.h"

CPanelUI::CPanelUI()
{
	dragStart = Vec2(0, 0);
}

CPanelUI* CPanelUI::clone()
{
	return new CPanelUI(*this);
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::mouseOn()
{

}

void CPanelUI::mouseLbtnDown()
{
	dragStart = GETMOUSEPOS();
}

void CPanelUI::mouseLbtnUp()
{

}
