#pragma once

#include "Define.h"
#include "Scene.h"

class CLogo :public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

