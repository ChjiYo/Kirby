#include "Door.h"

CDoor::CDoor()
{
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Initialize()
{
	m_tInfo.fCX = 35.f;
	m_tInfo.fCY = 60.f;

	m_eRender = RENDER_GAMEOBJECT;
}

int CDoor::Update()
{

	__super::RectUpdate();

	return OBJ_NOEVENT;
}

void CDoor::LateUpdate()
{
}

void CDoor::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CDoor::Release()
{
}
