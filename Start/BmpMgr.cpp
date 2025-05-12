#include "BmpMgr.h"

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::InsertBmp(const TCHAR* _pFilePath, const TCHAR* _pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(),
		[&](auto& MyPair)->bool
		{
			if (!lstrcmp(MyPair.first, _pImgKey))
				return true;

			return false;
		});

	if (iter == m_mapBit.end())
	{
		CMyBmp* pBmp = new CMyBmp;

		pBmp->LoadBmp(_pFilePath);	

		m_mapBit.insert({ _pImgKey, pBmp });
	}
}

HDC CBmpMgr::FindImage(const TCHAR* _pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(),
		[&](auto& MyPair)->bool
		{
			if (!lstrcmp(MyPair.first, _pImgKey))
				return true;

			return false;
		});

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->GetMemDC();
}

void CBmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), [&](auto& MyPair)
		{
			if (MyPair.second)
			{
				delete MyPair.second;
				MyPair.second = nullptr;
			}
		});

	m_mapBit.clear();
}
