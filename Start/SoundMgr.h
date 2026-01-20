#pragma once

#include "Define.h"


class CSoundMgr
{
private:
	CSoundMgr();
	~CSoundMgr();

public:
	static CSoundMgr& GetInst()
	{
		static CSoundMgr Inst;
		return Inst;
	}

public:
	void Initialize();
	void Release();

public:
	void PlaySound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, float fVolume);
	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);

private:
	void LoadSoundFile();


private:
	map<TCHAR*, FMOD_SOUND*> m_mapSound;
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL];

	//// 사운드 ,채널 객체 및 장치를 관리는 객체 
	FMOD_SYSTEM* m_pSystem;

};

