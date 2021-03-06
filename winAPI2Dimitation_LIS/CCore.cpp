#pragma once
#include "pch.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CEnemy.h"

//전역변수
bool g_isDeveloperMode = true;
float g_volume = 1.0f;
float g_musicVolume = 1.0f;
int g_level = 0;
int g_score = 0;
int g_highScore = 0;
int g_life = 0;
int g_spell = 0;
int g_power = 0;
int g_graze = 0;
int g_point = 0;
int g_time = 0;
double g_progress = 0;
int g_continue = 0;
int g_miss = 0;
int g_bombUse = 0;
int g_spellBonus = 0;
Group_CharacterMode g_mode = Group_CharacterMode::Sakuya;
double g_omission = 0;
Group_GameState g_gameState = Group_GameState::Play;

CMissile* g_missile[MAX_MISSILE];
int g_missileIndex = 0;

CPlayer* g_player = nullptr;
CEnemy* g_boss = nullptr;

CCore::CCore()
{
	for (int i = 0; i < sizeof(g_missile) / sizeof(CMissile*); i++)
	{
		g_missile[i] = nullptr;
	}
}

CCore::~CCore()
{

}

void CCore::update()
{
	CEventManager::getInstance()->update();
	CTimeManager::getInstance()->update();
	CKeyManager::getInstance()->update();
	CSceneManager::getInstance()->update();
	CCollisionManager::getInstance()->update();
	CCameraManager::getInstance()->update();
	CSoundManager::getInstance()->update();
	CUIManager::getInstance()->update();	
}

void CCore::render()
{
	//배경
	if (g_gameState != Group_GameState::Movie)
	{
		CRenderManager::getInstance()->GetRenderTarget()->BeginDraw();
		CRenderManager::getInstance()->RenderFillRectangle(-1, -1, WS_WIDTH + 1, WS_HEIGHT + 1, RGB(255, 255, 255));
		CSceneManager::getInstance()->render();

		//frame 출력
		WCHAR strFPS[10];
		swprintf_s(strFPS, L"FPS:%4d", CTimeManager::getInstance()->getFPS());
		CRenderManager::getInstance()->RenderText(strFPS, WS_WIDTH - 150, WS_HEIGHT - 30, 200, 10, 30, RGB(255, 255, 255));
		CRenderManager::getInstance()->GetRenderTarget()->EndDraw();
	}
	
}

void CCore::init()
{
	CSoundManager::getInstance()->init();
	CTimeManager::getInstance()->init();
	CRenderManager::getInstance()->init();
	CSceneManager::getInstance()->init();
	CCameraManager::getInstance()->init();
	CCollisionManager::getInstance()->init();
	
	srand(time(0));
}
