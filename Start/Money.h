#pragma once

#include "Define.h"
#include "Obj.h"

class CMoney : public CObj
{
public:
	CMoney();
	~CMoney();

public:
	int GetMoney() { return m_iMoney; }
	void SetMoney(int _iMoney) { m_iMoney += _iMoney; }
public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	int m_iMoney;
};

