#pragma once
#include "CResource.h"
class CTexture : public CResource
{
private:
	HDC hDC;
	HBITMAP hBitmap;
	BITMAP hBitmapInfo;

public:
	CTexture();
	virtual ~CTexture();

	void load(const wstring& path);
	void create(UINT width, UINT height);

	HDC& getDC();
	HBITMAP getBitmap();
	BITMAP getBitmapInfo();
	int getBitmapWidth();
	int getBitmapHeight();
};

