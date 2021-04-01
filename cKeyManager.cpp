#include "DXUT.h"

cKeyManager::cKeyManager()
{
	ZeroMemory(NowKeyState,sizeof(256));
	ZeroMemory(prevKeyState, sizeof(256));
}

cKeyManager::~cKeyManager()
{
}

void cKeyManager::Update()
{

	memcpy(prevKeyState,NowKeyState,256);
	for (int i = 0; i < 256; i++)
	{
		NowKeyState[i] = GetAsyncKeyState(i) & 0x8000;
	}
}

bool cKeyManager::IsOnceKeyDown(int key)
{
	return NowKeyState[key]&&!prevKeyState[key];
}

bool cKeyManager::IsStayKeyDown(int key)
{
	
	return NowKeyState[key];

}

bool cKeyManager::IsOnceKeyUp(int key)
{
	return !NowKeyState[key] && prevKeyState[key];

}
