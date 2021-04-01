#pragma once
#include "singleton.h"
class cPlayer;
class cObject;
class cObjectManager :public singleton<cObjectManager>
{
private:
	list<cObject*> m_objList;
	LPRECT rt;
	RECT RT;
	RECT Rt;

public:
	cPlayer * m_player = nullptr;

	void Update();
	void Render();
	void UIRender();
	void Release();

	cObject* AddObject(cObject* _newObj);

public:
	unsigned long long int score;

	int	  bulletMod = 0;

	bool  invincible = false;

	float skillCool = 0;
	bool  freeze = false;
	float shieldCool = 0;
	bool  shield = false;
};

#define OBJECTMANAGER cObjectManager::GetInstance()