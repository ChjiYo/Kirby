#pragma once

#include "Define.h"
#include "Obj.h"

class CDoor:public CObj
{
public:
	CDoor();
	virtual ~CDoor();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

