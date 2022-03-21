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
	Spell,
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

enum class Group_Item
{
	Power,
	Spell,
	Life,
	Score,
	Size,
};

enum class Group_CharacterMode
{
	Sakuya,
	Remilia,

	Size
};

enum class Type_Event
{
	Create_Object,
	Delete_Object,
	Change_Scene,
	Delete_Component,

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
#define PL_STARTPOSX 200
#define PL_STARTPOSY (WS_HEIGHT-50)
#define MAX_MISSILE 200

extern bool g_isDeveloperMode;
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
extern Group_CharacterMode g_mode;


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
#include "CMissile.h"
class CEnemy;
extern CPlayer* g_player;

extern CMissile* g_missile[MAX_MISSILE];
extern int g_missileIndex;
extern CEnemy* g_boss;


#define DT() CTimeManager::getInstance()->getDeltaTime()
#define KEY(vk_key) CKeyManager::getInstance()->getButtonState(vk_key)
#define CREATEOBJECT(obj, type) CEventManager::getInstance()->createGameObject(obj, type)
#define DELETEOBJECT(obj) CEventManager::getInstance()->deleteGameObject(obj);
#define DELETECOMPONENT(obj) CEventManager::getInstance()->deleteComponent(obj);
#define CHANGESCENE(scene) CEventManager::getInstance()->changeScene(scene);
#define GETMOUSEPOS() CKeyManager::getInstance()->getMousePos();

#define PI 3.141592
#define RADIAN (PI/180)

//#define MAXSIZE_PATH 255

extern HINSTANCE hInst;
extern HWND hWnd;