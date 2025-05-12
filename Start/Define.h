#pragma once

using namespace std;

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

#define SCALE_X 800
#define SCALE_Y 600

#define PUSE = 0 
#define PI 3.14f

#define OBJ_NOEVENT 0
#define OBJ_DISTORY 1

#define PLAYER_DEF 0
#define PLAYER_INHAL 1

#define	VK_MAX	0xff

#include <Windows.h>
#include <list>
#include <vector>
#include <map>
#include <time.h>
#include <algorithm>

#include <io.h>
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE , SC_UI ,SC_VEDEO,SC_END };
enum UIID{ UI_RSP , UI_END, };
enum STAGEID { STAGE_A1, STAGE_A2, STAGE_A3, STAGE_A4, STAGE_END};
enum CHANNELID { SOUND_EFFECT, SOUND_BGM, MAXCHANNEL };

enum DIRECTION2
{
	LEFT, RIGHT, END
};

enum MONID
{
	MON_NONE = 1,
	MON_SPARKY,
	MON_GUNTER,
	MON_SLEEPY,
	MON_END
};

enum OBJID
{
	OBJ_ATTACK,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_SPECIAL_MONSTER,
	OBJ_UI,
	OBJ_ITEM,
	OBJ_ITEMLIST,
	OBJ_MONATTACK,
	OBJ_DOOR,
	OBJ_NPC,
	OBJ_TEMP,
	OBJ_MOUSE,
	OBJ_PET,
	OBJ_END
};

enum NPCID
{
	NPC_RSP,
	NPC_PUZZLE,
	NPC_END
};

enum PLAYERID
{
	PLAYER_CLASIC,
	PLAYER_ICE,
	PLAYER_SPARK,
	PLAYER_SLEEP,
	PLAYER_END
};

enum ITEMID
{
	ITEM_MEAT,
	ITEM_TOMATO,
	ITEM_CANDY,
	ITEM_PET_GOUSE,
	ITEM_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_MONSTER,
	RENDER_EFFECT,
	RENDER_GAMEOBJECT,
	RENDER_FRONTEFFECT,
	RENDER_PRONTUI,
	RENDER_ITEM,
	RENDER_UI,
	RENDER_END
};

struct INFO
{
	float fX;
	float fY;
	float fCX;
	float fCY;
};

struct LINEPOINT
{
	float fX;
	float fY;

	LINEPOINT() { ZeroMemory(this, sizeof(LINEPOINT)); }
	LINEPOINT(float _fX, float _fY) : fX(_fX), fY(_fY) {}
};


struct LINEINFO
{
	LINEPOINT tLeft;
	LINEPOINT tRight;

	LINEINFO() { ZeroMemory(this, sizeof(LINEINFO)); }
	LINEINFO(LINEPOINT& _tLeft , LINEPOINT& _tRight) :
		tLeft(_tLeft), tRight(_tRight){ }
};

struct FRAME
{
	int iFrameStart;
	int iFrameEnd;
	int iMotion;
	DWORD dwSpeed;
	DWORD dwTime;
};

template<typename T>
void Safe_Delete(T& _Type)
{
	if (_Type)
	{
		delete _Type;
		_Type = nullptr;
	}
}

extern HWND g_hWnd;

