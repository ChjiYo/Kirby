#pragma once

#include "Define.h"
#include "Stage.h"

class CStageMgr
{
private:
	CStageMgr();
	~CStageMgr();

public:
	static CStageMgr& GetInst()
	{
		static CStageMgr Inst;
		return Inst;
	}

public:
	STAGEID GetCurStage() { return m_eCurStage; }

public:
	void StageChage(STAGEID eID);
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	CStage* m_pStage;

	STAGEID				m_ePreStage;
	STAGEID				m_eCurStage;

};

