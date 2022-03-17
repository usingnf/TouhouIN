#pragma once

#include "framework.h"
// 기본 추가 기능
#include <string>
#include <vector>
#include <list>
#include <map>
#include <chrono>
#include <assert.h>

using std::vector;
using std::list;
using std::map;
using std::string;
using std::wstring;

enum class Group_GameObj
{
	Default,
	Background,
	Tile,
	Effect,
	Enemy,
	Item,
	Body,
	Player,
	Missile,
	EnemyMissile,
	UI,

	Size,
};

enum class Group_Scene
{
	Default,
	Stage_Tile,
	Start,
	Stage_01,
	Stage_02,
	Result,
	End,
	Size,
};

enum class Type_Event
{
	Create_Object,
	Delete_Object,
	Change_Scene,

	Size,
};

enum class Key_State
{
	None,
	Tap,
	Hold,
	Off,
};

#define WS_MYSTYLE WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
#define WS_WIDTH 642
#define WS_HEIGHT 482
#define WS_STARTX 100
#define WS_STARTY 100
#define STAGE_WIDTH (400)
#define STAGE_HEIGHT (WS_HEIGHT - 20)

extern int g_level;
extern int g_score;
extern int g_highScore;
extern int g_life;
extern int g_spell;
extern int g_power;
extern int g_graze;
extern int g_point;
extern int g_time;
extern double g_progress;
extern int g_continue;
extern int g_miss;
extern int g_bombUse;
extern int g_spellBonus;
extern double g_omission;


#include "Vec2.h"
#include "logger.h"
#include "SelectGDI.h"
#include "CCore.h"
#include "CSingleton.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CPathManager.h"
#include "CRenderManager.h"
#include "CResourceManager.h"

#include "CSoundManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CGameObject.h"
#include "CSceneManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"

class CPlayer;
extern CPlayer* g_player;


#define DT() CTimeManager::getInstance()->getDeltaTime()
#define KEY(vk_key) CKeyManager::getInstance()->getButtonState(vk_key)
#define CREATEOBJECT(obj, type) CEventManager::getInstance()->createGameObject(obj, type)
#define DELETEOBJECT(obj) CEventManager::getInstance()->deleteGameObject(obj);
#define CHANGESCENE(scene) CEventManager::getInstance()->changeScene(scene);
#define GETMOUSEPOS() CKeyManager::getInstance()->getMousePos();

#define PI 3.141592
#define RADIAN (PI/180)

//#define MAXSIZE_PATH 255

extern HINSTANCE hInst;
extern HWND hWnd;

class CPlayer;
class CPlayer_Right;
class CBall;
//extern CPlayer* leftPlayer;
//extern CPlayer_Right* rightPlayer;
//extern CBall* ball;
//CPlayer* leftPlayer = new CPlayer();
//CPlayer_Right* rightPlayer = nullptr;
//CBall* ball = nullptr;