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

	wstring contentPath = CPathManager::getInstance()->getContentPath();
	contentPath += L"\\content\\sound\\";
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
	// CD2DImage 키 값을 통해 탐색
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

	IWICBitmapDecoder* p_decoder;		// 압축된 이미지를 해제할 객체
	IWICBitmapFrameDecode* p_frame;		// 특정 그림을 선택한 객체
	IWICFormatConverter* p_converter;	// 이미지 변환 객체

	// WIC용 Factory 객체를 사용하여 이미지 압축 해제를 위한 객체를 생성
	if (S_OK != CRenderManager::getInstance()->GetImageFactory()->CreateDecoderFromFilename(strFilePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder))
	{
		assert(nullptr);
	}
	// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
	if (S_OK != p_decoder->GetFrame(0, &p_frame))
	{
		assert(nullptr);
	}
	// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
	if (S_OK != CRenderManager::getInstance()->GetImageFactory()->CreateFormatConverter(&p_converter))
	{
		assert(nullptr);
	}
	// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정
	if (S_OK != p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom))
	{
		assert(nullptr);
	}
	// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성
	ID2D1Bitmap* bitmap = CRenderManager::getInstance()->GetBitmap();
	if (S_OK != CRenderManager::getInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &bitmap))
	{
		assert(nullptr);
	}

	// 성공적으로 생성한 경우
	img->setImage(bitmap);
	img->setName(strKey);
	img->setPath(strRelativePath);
	m_mapD2DImg.insert(std::make_pair(strFilePath.c_str(), img));

	p_converter->Release();		// 이미지 변환 객체 제거
	p_frame->Release();			// 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
	p_decoder->Release();		// 압축을 해제하기 위해 생성한 객체 제거

	return img;
}

