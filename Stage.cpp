#include "DXUT.h"
#include "Stage.h"
#include "cPlayer.h"
#include "cScrollMap.h"
#include "cEnemy.h"
#include "cBoss.h"

Stage::Stage()
	:m_speed(0)
{
	m_Timer = new cTimer(3);

	bossSpawn = false, chk = false;

	sc = new cScrollMap();

	m_image_bulletMod[0] = IMAGEMANAGER->FindImage("PlayerBulletMod1");
	m_image_bulletMod[1] = IMAGEMANAGER->FindImage("PlayerBulletMod2");

	stage = 1;
}

Stage::~Stage()
{
	SAFE_DELETE(sc);
}

void Stage::Init()
{
	OBJECTMANAGER->AddObject(new cPlayer);

	OBJECTMANAGER->score = 0;

	m_OldTime = m_CurTime = timeGetTime();
	m_OldTime2 = m_CurTime2 = timeGetTime();
	m_OldTime3 = m_CurTime3 = timeGetTime();
}

void Stage::Release()
{
}

void Stage::Update()
{
	//플레이어 게임 오버
	if (OBJECTMANAGER->m_player->GetHp() == 0)
	{
		OBJECTMANAGER->m_player->DestroyObj();
		SCENEMANAGER->ChangeScene("End");
	}

	//적, 보스 소환
	if (stage == 1)
	{
		EnemySpawn1();
	}
	else if (stage == 2)
	{
		EnemySpawn2();
	}
}

void Stage::Render()
{
	if (OBJECTMANAGER->freeze == false)
	{
		m_CurTime = timeGetTime();
		m_CurTime2 = timeGetTime();
		m_CurTime3 = timeGetTime();
	}

	RENDER->SetCamSize(1, 1);

	OBJECTMANAGER->score++;

	if (stage == 1)
		sc->Render(400);
	else if (stage == 2)
		sc->Render(600);
}

void Stage::UIRender()
{
	UIMANAGER->TextDraw("체력 : " + to_string(OBJECTMANAGER->m_player->GetHp()), Vec2(0, 0), 30, D3DCOLOR_XRGB(255, 255, 255), false);
	UIMANAGER->TextDraw("스킬 쿨타임 : " + to_string((int)OBJECTMANAGER->skillCool) + "초", Vec2(0, 50), 30, D3DCOLOR_XRGB(255, 255, 255), false);
	UIMANAGER->TextDraw("쉴드 쿨타임 : " + to_string((int)OBJECTMANAGER->shieldCool) + "초", Vec2(0, 100), 30, D3DCOLOR_XRGB(255, 255, 255), false);

	if (OBJECTMANAGER->bulletMod == 0)
		UIMANAGER->CenterRender(m_image_bulletMod[0], 100, 800);
	else if (OBJECTMANAGER->bulletMod == 1)
		UIMANAGER->CenterRender(m_image_bulletMod[1], 100, 800);

	if (chk)
	{
		if (m_Timer->Update())
		{
			chk = false;
		}
		UIMANAGER->TextDraw("스테이지 2", Vec2(WINSIZEX / 2 - 200, WINSIZEY / 2 - 100), 100, D3DCOLOR_XRGB(255, 255, 255), false);
	}
}

void Stage::EnemySpawn1()
{
	if (OBJECTMANAGER->freeze == false)
	{
		if (m_CurTime - m_OldTime > 0 && m_CurTime - m_OldTime <= 8000)
		{
			if (m_CurTime2 - m_OldTime2 >= 1000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(0, 400));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 10000 && m_CurTime - m_OldTime <= 20000)
		{
			if (m_CurTime2 - m_OldTime2 >= 2000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(1, 200));
				OBJECTMANAGER->AddObject(new cEnemy(2, 200));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 22000 && m_CurTime - m_OldTime <= 32000)
		{
			if (m_CurTime2 - m_OldTime2 >= 2000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(3, 300, Vec2(WINSIZEX + 150, 50), true));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 32000 && m_CurTime - m_OldTime <= 40000)
		{
			if (m_CurTime2 - m_OldTime2 >= 1000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(8, 400, Vec2(50, -150)));
				OBJECTMANAGER->AddObject(new cEnemy(8, 400, Vec2(WINSIZEX - 50, WINSIZEY + 150)));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime >= 43000)
		{
			stage = 2;
			m_CurTime = m_OldTime, m_CurTime2 = m_OldTime2;
		}
	}
}

void Stage::EnemySpawn2()
{
	if (OBJECTMANAGER->freeze == false)
	{
		if (m_CurTime - m_OldTime > 0 && m_CurTime - m_OldTime <= 8000)
		{
			if (m_CurTime2 - m_OldTime2 >= 500)
			{
				OBJECTMANAGER->AddObject(new cEnemy(0, 500));

				m_OldTime2 = timeGetTime();
			}

			if (m_CurTime3 - m_OldTime3 >= 1500)
			{
				OBJECTMANAGER->AddObject(new cEnemy(4, 500, Vec2(-150, -150)));
				OBJECTMANAGER->AddObject(new cEnemy(4, 500, Vec2(-150, WINSIZEY + 150)));

				OBJECTMANAGER->AddObject(new cEnemy(5, 500, Vec2(WINSIZEX + 150, -150)));
				OBJECTMANAGER->AddObject(new cEnemy(5, 500, Vec2(WINSIZEX + 150, WINSIZEY + 150)));

				m_OldTime3 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 10000 && m_CurTime - m_OldTime <= 20000)
		{
			if (m_CurTime2 - m_OldTime2 >= 2000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(1, 300));
				OBJECTMANAGER->AddObject(new cEnemy(2, 300));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 22000 && m_CurTime - m_OldTime <= 32000)
		{
			if (m_CurTime2 - m_OldTime2 >= 2000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(3, 300, Vec2(WINSIZEX + 150, 50), true));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 32000 && m_CurTime - m_OldTime <= 40000)
		{
			if (m_CurTime2 - m_OldTime2 >= 1000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(6, 200, Vec2(WINSIZEX + 150, 50)));
				OBJECTMANAGER->AddObject(new cEnemy(6, 200, Vec2(WINSIZEX + 150, WINSIZEY - 50)));

				OBJECTMANAGER->AddObject(new cEnemy(8, 400, Vec2(50, -150)));
				OBJECTMANAGER->AddObject(new cEnemy(8, 400, Vec2(WINSIZEX - 50, WINSIZEY + 150)));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 50000 && m_CurTime - m_OldTime <= 60000)
		{
			if (m_CurTime2 - m_OldTime2 >= 1000)
			{
				OBJECTMANAGER->AddObject(new cEnemy(7, 400, Vec2(WINSIZEX + 150, 50)));
				OBJECTMANAGER->AddObject(new cEnemy(7, 400, Vec2(-150, WINSIZEY - 50)));

				m_OldTime2 = timeGetTime();
			}
		}
		else if (m_CurTime - m_OldTime > 65000 && bossSpawn == false)
		{
			OBJECTMANAGER->AddObject(new cBoss());
			bossSpawn = true;
		}
	}
}