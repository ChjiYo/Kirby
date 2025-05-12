#pragma once

#include "Define.h"
#include "Scene.h"

class CMyMenu :public CScene
{
public:
	CMyMenu();
	virtual ~CMyMenu();


public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

