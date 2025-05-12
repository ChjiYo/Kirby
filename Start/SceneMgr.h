#pragma once

#include "Define.h"
#include "Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();

public:
	static CSceneMgr& GetInst()
	{
		static CSceneMgr Inst;
		return Inst;
	}


public:
	void		Scene_Change(SCENEID eID);
	void		Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

private:
	CScene*				m_pScene;

	SCENEID				m_ePreScene;
	SCENEID				m_eCurScene;
};

