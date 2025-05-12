#include "Attack.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

#include "Attack.h"
#include "Monster.h"

CAttack::CAttack()
{
	m_dwDeltaTime = 0;
	m_iScrollX = 0;
	m_fAttackRange = 0.f;
	m_iHp = 1;
	m_iDamage = 0;
}

CAttack::~CAttack()
{
}

void CAttack::MotionChange()
{

}

void CAttack::Initialize()
{
	
}

int CAttack::Update()
{
	return OBJ_NOEVENT;
}

void CAttack::LateUpdate()
{

}

void CAttack::Render(HDC _hDC)
{
}

void CAttack::Release()
{
}
