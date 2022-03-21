#include "pch.h"
#include "CAnimator.h"

CAnimator::CAnimator()
{
	owner = nullptr;
	curAnimation = nullptr;
}

CAnimator::~CAnimator()
{
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin(); iter != m_mapAni.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	curAnimation = nullptr;
	m_mapAni.clear();
}

void CAnimator::update()
{
	if (curAnimation != nullptr)
		curAnimation->update();
}

void CAnimator::render(HDC hDC)
{
	if (curAnimation != nullptr)
		curAnimation->render(hDC);
}

CGameObject* CAnimator::getOwner()
{
	return owner;
}


void CAnimator::createAnimation(const wstring& strName, CD2DImage* tex, Vec2 lt, Vec2 slice, Vec2 step, float duration, UINT frmCount)
{
	CAnimation* pAni = findAnimation(strName);
	if (pAni != nullptr)
	{
		m_mapAni.erase(m_mapAni.find(strName));
	}
	//assert(nullptr == pAni);

	pAni = new CAnimation;

	pAni->setName(strName);
	pAni->animator = this;
	pAni->create(tex, lt, slice, step, duration, frmCount);

	m_mapAni.insert(make_pair(strName, pAni));
}

/*
void CAnimator::createAnimation(const wstring& name, CTexture* tex, Vec2 leftTop, Vec2 slice, Vec2 step, float duration, UINT frameCount)
{
	CAnimation* ani = findAnimation(name);
	if (ani != nullptr)
	{
		return;
	}
	ani = new CAnimation();
	ani->animator = this;
	ani->name = name;
	ani->create(tex, leftTop, slice, step, duration, frameCount);

	m_mapAni.insert(make_pair(name, ani));
}
*/

CAnimation* CAnimator::findAnimation(const wstring& name)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(name);
	if (iter == m_mapAni.end())
	{
		return nullptr;
	}
	return iter->second;
}

CAnimation* CAnimator::getCurAnimation()
{
	return curAnimation;
}

wstring CAnimator::getCurAnimationName()
{
	return curAnimation->getName();
}

void CAnimator::selectAnimator()
{

}

void CAnimator::play(const wstring& name)
{
	CAnimation* ani = findAnimation(name);
	if (ani != nullptr)
	{
		curAnimation = ani;
		curAnimation->accTime = 0;
		curAnimation->curFrame = 0;
	}
	
}
