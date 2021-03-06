#include "pch.h"
#include "CUI.h"

CUI::CUI()
{
	image = CResourceManager::getInstance()->loadD2DImage(L"background.png", L"\\texture\\background.png");
	bCameraAffected = false;
	bMouseOn = false;
	bLbtnDown = false;

	startImagePos = Vec2(0, 0);
	endImagePos = Vec2(0, 0);
}


CUI::CUI(const CUI& other) : CGameObject(other)
{
	parent = nullptr;
	bCameraAffected = other.bCameraAffected;
	bMouseOn = false;
	bLbtnDown = false;

	vecChild.clear();
	for (UINT i = 0; i < other.vecChild.size(); i++)
	{
		AddChild(other.vecChild[i]->clone());
	}
}

CUI* CUI::clone()
{
	CUI* ui = new CUI(*this);
	ui->vecChild.clear();
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		ui->vecChild.push_back(new CUI(*vecChild[i]));
		ui->vecChild[i]->parent = ui;
	}
	
	return ui;
}

CUI::~CUI()
{
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		if (vecChild[i] != nullptr)
		{
			delete vecChild[i];
			vecChild[i] = nullptr;
		}
			
	}
}

void CUI::update()
{
	if (m_pFunc1 != nullptr)
		m_pFunc1((DWORD_PTR)this);
	update_child();
}

void CUI::finalupdate()
{
	CGameObject::finalupdate();

	finalPos = getPos();
	if (getParent() != nullptr)
	{
		Vec2 parentPos = getParent()->getPos();
		finalPos += parentPos;
	}
	mouseOnCheck();

	finalupdate_child();
}

void CUI::render()
{
	Vec2 p = getFinalPos();
	Vec2 s = getScale();

	if (isRender == false)
		return;

	if (bCameraAffected == true)
	{
		p = CCameraManager::getInstance()->getRenderPos(p);
	}

	if (image != nullptr)
	{
		CRenderManager::getInstance()->RenderFrame(
			image,
			p.x, p.y,
			p.x + s.x, p.y + s.y,
			startImagePos.x, startImagePos.y,
			endImagePos.x, endImagePos.y,
			alpha
		);
	}

	render_child();
}

void CUI::update_child()
{
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		vecChild[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		vecChild[i]->finalupdate();
	}
}

void CUI::render_child()
{
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		vecChild[i]->render();
	}
}

void CUI::mouseOn()
{

}

void CUI::mouseLbtnDown()
{

}

void CUI::mouseLbtnUp()
{

}

void CUI::mouseLbtnClicked()
{
}

bool CUI::isLbtnDown()
{
	return bLbtnDown;
}

bool CUI::isCameraAffected()
{
	return bCameraAffected;
}

bool CUI::isMouseOn()
{
	return bMouseOn;
}

void CUI::setCameraAffected(bool b)
{
	bCameraAffected = true;
	for (UINT i = 0; i < vecChild.size(); i++)
	{
		vecChild[i]->setCameraAffected(b);
	}
}

Vec2 CUI::getFinalPos()
{
	return finalPos;
}

vector<CUI*>& CUI::getChild()
{
	return vecChild;
}

void CUI::AddChild(CUI* ui)
{
	vecChild.push_back(ui);
	ui->parent = this;
	ui->bCameraAffected = this->bCameraAffected;
}

void CUI::setImage(const wstring& name)
{
	image = CResourceManager::getInstance()->loadD2DImage(name, L"\\texture\\" + name);
	if (image != nullptr)
	{
		endImagePos.x = image->getWidth();
		endImagePos.y = image->getHeight();
	}
}

void CUI::setImagePos(Vec2 start, Vec2 end)
{
	startImagePos = start;
	endImagePos = end;
	if (end.x == 0)
	{
		endImagePos.x = image->getWidth();
	}
	if (end.y == 0)
	{
		endImagePos.y = image->getHeight();
	}
}

void CUI::mouseOnCheck()
{
	Vec2 mousePos = GETMOUSEPOS();
	Vec2 fPos = getFinalPos();
	Vec2 s = getScale();
	if (bCameraAffected == true)
	{
		mousePos = CCameraManager::getInstance()->getRealPos(mousePos);
	}

	if (fPos.x <= mousePos.x && mousePos.x <= fPos.x + s.x &&
		fPos.y <= mousePos.y && mousePos.y <= fPos.y + s.y)
	{
		bMouseOn = true;
	}
	else
	{
		bMouseOn = false;
	}
}
