#pragma once
class CPathManager
{
	SINGLETON(CPathManager);
public:
	const static int MAXSIZE_PATH = 255;
private:
	WCHAR szContentPath[MAXSIZE_PATH];
public:
	const WCHAR* getContentPath();
	const WCHAR* getContentRelativePath();
};

