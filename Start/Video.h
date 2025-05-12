#pragma once

#include "Define.h"
#include "Scene.h"

class CVideo :public CScene
{
public:
	CVideo();
	~CVideo();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	DWORD m_dwSceneChange;

};

