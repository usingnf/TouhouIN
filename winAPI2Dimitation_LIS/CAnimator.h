#pragma once
#include "CAnimation.h"
//class CAnimation;

class CAnimator
{
	friend class CGameObject;
private:
	CGameObject* owner;
	map<wstring, CAnimation*> m_mapAni;
	CAnimation* curAnimation;
public:
	CAnimator();
	~CAnimator();

	void update();
	void render();

	CGameObject* getOwner();

	void createAnimation(const wstring& strName, CD2DImage* tex, Vec2 lt, Vec2 slice,
		Vec2 step, float duration, UINT frmCount);
	CAnimation* findAnimation(const wstring& name);
	CAnimation* getCurAnimation();
	wstring getCurAnimationName();
	void selectAnimator();
	void play(const wstring& name);
};

