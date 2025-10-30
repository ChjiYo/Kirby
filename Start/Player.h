#pragma once

#include "Obj.h"
#include "Define.h"

class CPlayer :public CObj
{
public:
	enum  STATE { IDLE, WALK,SIT,JUMP,FLY,HIT,LAND, INHAL, ATTACK, TACKLE,V_WALK , LAND_AIR,PORTAL, WATER_IDLE , WATER_WALK , WATER_UP, WATER_DOWN,STATE_END };


protected:
	CPlayer();
	virtual ~CPlayer();

protected:
	virtual void KeyInput();

protected:
	void Jump();
	void Land();
	void OffSet();
	void Hit();
	void Tackle();

protected:
	virtual void WaterMove() PUSE;
	virtual void LRKey() PUSE;

public:
	void SetID(MONID _MonID) { m_eMonsterID = _MonID; }

	char GetDir() { return m_szMoveDir; }

	virtual void SetHp(int _iHp) { m_iHp += _iHp; }
	virtual int GetHp() {return m_iHp; }

	virtual void SetMoney(int _iMoney) { m_iMoney += _iMoney; }
	virtual int GetMoney() { return m_iMoney; }

	virtual void SetHpInput(int _iHp) { m_iHp = _iHp; }
	virtual void SetMoneyInput(int _iMoney) { m_iMoney = _iMoney; }

	bool GetInhal() { return m_bInputKeyCheck; }

	virtual PLAYERID GetPlayerID() { return m_ePlayerID; }
	

//키 할당

//Axis 
protected:
	void BindAxis_LEFT(STATE eTpye  = WALK);
	void BindAxis_RIGHT(STATE eTpye = WALK);
	void BindAxis_MONE(STATE eTpye = IDLE);
	void BindAxis_DOWN();
	void BindAxis_JUMP_LEFT();
	void BindAxis_JUMP_RIGHT();

private :
//Action
	void BindAction_JUMP();
	void BindAction_TACKLE();
	void BindAction_ESCAPE();
	void BindAction_ATTACK();
	void BindAction_ITEM();

protected:
	void BindPressing(int _iKey);
	void BindDown(int _iKey);
	void MultyBindAction(int _iFirstKey, int _iSecondKey);

public:
	virtual void MotionChange() PUSE;
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

	bool m_bTackle;

	STATE			m_eCurState;
	STATE			m_ePreState;

	MONID m_eMonsterID;

	char m_szMoveDir; // 조심

	DWORD m_fTackleTimer;

	int m_iHp;
	
	int iJumpCount;

	DWORD m_dwInhalTime;
	bool m_bInhalCheck;

	DWORD m_dwHitTimer;
	DWORD m_dwEpicHitTimer;

	int m_iNowHp;
	float m_fVolume;

	bool m_bHitCheck;

	bool m_bInputKeyCheck;

	DWORD m_bWalkTimer;
	PLAYERID m_ePlayerID;

	//Money
	int m_iMoney;
	int m_iNowMoney;
	
};

