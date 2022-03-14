#pragma once
class CResource
{
private:
	wstring filePath;
	wstring resourceName;
public:
	CResource();
	virtual ~CResource();

	void setName(const wstring& name);
	void setPath(const wstring& path);
	const wstring& getName();
	const wstring& getPath();
};

