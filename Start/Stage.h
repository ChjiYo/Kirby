#pragma once

#include "Define.h"
#include "Scene.h"

class CStage :public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

protected:
	float m_fVolume;
};

