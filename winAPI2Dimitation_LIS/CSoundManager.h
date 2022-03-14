#pragma once
#include "FMOD/inc/fmod.hpp"
#include "CResource.h"
#include "CSound.h"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSound;

class CSoundManager
{
	SINGLETON(CSoundManager);
private:
	map<wstring, CSound*> mapSound;
	System* m_system;
	
public:
	void init();
	void update();

	System* getSystem();

	void addSound(const wstring& name, const wstring& path, bool isBGM, bool isLoop);
	
	void play(const wstring& name);
	void stop(const wstring& name);
	void pause(const wstring& name);
	void resume(const wstring& name);

	bool isPlaying(const wstring& name);
	bool isPaused(const wstring& name);

};

