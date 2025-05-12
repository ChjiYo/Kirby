#pragma once

#include "Define.h"
#include "Scene.h"

class CMini :public CScene
{
public:
	CMini();
	~CMini();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

