#pragma once
class CText : public CUI
{
private:
	WCHAR mtext[40] = L"";
	float fontSize;
	Type_TextHeightAlignment heightAlign = Type_TextHeightAlignment::Center;
	Type_TextWidthAlignment widthAlign = Type_TextWidthAlignment::Left;
	
public:
	CText();
	virtual CText* clone();
	~CText();
	virtual void update();
	virtual void render();
	void setText(const WCHAR* text);
	void setSize(float size);
	void setHeightAlignment(Type_TextHeightAlignment align);
	void setWidthAlignment(Type_TextWidthAlignment align);
};

