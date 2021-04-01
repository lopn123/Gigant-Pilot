#include "DXUT.h"
#include "cEnd.h"

cEnd::cEnd()
{
	m_image = IMAGEMANAGER->FindImage("End");
}

cEnd::~cEnd()
{
}

void cEnd::Init()
{
}

void cEnd::Release()
{
}

void cEnd::Update()
{
	if (DXUTWasKeyPressed(VK_RETURN))
	{
		SCENEMANAGER->ChangeScene("Title");
	}
}

void cEnd::Render()
{
	RENDER->CenterRender(m_image, WINSIZEX / 2, WINSIZEY / 2);
}

void cEnd::UIRender()
{
	UIMANAGER->TextDraw("게임 종료", Vec2(WINSIZEX / 2 - 180, WINSIZEY / 2 - 300), 100, D3DCOLOR_XRGB(0, 0, 0), false);
	UIMANAGER->TextDraw("점수 : " + to_string(OBJECTMANAGER->score), Vec2(WINSIZEX/2 - 200, WINSIZEY/2), 100, D3DCOLOR_XRGB(0, 0, 0), false);
}
