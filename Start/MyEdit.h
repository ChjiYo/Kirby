#pragma once

#include "Define.h"
#include "Scene.h"

class CMyEdit : public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	void	Key_Input();

};

