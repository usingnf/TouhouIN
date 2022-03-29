#pragma once
#include "CAnimator.h"
class CMissile;
class CCollider;
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
	float alpha = 1.0f;
	bool isFixed;
	bool isInvincible = false;

	CD2DImage* image;
	CCollider* collider;
	CAnimator* animator;

	double speed;
	double maxHp = 0;
	double hp;
	bool isDelete;
	double timer = 0;
	double timer2 = 0;
	double timer3 = 0;
	int timerCount = 0;
	int timerCount2 = 0;
	int timerCount3 = 0;

	bool isRender;
	void setIsDelete(bool dead);
protected:
	BTN_FUNC1 m_pFunc1 = nullptr;
public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual CGameObject* clone() = 0;
	virtual ~CGameObject();

	CGameObject* getParent();
	void setParent(CGameObject* obj);

	virtual void update();
	virtual void finalupdate(); //collider¿ë
	virtual void render();
	virtual void component_render();
	
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
	void setMaxHp(double hp);
	double getMaxHp();

	virtual void setAngle(double ang);
	virtual void setAngle(Vec2 vec);
	virtual double getAngle();
	bool getFixed();
	void setFixed(bool fix);

	void setSpeed(double speed);
	double getSpeed();

	void setAlpha(float alpha);
	float getAlpha();

	bool getIsInvincible();
	void setIsInvincible(bool b);

	virtual void die();

	void setTimer(double time);
	double getTimer();
	void setTimerCount(int count);
	int getTimerCount();

	bool getIsDelete();

	void createCollider(Type_Collider type = Type_Collider::Rectangle);
	void setColldier(CCollider* col);
	CCollider* getCollider();

	void addForce(Vec2 vec);

	virtual CMissile* createMissile(const wstring& image, Vec2 leftTop, Vec2 imageSize, Vec2 pos, 
		Vec2 size, Vec2 colSize, double speed, double angle, double damage, 
		Group_GameObj type, Type_Collider shape = Type_Collider::Rectangle);

	virtual void onCollisionEnter(CCollider* other) {};
	virtual void onCollisionStay(CCollider* other) {};
	virtual void onCollisionExit(CCollider* other) {} ;

	CAnimator* getAnimator();
	void setAnimator(CAnimator* ani);
	void createAnimator();

	void setColor(COLORREF color);
	void setImage(const wstring& name);
	void setImage(const wstring& name, Vec2 leftTop, Vec2 imageSize);
	void addAnimation(const wstring& name, Vec2 leftTop, Vec2 imageSize, double aniSpeed = 1, int frame = 1, bool loop = false, bool reverse = false);

	bool getIsRender();
	void setIsRender(bool render);

	void deleteComponent();
	virtual void setUpdateCallBack(BTN_FUNC1 pFunc1);

	void viewData();
};

