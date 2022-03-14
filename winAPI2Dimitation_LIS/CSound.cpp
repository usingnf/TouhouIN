#include "pch.h"
#include "CSound.h"

CSound::CSound()
{
	m_sound = nullptr;
	m_channel = nullptr;
}

CSound::~CSound()
{
	stop();

	if (nullptr != m_sound)
	{
		m_sound->release();
		//delete m_sound;
	}
}

void CSound::play()
{
	FMOD_RESULT result;
	result = CSoundManager::getInstance()->getSystem()->playSound(m_sound, nullptr, false, &m_channel);
	assert(!result);
}

void CSound::stop()
{
	if(m_channel != nullptr)
		m_channel->stop();
}

void CSound::pause()
{
	if (m_channel != nullptr)
		m_channel->setPaused(true);
}

void CSound::resume()
{
	if (m_channel != nullptr)
		m_channel->setPaused(false);
}

bool CSound::IsPlaying()
{
	bool playing = false;
	if (nullptr != m_channel)
		m_channel->isPlaying(&playing);

	return playing;
}

bool CSound::IsPaused()
{
	bool paused = false;
	if (nullptr != m_channel)
		m_channel->getPaused(&paused);

	return paused;
}

void CSound::SetLoop(bool loop)
{
	if (loop == true)
	{
		m_sound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		m_sound->setMode(FMOD_LOOP_OFF);
	}
	
}

void CSound::load(const wstring& path, bool isBGM)
{
	FMOD_RESULT result;

	char str[255];
	wcstombs_s(nullptr, str, path.c_str(), 255);

	
	if (isBGM == true)
	{
		result = CSoundManager::getInstance()->getSystem()->createStream(str, FMOD_DEFAULT, nullptr, &m_sound);
	}
	else
	{
		result = CSoundManager::getInstance()->getSystem()->createSound(str, FMOD_LOOP_OFF, nullptr, &m_sound);
	}
	assert(!result);
}
