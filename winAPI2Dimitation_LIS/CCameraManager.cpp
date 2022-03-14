#include "pch.h"
#include "CCameraManager.h"

CCameraManager::CCameraManager()
{
	pos = Vec2(WS_WIDTH / 2, WS_HEIGHT / 2);
	targetObj = nullptr;
	curTime = 0;

	texture = nullptr;
}

CCameraManager::~CCameraManager()
{

}

void CCameraManager::setLookAt(Vec2 vec)
{
	pos = vec;
}

void CCameraManager::setTargetObj(CGameObject* obj)
{
	targetObj = obj;
}

void CCameraManager::calDiff()
{
	Vec2 center = Vec2(WS_WIDTH / 2, WS_HEIGHT / 2);

	diffPos = pos - center;
}

Vec2 CCameraManager::getPos()
{
	return pos;
}

Vec2 CCameraManager::getRenderPos(Vec2 vec)
{
	return vec - diffPos;
}

Vec2 CCameraManager::getRealPos(Vec2 vec)
{
	return vec + diffPos;
}

void CCameraManager::init()
{
	texture = CResourceManager::getInstance()->createTexture(L"CameraTexture", WS_WIDTH, WS_HEIGHT);
}

void CCameraManager::render(HDC& hDC)
{
	if (CAM_EFFECT::None == effect)
	{
		return;
	}

	curTime += DT();
	if (effectDuration < curTime)
	{
		effect = CAM_EFFECT::None;
		return;
	}

	double ratio = curTime / effectDuration;
	int alpha = (int)255 * ratio;

	if (CAM_EFFECT::Fade_Out == effect)
	{
		alpha = (int)255 * (1- ratio);
	}
	else if (CAM_EFFECT::Fade_In == effect)
	{
		alpha = (int)255 * ratio;
	}

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(hDC, 0, 0,
		(int)texture->getBitmapWidth(),
		(int)texture->getBitmapHeight(),
		texture->getDC(),
		0, 0,
		(int)texture->getBitmapWidth(),
		(int)texture->getBitmapHeight(),
		bf);

	
	/*
	BitBlt(hDC, 0, 0,
		(int)texture->getBitmapWidth(),
		(int)texture->getBitmapHeight(),
		texture->getDC(),
		0,
		0, 
		SRCCOPY
	);
	*/
}

void CCameraManager::update()
{
	if (targetObj != nullptr)
	{
		if (targetObj->getIsDelete() == true)
		{
			targetObj = nullptr;
		}
		else
		{
			pos = targetObj->getPos();
		}
	}
	else
	{
		if (Vec2::distance(pos, destPos) < 1)
		{
			pos = destPos;
		}
		else
		{
			pos = pos + (destPos - pos).normalized() * speed * DT();
			speed += maxSpeed * -DT();
		}
	}
	calDiff();
}

void CCameraManager::timeMove(Vec2 dest, double t)
{
	destPos = dest;
	maxSpeed = (destPos - pos).length() / t;
	speed = maxSpeed * 2;
}

void CCameraManager::move(Vec2 vec)
{
	this->pos.x += vec.x;
	this->pos.y += vec.y;
}

void CCameraManager::fadeIn(double duration)
{
	effect = CAM_EFFECT::Fade_In;
	curTime = 0;
	effectDuration = duration;
}

void CCameraManager::fadeOut(double duration)
{
	effect = CAM_EFFECT::Fade_Out;
	curTime = 0;
	effectDuration = duration;
}
