#include "DXUT.h"
#include "mainGame.h"
#include "cAdd.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

void mainGame::Init()
{
	srand(time(NULL));

	SOUNDMANAGER->Init();

	m_Add->AddImages();
	m_Add->AddScenes();
	
	SCENEMANAGER->ChangeScene("Title");
}

void mainGame::Release()
{
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cImageManager::ReleaseInstance();
	cKeyManager::ReleaseInstance();
	cObjectManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	OBJECTMANAGER->Release();
}

void mainGame::Update()
{
	KEYMANAGER->Update();
	OBJECTMANAGER->Update();
	SCENEMANAGER->Update();
}

void mainGame::Render()
{
	SCENEMANAGER->Render();
	OBJECTMANAGER->Render();

	UIMANAGER->Begin();
	SCENEMANAGER->UIRender();
	OBJECTMANAGER->UIRender();

	UIMANAGER->End();
}

void mainGame::LostDevice()
{
	UIMANAGER->LostDevice();
}

void mainGame::ResetDevice()
{
	UIMANAGER->ResetDevice();
}
