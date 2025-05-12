#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize()			PURE;
	virtual int Update()				PURE;
	virtual void LateUpdate()			PURE;
	virtual void Render(HDC _hDC)		PURE;
	virtual void Release()				PURE;
};

