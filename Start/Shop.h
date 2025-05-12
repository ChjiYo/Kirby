#pragma once

#include "Define.h"
#include "ObjMgr.h"

class CShop :public CObj
{
public:
	CShop();
	~CShop();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	vector<ITEMID>	VecItem;
	int m_iStartX;
	int m_iStartY;

	bool CreateCheck;
};

