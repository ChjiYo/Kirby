#pragma once

#include "Define.h"
#include "Scene.h"
#include "StageA.h"

class CStageA4 :public CStageA
{
public:
	CStageA4();
	virtual ~CStageA4();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

