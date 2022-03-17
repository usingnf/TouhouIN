#pragma once
#include "CAnimator.h"

class CCollider;
//class CAnimator;
class CTexture;
class CD2DImage;

typedef void(*BTN_FUNC1)(DWORD_PTR);

class CGameObject
{
	friend class CEventManager;
protected:
	wstring name;
	CGameObject* parent;
	Vec2 pos;
	Vec2 destPos;
	double angle;
	Vec2 scale;
	Vec2 velocity;
	double gravity;
	double drag;
	COLORREF color;
	bool isFixed;

	CTexture* texture;
	CD2DImage* image;
	CCollider* collider;
	CAnimator* animator;

	double speed;
	double hp;
	bool isDelete;
	double timer = 0;

	bool isRender;
	void setIsDelete(bool dead);
protected:
	BTN_FUNC1 m_pFunc1 = nullptr;
public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual CGameObject* clone() = 0;
	virtual ~CGameObject();

	virtual void update();
	virtual void finalupdate(); //collider¿ë
	virtual void render(HDC& hDC);
	virtual void component_render(HDC& hDC);
	
	void setName(wstring _name);
	wstring getName();

	void setPos(Vec2 vec);
	Vec2 getPos();

	void setDestPos(Vec2 vec);
	Vec2 getDestPos();
	
	void setScale(Vec2 scale);
	Vec2 getScale();

	void setHp(double hp);
	double getHp();

	virtual void setAngle(double ang);
	virtual void setAngle(Vec2 vec);
	virtual double getAngle();
	bool getFixed();

	void setSpeed(double speed);

	virtual void die();

	void setTimer(double time);
	double getTimer();

	bool getIsDelete();

	void createCollider();
	CCollider* getCollider();

	void addForce(Vec2 vec);

	void createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, Vec2 size, Vec2 colSize, double speed, double angle, double damage, Group_GameObj type);

	virtual void onCollisionEnter(CCollider* other) {};
	virtual void onCollisionStay(CCollider* other) {};
	virtual void onCollisionExit(CCollider* other) {} ;

	CAnimator* getAnimator();
	void createAnimator();

	void setColor(COLORREF color);
	void setImage(const wstring& name);
	void setImage(const wstring& name, Vec2 leftTop, Vec2 imageSize);

	bool getIsRender();
	void setIsRender(bool render);

	virtual void setUpdateCallBack(BTN_FUNC1 pFunc1);
};

