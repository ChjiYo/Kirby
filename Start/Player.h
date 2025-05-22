#pragma once

#include "Obj.h"
#include "Define.h"

class CPlayer :public CObj
{
public:
	enum STATE { IDLE, WALK,SIT,JUMP,FLY,HIT,LAND, INHAL, INHALTRUE, INHAL_FALSE ,ATTACK,INHAL_IDLE, INHAL_WALK, ABSORB ,TACKLE,TEST,V_WALK , LAND_AIR,PORTAL, WATER_IDLE , WATER_WALK , WATER_UP, WATER_DOWN,STATE_END };

protected:
	CPlayer();
	virtual ~CPlayer();

protected:
	void KeyInput();
	void Jump();
	void Land();
	void OffSet();
	void Inhal();
	void Hit();
	void Tackle();

public:
	void SetID(MONID _MonID) { m_eMonsterID = _MonID; }

	void SetLeftFrameKey(const TCHAR* _eKey) { m_eLeftKey = _eKey; }
	void SetRightFrameKey(const TCHAR* _eKey) { m_eRightKey = _eKey; }

	char GetDir() { return m_szMoveDir; }
	void SetStateHit() { m_eCurState = HIT; }

	void SetMapCheck() { m_bMapCheck = false; }
	bool GetMapCheck() { return m_bMapCheck; }

	virtual void SetHp(int _iHp) { m_iHp += _iHp; }
	virtual int GetHp() {return m_iHp; }

	virtual void SetMoney(int _iMoney) { m_iMoney += _iMoney; }
	virtual int GetMoney() { return m_iMoney; }

	virtual void SetHpInput(int _iHp) { m_iHp = _iHp; }
	virtual void SetMoneyInput(int _iMoney) { m_iMoney = _iMoney; }

	bool GetInhal() { return m_bInputKeyCheck; }

	virtual PLAYERID GetPlayerID() { return m_ePlayerID; }
	//void SetDamage();

private:
//키 할당

//Axis 
	void BindAxis_LEFT();
	void BindAxis_RIGHT();
	void BindAxis_DOWN();
	void BindAxis_MONE();

//Action
	void BindAction_JUMP();
	void BindAction_TACKLE();
	void BindAction_ESCAPE();
	void BindAction_ATTACK();

	void BindAxis(int _iKey);
	void BindAction(int _iKey);

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

protected:
	//충돌처리
	float m_fPower;
	float m_fTime;

	bool m_bJump;
	bool m_bAirAttack;

	STATE			m_eCurState;
	STATE			m_ePreState;

	float m_fWidth;
	float m_fHeight;
	float m_fDiagonal;
	float m_fRadian;

	MONID m_eMonsterID;

	const TCHAR* m_eLeftKey;
	const TCHAR* m_eRightKey;

	char m_szMoveDir; // 조심

	DWORD m_fTackleTimer;

	int m_iHp;
	
	int m_iMapCount;

	bool m_bFlyCheck;
	float m_bFlyTimer;
	DWORD m_dwFlyTimer;

	int iJumpCount;

	int m_iInhalCount;
	DWORD m_dwInhalTime;

	bool m_bMapCheck;

	DWORD m_dwHitTimer;
	DWORD m_dwEpicHitTimer;

	int m_iNowHp;
	float m_fVolume;

	bool m_bHitCheck;

	DWORD m_dwHitIdleTimer;

	bool m_bInputKeyCheck;

	DWORD m_bWalkTimer;
	
	int m_iMoney;

	PLAYERID m_ePlayerID;

	DWORD m_dwLandTimer;

	int m_iNowMoney;
	
};

