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
	if (isLbtnDown() == true)
	{
		Vec2 mousePos = GETMOUSEPOS();
		Vec2 diff = mousePos - dragStart;
		Vec2 curPos = this->pos;
		curPos += diff;
		setPos(curPos);
		dragStart = GETMOUSEPOS();
	}
}

void CPanelUI::mouseLbtnDown()
{
	dragStart = GETMOUSEPOS();
}

void CPanelUI::mouseLbtnUp()
{

}
