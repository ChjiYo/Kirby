#pragma once

#include "Define.h"
#include "Stage.h"

class CStageA1 :public CStage
{
public:
	CStageA1();
	virtual ~CStageA1();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	bool m_bCheck;
	int m_iSize;
};


