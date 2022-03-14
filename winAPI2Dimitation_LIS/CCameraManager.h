#pragma once

enum class CAM_EFFECT
{
	Fade_In,
	Fade_Out,

	None,
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	Vec2 pos;
	Vec2 destPos;
	Vec2 diffPos;
	CGameObject* targetObj;

	double time;
	double speed;
	double maxSpeed;

	CAM_EFFECT effect;
	double curTime;
	double effectDuration;

	CTexture* texture;
	
public:

	void setLookAt(Vec2 vec);
	void setTargetObj(CGameObject* obj);
	
	void calDiff();

	Vec2 getPos();
	Vec2 getRenderPos(Vec2 vec);
	Vec2 getRealPos(Vec2 vec);

	void init();
	void render(HDC& hDC);
	void update();

	void timeMove(Vec2 dest, double t);
	void move(Vec2 vec);

	void fadeIn(double duration);
	void fadeOut(double duration);
};

