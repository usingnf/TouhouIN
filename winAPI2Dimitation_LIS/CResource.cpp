#include "pch.h"
#include "CResource.h"

CResource::CResource()
{
}

CResource::~CResource()
{
}

void CResource::setName(const wstring& name)
{
	this->resourceName = name;
}

void CResource::setPath(const wstring& path)
{
	this->filePath = path;
}

const wstring& CResource::getName()
{
	return resourceName;
}

const wstring& CResource::getPath()
{
	return filePath;
}
