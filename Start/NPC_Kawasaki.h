#pragma once

#include "Define.h"
#include "Obj.h"

class CNPC_Kawasaki :public CObj
{
public:
	CNPC_Kawasaki();
	~CNPC_Kawasaki();

public:
	void Inter();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

