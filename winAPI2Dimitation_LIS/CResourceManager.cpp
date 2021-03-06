#include "pch.h"
#include "CResourceManager.h"

CResourceManager::CResourceManager()
{
	textureData = { };
	soundData = {};
}

CResourceManager::~CResourceManager()
{
	for (map<wstring, CTexture*>::iterator iter = textureData.begin(); iter != textureData.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	textureData.clear();
	
	for (map<wstring, CSound*>::iterator iter = soundData.begin(); iter != soundData.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	soundData.clear();
}


CTexture* CResourceManager::findTexture(const wstring& name)
{
	map<wstring, CTexture*>::iterator iter = textureData.find(name);
	if (iter == textureData.end())
		return nullptr;
	return iter->second;
}


CTexture* CResourceManager::loadTexture(const wstring& name, const wstring& path)
{
	CTexture* texture = findTexture(name);
	if (texture != nullptr)
		return texture;

	
	wstring contentPath = CPathManager::getInstance()->getContentPath();
	contentPath += L"\\content\\texture\\";
	contentPath += path;

	texture = new CTexture();
	texture->load(contentPath);
	texture->setName(name);
	texture->setPath(path);


	textureData.insert(std::make_pair(name, texture));

	return texture;
}

CTexture* CResourceManager::createTexture(const wstring& name, UINT width, UINT height)
{
	CTexture* texture = findTexture(name);
	if (nullptr != texture)
		return texture;

	texture = new CTexture();
	texture->create(width, height);
	texture->setName(name);

	textureData.insert(std::make_pair(name, texture));

	return texture;
}

CSound* CResourceManager::findSound(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = soundData.find(name);
	if (iter == soundData.end())
		return nullptr;
	return iter->second;
}

CSound* CResourceManager::loadBGM(const wstring& name, const wstring& path)
{
	CSound* sound = findSound(name);
	if (sound != nullptr)
		return sound;

	wstring contentPath = CPathManager::getInstance()->getContentRelativePath();
	contentPath += L"\\sound\\";
	contentPath += path;

	sound = new CSound();
	sound->load(contentPath, true);
	sound->setName(name);
	sound->setPath(path);


	soundData.insert(std::make_pair(name, sound));

	return sound;
}

CSound* CResourceManager::loadSound(const wstring& name, const wstring& path)
{
	CSound* sound = findSound(name);
	if (sound != nullptr)
		return sound;

	wstring contentPath = CPathManager::getInstance()->getContentRelativePath();
	contentPath += L"\\sound\\";
	contentPath += path;

	sound = new CSound();
	sound->load(contentPath, false);
	sound->setName(name);
	sound->setPath(path);


	soundData.insert(std::make_pair(name, sound));

	return sound;
}


CD2DImage* CResourceManager::findD2DImage(const wstring& strKey)
{
	map<wstring, CD2DImage*>::iterator iter = m_mapD2DImg.find(strKey);

	if (m_mapD2DImg.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

CD2DImage* CResourceManager::loadD2DImage(const wstring& strKey, const wstring& strRelativePath)
{
	CD2DImage* pD2DImg = findD2DImage(strKey);
	if (nullptr != pD2DImg)
		return pD2DImg;

	wstring strFilePath = CPathManager::getInstance()->getContentRelativePath();
	strFilePath += strRelativePath;

	CD2DImage* img = new CD2DImage;

	IWICBitmapDecoder* p_decoder;		// ?????? ???????? ?????? ????
	IWICBitmapFrameDecode* p_frame;		// ???? ?????? ?????? ????
	IWICFormatConverter* p_converter;	// ?????? ???? ????

	// WIC?? Factory ?????? ???????? ?????? ???? ?????? ???? ?????? ????
	if (S_OK != CRenderManager::getInstance()->GetImageFactory()->CreateDecoderFromFilename(strFilePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// ?????? ???????? ?????? ?????? ?????? ???????? ????????.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap?????? ???????? ID2D1Bitmap. ???????? ???????? ???? ???? ????
	if (S_OK != CRenderManager::getInstance()->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// ?????? ?????? ???? ?????? ?????????? ?????? ?????? ????
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap ?????? ?????????? ID2D1Bitmap ?????? ????
	ID2D1Bitmap* bitmap = CRenderManager::getInstance()->GetBitmap();
	if (S_OK != CRenderManager::getInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// ?????????? ?????? ????
	img->setImage(bitmap);
	img->setName(strKey);
	img->setPath(strRelativePath);
	m_mapD2DImg.insert(std::make_pair(strKey.c_str(), img));

	p_converter->Release();		// ?????? ???? ???? ????
	p_frame->Release();			// ?????????? ???? ???????? ???????? ???? ?????? ???? ????
	p_decoder->Release();		// ?????? ???????? ???? ?????? ???? ????

	return img;
}

