#pragma once

class CAnimator;
class CTexture;
class CD2DImage;

struct tAniFrame
{
	Vec2 leftTop;
	Vec2 slice;
	Vec2 fptOffset;
	float duration;
};

class CAnimation
{
	friend class CAnimator;
private:
	wstring name;
	CAnimator* animator;
	//CTexture* texture;
	CD2DImage* image;
	vector<tAniFrame> vecFrame;
	
	int curFrame;
	double accTime;
	bool isLoop;
	float angle;
	bool reverse;
public:
	CAnimation();
	~CAnimation();

	void setLoop(bool b);
	bool getLoop();

	void setName(const wstring& name);
	const wstring& getName();

	void SetFrame(int frmIndex);
	tAniFrame& GetFrame(int frmIndex);

	void update();
	void render(HDC& hDC);

	void create(CD2DImage* tex, Vec2 lt, Vec2 slice, Vec2 step, float duration, UINT frmCount);
	void setReverse(bool reverse);
	//void create(CTexture* tex, Vec2 leftTop, Vec2 slice, Vec2 step, float duration, UINT frameCount);
};

