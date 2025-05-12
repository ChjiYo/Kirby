#pragma once

#include "Define.h"
#include "Item.h"

class CItem_Now:public CItem
{
public:
	CItem_Now();
	~CItem_Now();

public:
	ITEMID GetItemID() { return m_eItemID; }
	void SetItemID(ITEMID _eItemID) { m_eItemID = _eItemID; }

	void Land();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	ITEMID m_eItemID;
	HDC	m_hItemMemDC;
	float m_fTime;
};

