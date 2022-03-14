#pragma once

//함수포인터를 위한 타입 정의
typedef void(*BTN_FUNC)(DWORD_PTR, DWORD_PTR);


class CButtonUI : public CUI
{
private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_pParam1;
	DWORD_PTR m_pParam2;

public:
	CButtonUI();
	virtual CButtonUI* Clone();
	~CButtonUI();
	

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	void setClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);
};

