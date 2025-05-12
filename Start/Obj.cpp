#include "Obj.h"
#include "ObjMgr.h"
#include "Player_Ice.h"


CObj::CObj()
{
    ZeroMemory(&m_tInfo, sizeof(m_tInfo));
    ZeroMemory(&m_tRect, sizeof(m_tRect));

    m_fSpeed = 0.f;
    m_bDead = false;

    m_eRender = RENDER_END;
}

CObj::~CObj()
{
}

void CObj::RectUpdate()
{
    m_tRect.left = LONG(m_tInfo.fX - (m_tInfo.fCX * 1.5f));
    m_tRect.top = LONG(m_tInfo.fY - (m_tInfo.fCY * 1.5f));
    m_tRect.right = LONG(m_tInfo.fX + (m_tInfo.fCX * 1.5f));
    m_tRect.bottom = LONG(m_tInfo.fY + (m_tInfo.fCY * 1.5f));
}

void CObj::MoveFrame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < GetTickCount64())
    {
        ++m_tFrame.iFrameStart;

        if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
            m_tFrame.iFrameStart = 0;

        m_tFrame.dwTime = (DWORD)GetTickCount64();
    }
}
