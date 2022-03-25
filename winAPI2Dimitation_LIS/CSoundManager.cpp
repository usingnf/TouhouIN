#include "pch.h"
#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
	m_system = nullptr;
}

CSoundManager::~CSoundManager()
{
	m_system->release();
	m_system->close();
}

void CSoundManager::init()
{
	FMOD_RESULT result;
	result = System_Create(&m_system);
	assert(!result);
	result = m_system->init(32, FMOD_INIT_NORMAL, nullptr);
	assert(!result);
	
}

void CSoundManager::update()
{
	//must do update per frame.
	m_system->update();
}

System* CSoundManager::getSystem()
{
	return m_system;
}

void CSoundManager::addSound(const wstring& name, const wstring& path, bool isBGM, bool isLoop)
{
	CSound* sound = nullptr;

	if (isBGM == true)
	{
		sound = CResourceManager::getInstance()->loadBGM(name, path);
	}
	else
	{
		sound = CResourceManager::getInstance()->loadSound(name, path);
	}
	if (sound != nullptr)
	{
		sound->SetLoop(isLoop);
		mapSound.insert(std::make_pair(name, sound));
	}
}

void CSoundManager::play(const wstring& name, float volume)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
		return;
	iter->second->play(volume);
}

void CSoundManager::playMusic(const wstring& name, float volume)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
		return;
	iter->second->playMusic(volume);
}

void CSoundManager::stop(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
	{
		return;
	}
	iter->second->stop();
}

void CSoundManager::pause(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
	{
		return;
	}
	iter->second->pause();
}

void CSoundManager::resume(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
	{
		return;
	}
	iter->second->resume();
}

bool CSoundManager::isPlaying(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
	{
		return false;
	}
	
	return iter->second->IsPlaying();

}

bool CSoundManager::isPaused(const wstring& name)
{
	map<wstring, CSound*>::iterator iter = mapSound.find(name);
	if (iter == mapSound.end())
	{
		return false;
	}

	return iter->second->IsPaused();
}

Channel* CSoundManager::getMusicChannel()
{
	return this->m_musicChannel;
}

void CSoundManager::setMusicChannel(Channel* channel)
{
	this->m_musicChannel = channel;
}