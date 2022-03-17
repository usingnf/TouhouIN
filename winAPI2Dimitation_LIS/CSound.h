#pragma once

#include "FMOD/inc/fmod.hpp"
#include "CResource.h"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSound : public CResource
{
private:
	Sound* m_sound;
	Channel* m_channel;
public:
	CSound();
	~CSound();
	
	void play(float volume = 1.f);
	void stop();
	void pause();
	void resume();

	bool IsPlaying();
	bool IsPaused();

	void SetLoop(bool loop);

	void load(const wstring& path, bool isBGM);

};

