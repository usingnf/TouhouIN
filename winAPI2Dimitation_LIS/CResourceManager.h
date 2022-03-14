#pragma once
#include "CTexture.h"
#include "CSound.h"

class CResourceManager
{
	SINGLETON(CResourceManager);
private:
	map<wstring, CTexture*> textureData;
	map<wstring, CSound*> soundData;
	map<wstring, CD2DImage*> m_mapD2DImg;
public:
	//void init();
	CTexture* findTexture(const wstring& name);
	CTexture* loadTexture(const wstring& name, const wstring& path);
	CTexture* createTexture(const wstring& name, UINT width, UINT height);
	
	CSound* findSound(const wstring& name);
	CSound* loadBGM(const wstring& name, const wstring& path);
	CSound* loadSound(const wstring& name, const wstring& path);

	CD2DImage* findD2DImage(const wstring& name);
	CD2DImage* loadD2DImage(const wstring& name, const wstring& strRelativePath);
};

