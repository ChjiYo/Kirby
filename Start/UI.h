#pragma once

#include "Define.h"
#include "Obj.h"
#include "Scene.h"

class CUI :public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

