#pragma once
class CText : public CGameObject
{
private:
	WCHAR mtext[20] = L"";
public:
	CText();
	virtual CText* clone();
	~CText();
	virtual void update();
	virtual void render(HDC& hDC);
	void setText(const WCHAR* text);
};

