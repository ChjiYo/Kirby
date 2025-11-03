#include "StageA1.h"
#include "ObjMgr.h"
#include "Factory.h"
#include "Player.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "LineMgr.h"
#include "Player_Origin.h"
#include "Player_Spark.h"
#include "Door.h"
#include "CollisionMgr.h"
#include "Monster_Sparky.h"
#include "Monster_Gunter.h"
#include "UI.h"
#include "Ability.h"
#include "PlayerHp.h"
#include "SoundMgr.h"

#include "NPC_Kawasaki.h"

#include "Player_Rock.h"

#include "Wadle.h"
#include "Mouse.h"
#include "NPC_Mario.h"
#include "KeyMgr.h"
#include "Money.h"
#include "Quest.h"
#include "Metal.h"

CStageA1::CStageA1()
{
	m_bCheck = true;
	m_iSize = 0;
}

CStageA1::~CStageA1()
{
	Release();
}

void CStageA1::Initialize()
{
	m_fVolume = 1.f;
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Map/Stage1/Map_NewStage1.bmp", L"Ground");
	CBmpMgr::GetInst().InsertBmp(L"../Kirby/Back/Back_StagaA1.bmp", L"Back_Ground");

	CScrollMgr::GetInst().SetScrollX();
	CScrollMgr::GetInst().SetScrollY();

	//CObjMgr::GetInst().Delete_ID(OBJ_UI);
	CObjMgr::GetInst().GetObjectList(OBJ_UI).back()->SetDead();

	CLineMgr::GetInst().Load_Line();

	CObjMgr::GetInst().Add_Create(OBJ_PLAYER, CFactory<CPlayer_Origin>::Create());
	CObjMgr::GetInst().Add_Create(OBJ_MOUSE, CFactory<CMouse>::Create());

	CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CMonster_Sparky>::Create(1950 ,330));
	//CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CMonster_Sparky>::Create(1900, 330));

	CObjMgr::GetInst().Add_Create(OBJ_MONSTER, CFactory<CWadle>::Create(3900.f, 320.f));

	CObjMgr::GetInst().Add_Create(OBJ_NPC, CFactory<CNPC_Kawasaki>::Create(2320, 350));
	CObjMgr::GetInst().Add_Create(OBJ_NPC, CFactory<CMetal>::Create(800, 350));

	CObjMgr::GetInst().Add_Create(OBJ_DOOR, CFactory<CDoor>::Create(4645.f,380.f));
	CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CPlayerHp>::Create());
	CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CAbility>::Create());
	CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CMoney>::Create());
	CObjMgr::GetInst().Add_Create(OBJ_UI, CFactory<CQuest>::Create());

	//CObjMgr::GetInst().Add_Create(OBJ_NPC, CFactory<CNPC_Mario>::Create(800.f, 400.f));

	m_iSize = CObjMgr::GetInst().GetObjectList(OBJ_MONSTER).size();

	//CSoundMgr::GetInst().PlayBGM(L"Normal.wav", m_fVolume);
}

int CStageA1::Update()
{
	CObjMgr::GetInst().Update();
	return 0;
}

void CStageA1::LateUpdate()
{
	CObjMgr::GetInst().LateUpdate();
}

void CStageA1::Render(HDC _hDC)
{
	HDC	hBackGroundDC = CBmpMgr::GetInst().FindImage(L"Back_Ground");
	HDC	hGroundDC = CBmpMgr::GetInst().FindImage(L"Ground");

	int iScrollX = (int)CScrollMgr::GetInst().GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInst().GetScrollY();

	BitBlt(_hDC, 0, 0, 800, 600, hBackGroundDC, 0, 0, SRCCOPY);
	
	GdiTransparentBlt(
		_hDC,
		iScrollX,
		iScrollY,
		4761,
		600,
		hGroundDC,
		0,
		0,
		4761,
		600,
		RGB(0,18, 127));

	CObjMgr::GetInst().Render(_hDC);

	/*TCHAR		szHp[64] = L"";

	swprintf_s(szHp, L"Candy : %d " , dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetObjectList(OBJ_PLAYER).back())->GetMoney());
	TextOut(_hDC, 400, 100, szHp, lstrlen(szHp));*/
}

void CStageA1::Release()
{	
	int iDebug(0);
}
