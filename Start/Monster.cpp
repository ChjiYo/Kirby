#include "Monster.h"

#include "ObjMgr.h"
#include "CollisionMgr.h"

#include "Attack.h"
#include "Player.h"

CMonster::CMonster()
{
	ZeroMemory(&m_eCurState, sizeof(m_eCurState));
	ZeroMemory(&m_ePreState, sizeof(m_ePreState));

	m_iHp = 0;

	m_fInhalSpeed = 0.f;

	m_bInhalMoveStop = false;

	m_iKillCount = 0;
}

CMonster::~CMonster()
{
}

void CMonster::Move()
{

}

void CMonster::Hit()
{
	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetMonEpickList()))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonEpickInfo())->SetHp(-(dynamic_cast<CAttack*>(CObjMgr::GetInst().GetAttackInfo())->GetDamage()));
		//CObjMgr::GetInst().GetAttackInfo()->SetDead();
	}

	if (CCollisionMgr::GetInst().ObjectCollisionCheck(CObjMgr::GetInst().GetAttackList(), CObjMgr::GetInst().GetMonsterList()))
	{
		dynamic_cast<CMonster*>(CObjMgr::GetInst().GetMonsterInfo())->SetHp(-(dynamic_cast<CAttack*>(CObjMgr::GetInst().GetAttackInfo())->GetDamage()));
		//CObjMgr::GetInst().GetAttackInfo()->SetDead();
	}
}

bool CMonster::Inhal()
{
	float fDistance = abs(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX - m_tInfo.fX);

	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetInhal() && fDistance < 200.f)
	{
		m_bInhalMoveStop = true;
		
		m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_PLAYER, this);

		if (m_pTarget)
		{
			float m_fWidth = (m_pTarget->GetInfo().fX - m_tInfo.fX);
			float m_fHeight = (m_pTarget->GetInfo().fY - m_tInfo.fY);

			float m_fDiagonal = (float)(sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight));

			float m_fRadian = (float)acos(m_fWidth / m_fDiagonal);

			if (m_pTarget->GetInfo().fY > m_tInfo.fY)
				m_fRadian = (2 * PI) - m_fRadian;

			m_fAngle = m_fRadian * (180.f / PI);

			CObjMgr::GetInst().GetMonsterInfo()->SetAngle(m_fAngle);
		
		}
		m_tInfo.fX += m_fInhalSpeed * (float)cos(m_fAngle * (PI / 180.f));
		m_tInfo.fY -= m_fInhalSpeed * (float)sin(m_fAngle * (PI / 180.f));

			SetStage(INHAL);

		return true;
	}
	return false;
}


/*



bool CMonster::Inhal()
{
	float fDistance = abs(CObjMgr::GetInst().GetPlayerInfo()->GetInfo().fX - m_tInfo.fX);

	if (dynamic_cast<CPlayer*>(CObjMgr::GetInst().GetPlayerInfo())->GetInhal() && fDistance < 140.f)
	{
		m_pTarget = CObjMgr::GetInst().Get_Target(OBJ_MONSTER, this);

		if (m_pTarget)
		{
			m_bInputKeyCheck = true;
			m_fWidth = (m_pTarget->GetInfo().fX - m_tInfo.fX);
			m_fHeight = (m_pTarget->GetInfo().fY - m_tInfo.fY);

			m_fDiagonal = (float)(sqrt(m_fWidth * m_fWidth + m_fHeight * m_fHeight));

			m_fRadian = (float)acos(m_fWidth / m_fDiagonal);

			if (m_pTarget->GetInfo().fY > m_tInfo.fY)
				m_fRadian = (2 * PI) - m_fRadian;

			m_fAngle = m_fRadian * (180.f / PI);

			CObjMgr::GetInst().GetMonsterInfo()->SetAngle(m_fAngle);
			m_tInfo.fX += m_fInhalSpeed * cos(m_fAngle * (PI / 180.f));
			m_tInfo.fY -= m_fInhalSpeed * sin(m_fAngle * (PI / 180.f));
		}

	}
	SetStage(INHAL);

	return true;

	return false;
}





*/