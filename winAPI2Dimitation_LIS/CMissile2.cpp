#include "pch.h"
#include "CMissile2.h"

CMissile2::CMissile2()
{
	scale = Vec2(30, 30);
	gravity = 100;
}

CMissile2* CMissile2::clone()
{
	return new CMissile2(*this);
}

CMissile2::~CMissile2()
{
	
}

void CMissile2::update()
{
	if (pos.x < 0 || pos.x > WS_WIDTH || pos.y < 0 || pos.y > WS_HEIGHT)
	{
		return;
		//object 파괴 작업 필요.
	}
	velocity.y += -gravity * DT();
	pos.x += velocity.x * DT();
	pos.y += -velocity.y * DT();
}

void CMissile2::render(HDC& hDC)
{
	Ellipse(hDC,
		pos.x - (scale.x / 2),
		pos.y - (scale.y / 2),
		pos.x + (scale.x / 2),
		pos.y + (scale.y / 2));
}
