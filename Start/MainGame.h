#pragma once

#include "Define.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	HDC m_hDC;

	DWORD			m_dwTime;
	int				m_iFPS;
	TCHAR			m_szFPS[16];
};

