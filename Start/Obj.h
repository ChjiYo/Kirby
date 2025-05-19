#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void RectUpdate();
	void MoveFrame();

public:
	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }

public:
	const INFO& GetInfo() const{ return m_tInfo; }
	const RECT& GetRect() const{ return m_tRect; }
	const bool& GetDead() const { return m_bDead; }
	const TCHAR* GetKey() { return m_pFrameKey;}

	float GetSpeed() { return m_fSpeed; }

	void SetObjPos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}

	void SetInhalPos(float _fX)
	{
		m_tInfo.fX += _fX;
	}

	RENDERID	Get_RenderID() { return m_eRender; }

	char GetDirKey() { return m_szMoveDir; } // Check

	void SetAngle(float _fAngle) { m_fAngle = _fAngle; }

	void SetDead() { m_bDead = true; }
	void SetFrameKey(const TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }

	void SetPlayerChange(CObj* m_pPlayer) { m_pChange = m_pPlayer; }

	FRAME GetfRAME() {return m_tFrame;}

public:
	virtual void Initialize()		PURE;
	virtual int Update()			PURE;
	virtual void LateUpdate()		PURE;
	virtual void Render(HDC _hDC)	PURE;
	virtual void Release()			PURE;

protected:
	INFO m_tInfo;
	RECT m_tRect;

	float m_fSpeed;
	bool m_bDead;

	FRAME m_tFrame;
	const TCHAR* m_pFrameKey;

	float m_fAngle;
	RENDERID	m_eRender;

	CObj* m_pTarget;
	CObj* m_pChange;

	char m_szMoveDir;
};

