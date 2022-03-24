#pragma once
class CSpell : public CGameObject
{
public:
	CSpell();
	virtual CSpell* clone();
	virtual ~CSpell();

	virtual void update();
	virtual void render();

	virtual void die();
};

