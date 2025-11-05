#pragma once

#include "Define.h"
#include "Obj.h"

class CShop_Item :public CObj
{
public:
	CShop_Item();
	virtual ~CShop_Item();

public:
	virtual void SetItemID(ITEMID _eItemID) {
		m_eItemID = _eItemID;
	}

private:
	void ClickBuy();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	ITEMID m_eItemID;
	HDC	m_hItemMemDC;
	int m_iPrice;
};

