#pragma once
#include "singleton.h"
class cSoundManager:public singleton< cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();
	void Init();
	void Play_Bgm(LPCWSTR path);
	void Play_Eft(string path);
	MCI_PLAY_PARMS play;
	MCI_OPEN_PARMS open;
};

#define SOUNDMANAGER cSoundManager::GetInstance()