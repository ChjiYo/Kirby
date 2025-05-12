#pragma once

#include "Define.h"
#include "Obj.h"

class CMetal :public CObj
{
public:
	CMetal();
	~CMetal();

public:
	void Inter();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();
};

