#pragma once
class CText : public CUI
{
private:
	WCHAR mtext[40] = L"";
	float fontSize;
	
public:
	CText();
	virtual CText* clone();
	~CText();
	virtual void update();
	virtual void render(HDC& hDC);
	void setText(const WCHAR* text);
	void setSize(float size);
};

