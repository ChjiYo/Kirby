#pragma once

#include "Define.h"
#include "Obj.h"

class CTemp:public CObj
{
public:
	CTemp();
	~CTemp();

public:
	void Initialize();
	int  Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();
};

