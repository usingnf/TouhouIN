#include "pch.h"
#include "CAnimation.h"



CAnimation::CAnimation()
{
	name = L"Noname";
	animator = nullptr;
	//texture = nullptr;
	image = nullptr;
	curFrame = -1;
	accTime = 0;
	isLoop = true;
	reverse = false;
	angle = 0;
}

CAnimation::~CAnimation()
{
	
}

void CAnimation::setLoop(bool b)
{
	isLoop = b;
}

bool CAnimation::getLoop()
{
	return isLoop;
}

void CAnimation::setName(const wstring& name)
{
	this->name = name;
}

const wstring& CAnimation::getName()
{
	return name;
}

void CAnimation::update()
{
	accTime += DT();

	if (accTime > vecFrame[curFrame].duration)
	{
		accTime -= vecFrame[curFrame].duration;
		curFrame++;
		if (curFrame >= vecFrame.size())
		{
			if (isLoop == true)
			{
				curFrame %= vecFrame.size();
			}
			else
			{
				curFrame--;
			}
		}
		
	}
}

void CAnimation::render(HDC& hDC)
{
	CGameObject* obj = animator->getOwner();
	tAniFrame frm = vecFrame[curFrame];
	
	Vec2 pos = obj->getPos() + frm.fptOffset;
	pos = CCameraManager::getInstance()->getRenderPos(pos);

	if (reverse)
	{
		CRenderManager::getInstance()->RenderRevFrame(
			image,
			pos.x - frm.slice.x / 2.f,
			pos.y - frm.slice.y / 2.f,
			pos.x + frm.slice.x / 2.f,
			pos.y + frm.slice.y / 2.f,
			frm.leftTop.x,
			frm.leftTop.y,
			frm.leftTop.x + frm.slice.x,
			frm.leftTop.y + frm.slice.y,
			pos, angle
		);
	}
	else
	{
		CRenderManager::getInstance()->RenderFrame(
			image,
			pos.x - frm.slice.x / 2.f,
			pos.y - frm.slice.y / 2.f,
			pos.x + frm.slice.x / 2.f,
			pos.y + frm.slice.y / 2.f,
			frm.leftTop.x,
			frm.leftTop.y,
			frm.leftTop.x + frm.slice.x,
			frm.leftTop.y + frm.slice.y,
			pos, angle
		);
	}
}

void CAnimation::create(CD2DImage* img, Vec2 lt, Vec2 slice, Vec2 step, float duration,	UINT frmCount)
{
	image = img;

	tAniFrame frm = {};
	for (UINT i = 0; i < frmCount; i++)
	{
		frm.duration = duration;
		frm.slice = slice;
		frm.leftTop = lt + step * i;

		vecFrame.push_back(frm);
	}
}
void CAnimation::setReverse(bool reverse)
{
	this->reverse = reverse;
}

void CAnimation::SetFrame(int frmIndex)
{
	curFrame = frmIndex;
}

tAniFrame& CAnimation::GetFrame(int frmIndex)
{
	return vecFrame[frmIndex];
}