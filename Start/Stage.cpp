#include "Stage.h"
#include "StageMgr.h"

#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"

#include "Factory.h"
#include "Player_Origin.h"

CStage::CStage()
{
    m_fVolume = 0.f;
}

CStage::~CStage()
{
    Release();
}

void CStage::Initialize()
{
   CStageMgr::GetInst().StageChage(STAGE_A4);
}
    
int CStage::Update()
{
    CStageMgr::GetInst().Update();

    return 0;
}

void CStage::LateUpdate()
{
    CStageMgr::GetInst().LateUpdate();
  
}

void CStage::Render(HDC _hDC)
{
    CStageMgr::GetInst().Render(_hDC);

}

void CStage::Release()
{
}
