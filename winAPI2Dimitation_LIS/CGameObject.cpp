#include "pch.h"
#include "CCollider.h"
#include "CMissile.h"

CGameObject::CGameObject()
{
	parent = nullptr;
	name = L"Noname";
	pos = Vec2(0,0);
	destPos = Vec2(0, 0);
	angle = 0;
	scale = Vec2(0,0);
	velocity = Vec2(0, 0);
	gravity = 0;
	drag = 0;
	isFixed = false;

	texture = nullptr;
	image = nullptr;
	collider = nullptr;
	animator = nullptr;

	speed = 100;
	hp = 100;
	isDelete = false;
	isRender = true;

	color = COLORREF(RGB(255, 255, 255));
	timer = 0;
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
	if (nullptr != other.animator)
	{
		animator = new CAnimator(*other.animator);
		animator->owner = this;
		animator->m_mapAni = other.animator->m_mapAni;
		animator->curAnimation = other.animator->curAnimation;
	}

	speed = other.speed;
	hp = other.hp;
	isDelete = false;

}

CGameObject::~CGameObject()
{
	if (nullptr != collider)
	{
		delete collider;
		collider = nullptr;
	}
		
	if (nullptr != animator)
	{
		delete animator;
		animator = nullptr;
	}
		
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

void CGameObject::setDestPos(Vec2 vec)
{
	this->destPos = vec;
}

Vec2 CGameObject::getDestPos()
{
	return destPos;
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

bool CGameObject::getFixed()
{
	return isFixed;
}

void CGameObject::setSpeed(double speed)
{
	this->speed = speed;
}

void CGameObject::die()
{
	DeleteObject(this);
}

void CGameObject::setTimer(double time)
{
	this->timer = time;
}

double CGameObject::getTimer()
{
	return this->timer;
}

void CGameObject::setTimerCount(int count)
{
	this->timerCount = count;
}

int CGameObject::getTimerCount()
{
	return timerCount;
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

void CGameObject::setColldier(CCollider* col)
{
	this->collider = col;
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

void CGameObject::setAnimator(CAnimator* ani)
{
	this->animator = ani;
}

void CGameObject::createAnimator()
{
	if(animator == nullptr)
		animator = new CAnimator();
	animator->owner = this;
}

void CGameObject::setColor(COLORREF color)
{
	this->color = color;
}

void CGameObject::setImage(const wstring& name)
{
	image = CResourceManager::getInstance()->loadD2DImage(name, L"\\texture\\" + name);
}

void CGameObject::setImage(const wstring& name, Vec2 leftTop, Vec2 imageSize)
{
	image = CResourceManager::getInstance()->loadD2DImage(name, L"\\texture\\" + name);
	
	createAnimator();
	animator->createAnimation(L"stay", image, leftTop, imageSize, imageSize, 1, 1);
	animator->play(L"stay");
}

bool CGameObject::getIsRender()
{
	return isRender;
}

void CGameObject::setIsRender(bool render)
{
	this->isRender = render;
}

void CGameObject::setUpdateCallBack(BTN_FUNC1 pFunc1)
{
	this->m_pFunc1 = pFunc1;
}


void CGameObject::setAngle(double ang)
{
	this->angle = ang;
}

void CGameObject::setAngle(Vec2 vec)
{
	this->angle = Vec2::getAngle(vec);
}

void CGameObject::createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type)
{
	if (g_missileIndex >= MAX_MISSILE - 1)
		g_missileIndex = 0;

	int startIndex = g_missileIndex;

	while (g_missile[g_missileIndex]->getIsUse() == true)
	{
		g_missileIndex += 1;
		if (g_missileIndex >= MAX_MISSILE - 1)
			g_missileIndex = 0;

		if (g_missileIndex == startIndex)
			break;
	}
	string str = std::to_string(g_missileIndex);
	wstring w;
	w.assign(str.begin(), str.end());
	Logger::debug(w.c_str());

	CMissile* missile = g_missile[g_missileIndex];
	missile->setPos(pos);
	missile->setScale(size);
	if (missile->getCollider() == nullptr)
	{
		missile->createCollider();
	}
	missile->getCollider()->setColliderScale(colSize);
	missile->setSpeed(speed);
	missile->setAngle(angle);
	missile->setDamage(damage);
	missile->setImage(image, leftTop, imageSize);
	missile->setIsUse(true);
	//CREATEOBJECT(missile, type);

	g_missileIndex += 1;
}