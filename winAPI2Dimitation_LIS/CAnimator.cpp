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

void CAnimator::render()
{
	if (curAnimation != nullptr)
		curAnimation->render();
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

	pAni = new CAnimation;

	pAni->setName(strName);
	pAni->animator = this;
	pAni->create(tex, lt, slice, step, duration, frmCount);

	m_mapAni.insert(make_pair(strName, pAni));
}

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
