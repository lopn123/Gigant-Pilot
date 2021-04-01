#include "DXUT.h"
#include "cTitle.h"

cTitle::cTitle()
{
}


cTitle::~cTitle()
{
}

void cTitle::Init()
{
	m_image = IMAGEMANAGER->FindImage("Title");

	m_image_PlayOn =	 IMAGEMANAGER->FindImage("PlayOn");
	m_image_SettingOn =	 IMAGEMANAGER->FindImage("SettingOn");
	m_image_CreditOn =	 IMAGEMANAGER->FindImage("CreditOn");
	m_image_ExitOn =	 IMAGEMANAGER->FindImage("ExitOn");

	m_image_PlayOff =	 IMAGEMANAGER->FindImage("PlayOff");
	m_image_SettingOff = IMAGEMANAGER->FindImage("SettingOff");
	m_image_CreditOff =  IMAGEMANAGER->FindImage("CreditOff");
	m_image_ExitOff =	 IMAGEMANAGER->FindImage("ExitOff");

	m_image_Play =		 IMAGEMANAGER->FindImage("Play");
	m_image_Setting =	 IMAGEMANAGER->FindImage("Setting");
	m_image_Credit =	 IMAGEMANAGER->FindImage("Credit");
	m_image_Exit =		 IMAGEMANAGER->FindImage("Exit");

	credit = IMAGEMANAGER->FindImage("Creditt");
	setting = IMAGEMANAGER->FindImage("Settingg");

	ButtonPos = Vec2(WINSIZEX / 2, WINSIZEY / 2);

	CurStatus = 1, Return = 0;
}

void cTitle::Release()
{
}

void cTitle::Update()
{
	if (KEYMANAGER->IsOnceKeyDown(VK_UP) && (CurStatus == 3 || CurStatus == 4))
	{
		CurStatus -= 2;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_DOWN) && (CurStatus == 1 || CurStatus == 2))
	{
		CurStatus += 2;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_RIGHT) && CurStatus != 4)
	{
		CurStatus++;
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_LEFT) && CurStatus != 1)
	{
		CurStatus--;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RETURN))
	{
		switch (CurStatus)
		{
		case 1:
			Return = 1;
			break;
		case 2:
			Return = 2;
			break;
		case 3:
			Return = 3;
			break;
		case 4:
			Return = 4;
			break;
		}
	}
}

void cTitle::Render()
{
	RENDER->CamUpdate(Vec2(0 + WINSIZEX / 2, 0 + WINSIZEY / 2));
	RENDER->SetCamSize(2, 2);

	RENDER->ScaleRender(m_image, WINSIZEX / 2, WINSIZEY / 2 , 2);
}

void cTitle::UIRender()
{
	switch (CurStatus)
	{
	case 1:
		if (Return == 1)
		{
			Return = 0;
			UIMANAGER->CenterRender(m_image_Play, ButtonPos.x - 200, ButtonPos.y + 150);
			SCENEMANAGER->ChangeScene("Stage");
		}
		else
			UIMANAGER->CenterRender(m_image_PlayOn, ButtonPos.x - 200, ButtonPos.y + 150);

		UIMANAGER->CenterRender(m_image_SettingOff, ButtonPos.x + 200, ButtonPos.y + 150);
		UIMANAGER->CenterRender(m_image_CreditOff, ButtonPos.x - 200, ButtonPos.y + 300);
		UIMANAGER->CenterRender(m_image_ExitOff, ButtonPos.x + 200, ButtonPos.y + 300);
		break;
	case 2:
		if (Return == 2)
		{
			Return = 0;
			UIMANAGER->CenterRender(m_image_Setting, ButtonPos.x + 200, ButtonPos.y + 150);
			UIMANAGER->CenterRender(setting, WINSIZEX / 2, WINSIZEY / 2);
		}
		else
		{
			UIMANAGER->CenterRender(m_image_SettingOn, ButtonPos.x + 200, ButtonPos.y + 150);
			UIMANAGER->CenterRender(m_image_PlayOff, ButtonPos.x - 200, ButtonPos.y + 150);
			UIMANAGER->CenterRender(m_image_CreditOff, ButtonPos.x - 200, ButtonPos.y + 300);
			UIMANAGER->CenterRender(m_image_ExitOff, ButtonPos.x + 200, ButtonPos.y + 300);
		}
		
		break;
	case 3:
		if (Return == 3)
		{
			Return = 0;
			UIMANAGER->CenterRender(m_image_Credit, ButtonPos.x - 200, ButtonPos.y + 300);
			UIMANAGER->CenterRender(credit, WINSIZEX / 2, WINSIZEY / 2);
		}
		else
		{
			UIMANAGER->CenterRender(m_image_CreditOn, ButtonPos.x - 200, ButtonPos.y + 300);
			UIMANAGER->CenterRender(m_image_PlayOff, ButtonPos.x - 200, ButtonPos.y + 150);
			UIMANAGER->CenterRender(m_image_SettingOff, ButtonPos.x + 200, ButtonPos.y + 150);
			UIMANAGER->CenterRender(m_image_ExitOff, ButtonPos.x + 200, ButtonPos.y + 300);
		}
		break;
	case 4:
		if (Return == 4)
		{
			Return = 0;
			UIMANAGER->CenterRender(m_image_Exit, ButtonPos.x + 200, ButtonPos.y + 300);
			PostQuitMessage(0);
		}
		else
			UIMANAGER->CenterRender(m_image_ExitOn, ButtonPos.x + 200, ButtonPos.y + 300);

		UIMANAGER->CenterRender(m_image_PlayOff, ButtonPos.x - 200, ButtonPos.y + 150);
		UIMANAGER->CenterRender(m_image_SettingOff, ButtonPos.x + 200, ButtonPos.y + 150);
		UIMANAGER->CenterRender(m_image_CreditOff, ButtonPos.x - 200, ButtonPos.y + 300);
	}
}