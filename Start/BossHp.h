#pragma once

#include "Define.h"
#include "Obj.h"

class CBossHp :public CObj
{
public:
	CBossHp();
	virtual ~CBossHp();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	int m_iBossHp;
};

