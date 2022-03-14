#include "pch.h"
#include "CD2DImage.h"

CD2DImage::CD2DImage()
{
	m_pBitmap = nullptr;
}

CD2DImage::~CD2DImage()
{
}

ID2D1Bitmap* CD2DImage::getImage()
{
	return m_pBitmap;
}

void CD2DImage::setImage(ID2D1Bitmap* bitmap)
{
	m_pBitmap = bitmap;
}

int CD2DImage::getWidth()
{
	return (int)m_pBitmap->GetSize().width;
}

int CD2DImage::getHeight()
{
	return (int)m_pBitmap->GetSize().height;
}