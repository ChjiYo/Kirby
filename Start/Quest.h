#pragma once

#include "Define.h"
#include "Obj.h"

class CQuest:public CObj
{
public:
	CQuest();
	~CQuest();

public:
	void SetQuest() { m_bQuestAccept = true; }

public:
	void KillQuest();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	int m_iKillCount;
	bool m_bQuestClear;
	bool m_bQuestAccept;
	DWORD m_dwClearMsgTimer;
	bool m_bCreateCheck;
	bool m_bMsgCheck;
};

