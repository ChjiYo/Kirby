#pragma once

#include "Define.h"
#include "Obj.h"

class CButton :public CObj
{
public:
	CButton();
	virtual ~CButton();

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	int m_iDrawID;
};

