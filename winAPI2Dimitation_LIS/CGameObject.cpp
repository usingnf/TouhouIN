#include "pch.h"
#include "CCollider.h"

CGameObject::CGameObject()
{
	parent = nullptr;
	name = L"Noname";
	pos = Vec2(0,0);
	angle = 0;
	scale = Vec2(0,0);
	velocity = Vec2(0, 0);
	gravity = 0;
	drag = 0;

	texture = nullptr;
	image = nullptr;
	collider = nullptr;
	animator = nullptr;

	speed = 100;
	hp = 100;
	isDelete = false;
}

CGameObject::CGameObject(const CGameObject& other)
{
	parent = other.parent;
	name = other.name;
	pos = other.pos;
	angle = other.angle;
	scale = other.scale;
	velocity = other.velocity;
	gravity = other.gravity;
	drag = other.drag;
	collider = nullptr;
	animator = nullptr;

	image = other.image;
	//texture = other.texture;

	if (nullptr != other.collider)
	{
		collider = new CCollider(*other.collider);
		collider->owner = this;
	}
	if (nullptr != other.collider)
	{
		animator = new CAnimator(*other.animator);
		animator->owner = this;
	}

	speed = other.speed;
	hp = other.hp;
	isDelete = false;

}

CGameObject::~CGameObject()
{
	if (nullptr != collider)
		delete collider;
	if (nullptr != animator)
		delete animator;
}

void CGameObject::update()
{
	
}

void CGameObject::finalupdate()
{
	if (collider != nullptr)
	{
		collider->finalupdate();
	}
}

void CGameObject::render(HDC& hDC)
{
	Vec2 camPos = CCameraManager::getInstance()->getRenderPos(pos);

	Rectangle(hDC, 
		camPos.x - (scale.x / 2),
		camPos.y - (scale.y / 2),
		camPos.x + (scale.x / 2),
		camPos.y + (scale.y / 2));

	component_render(hDC);
}

void CGameObject::component_render(HDC& hDC)
{
	if(collider != nullptr)
		collider->render(hDC);
	if (animator != nullptr)
		animator->render(hDC);
}

void CGameObject::setName(wstring _name)
{
	this->name = _name;
}

wstring CGameObject::getName()
{
	return name;
}

void CGameObject::setPos(Vec2 vec)
{
	this->pos = vec;
}

void CGameObject::setScale(Vec2 scale)
{
	this->scale = scale;
}

Vec2 CGameObject::getPos()
{
	return pos;
}

Vec2 CGameObject::getScale()
{
	return scale;
}

void CGameObject::setHp(double hp)
{
	this->hp = hp;
}

double CGameObject::getHp()
{
	return hp;
}

double CGameObject::getAngle()
{
	return this->angle;
}

bool CGameObject::getIsDelete()
{
	return isDelete;
}

void CGameObject::setIsDelete(bool dead)
{
	this->isDelete = dead;
}

void CGameObject::createCollider()
{
	collider = new CCollider();
	collider->owner = this;
}

CCollider* CGameObject::getCollider()
{
	return collider;
}

void CGameObject::addForce(Vec2 vec)
{
	this->velocity.x += vec.x;
	this->velocity.y += vec.y;
}

CAnimator* CGameObject::getAnimator()
{
	return animator;
}

void CGameObject::createAnimator()
{
	animator = new CAnimator();
	animator->owner = this;
}


void CGameObject::setAngle(double ang)
{
	this->angle = ang;
}

void CGameObject::setAngle(Vec2 vec)
{
	this->angle = Vec2::getAngle(vec);
}

