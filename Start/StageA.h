#pragma once

#include "Define.h"
#include "Scene.h"
#include "Stage.h"

class CStageA :public CStage
{
public:
	CStageA();
	virtual ~CStageA();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

};

