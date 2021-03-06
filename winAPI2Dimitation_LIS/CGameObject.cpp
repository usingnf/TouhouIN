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

CGameObject* CGameObject::getParent()
{
	return parent;
}

void CGameObject::setParent(CGameObject* obj)
{
	this->parent = obj;
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

void CGameObject::render()
{
	Vec2 camPos = CCameraManager::getInstance()->getRenderPos(pos);

	CRenderManager::getInstance()->RenderFillRectangle
		(camPos.x - (scale.x / 2), camPos.y - (scale.y / 2),
		camPos.x + (scale.x / 2), camPos.y + (scale.y / 2));

	component_render();
}

void CGameObject::component_render()
{
	if(collider != nullptr)
		collider->render();
	if (animator != nullptr)
		animator->render();
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
	if (maxHp == 0)
		maxHp = hp;
	this->hp = hp;
}

double CGameObject::getHp()
{
	return hp;
}

void CGameObject::setMaxHp(double hp)
{
	this->maxHp = hp;
}

double CGameObject::getMaxHp()
{
	return maxHp;
}

double CGameObject::getAngle()
{
	return this->angle;
}

bool CGameObject::getFixed()
{
	return isFixed;
}

void CGameObject::setFixed(bool fix)
{
	this->isFixed = fix;
}

void CGameObject::setSpeed(double speed)
{
	this->speed = speed;
}

double CGameObject::getSpeed()
{
	return this->speed;
}

void CGameObject::setAlpha(float alpha)
{
	this->alpha = alpha;
}

float CGameObject::getAlpha()
{
	return this->alpha;
}

bool CGameObject::getIsInvincible()
{
	return this->isInvincible;
}

void CGameObject::setIsInvincible(bool b)
{
	this->isInvincible = b;
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

void CGameObject::createCollider(Type_Collider type)
{
	if(collider == nullptr)
		collider = new CCollider();
	collider->owner = this;
	collider->setType(type);
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
	animator->createAnimation(L"stay", image, leftTop, imageSize, Vec2(imageSize.x, 0), 1, 1);
	animator->play(L"stay");
}

void CGameObject::addAnimation(const wstring& name, Vec2 leftTop, Vec2 imageSize, double aniSpeed, int frame, bool loop, bool reverse)
{
	createAnimator();
	animator->createAnimation(name, image, leftTop, imageSize, Vec2(imageSize.x, 0), aniSpeed, frame);
	animator->play(name);

	CAnimation* ani = animator->findAnimation(name);
	ani->setLoop(loop);
	ani->setReverse(reverse);
}

bool CGameObject::getIsRender()
{
	return isRender;
}

void CGameObject::setIsRender(bool render)
{
	this->isRender = render;
}

void CGameObject::deleteComponent()
{
	if(animator != nullptr)
		delete this->animator;
	animator = nullptr;
	if(collider != nullptr)
		delete this->collider;
	collider = nullptr;
}

void CGameObject::setUpdateCallBack(BTN_FUNC1 pFunc1)
{
	this->m_pFunc1 = pFunc1;
}

void CGameObject::viewData()
{
	string str = "pos: " + std::to_string((int)pos.x) + "/" + std::to_string((int)pos.y) + "\n";
	str += "hp: " + std::to_string((int)hp) + "\n";
	str += "speed: " + std::to_string((int)speed) + "\n";
	str += "invinsible: " + std::to_string(isInvincible) +"\n";
	wstring w;
	w.assign(str.begin(), str.end());
	CRenderManager::getInstance()->RenderText(w.c_str(), pos.x, pos.y, 200, 50,
		10, RGB(255,255,255), Vec2(0, 0), 0, 0, 0);
}


void CGameObject::setAngle(double ang)
{
	this->angle = ang;
}

void CGameObject::setAngle(Vec2 vec)
{
	this->angle = Vec2::getAngle(vec);
}

CMissile* CGameObject::createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type, Type_Collider shape)
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
	
	CMissile* missile = g_missile[g_missileIndex];
	missile->setPos(pos);
	missile->setScale(size);
	if (missile->getCollider() == nullptr)
		missile->createCollider(Type_Collider::Circle);
	missile->getCollider()->setColliderScale(colSize);
	missile->getCollider()->setType(shape);
	missile->setSpeed(speed);
	missile->setAngle(angle);
	missile->setDamage(damage);
	missile->setImage(image, leftTop, imageSize);
	missile->setIsUse(true);
	missile->setUpdateCallBack(nullptr);
	missile->setHp(10);

	g_missileIndex += 1;

	return missile;
}