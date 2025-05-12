#pragma once

#include "Define.h"
#include "Obj.h"

class CMonster :public CObj
{
protected:
	enum STATE{IDLE,WALK,ATTACK,INHAL, JUMP ,WAIT , ABILITY , DIE};
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void SetHp(int m_iDamage) { m_iHp += m_iDamage; }
	const MONID&  GetID()const { return m_eMonID; }
	virtual void KillCount() { m_iKillCount++; }
	int GetKillCount() { return m_iKillCount; }
	
	virtual int GetHp() { return m_iHp; }
	virtual void MotionChage() {};
public:
	virtual void Initialize() {};
	virtual int Update() { return OBJ_NOEVENT; }
	virtual void LateUpdate() {};
	virtual void Render(HDC _hDC) {};
	virtual void Release() {};

	virtual void Move();
	virtual  void Hit();
	bool Inhal();

	virtual void SetStage(STATE _eID) { m_eCurState = _eID; }

protected:
	STATE			m_eCurState;
	STATE			m_ePreState;

	MONID m_eMonID;

	int m_iHp;
	float m_fInhalSpeed;

	bool m_bInhalMoveStop;

	int m_iKillCount;
};

