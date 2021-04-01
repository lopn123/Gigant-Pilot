#include "DXUT.h"
#include "cBombEnemy.h"
#include "cBossDeadEffect.h"
#include "cPlayer.h"

cBombEnemy::cBombEnemy(Vec2 pos)
	:m_pos(pos)
{
	m_image[0] = IMAGEMANAGER->FindImage("BombEnemy");
	m_image[1] = IMAGEMANAGER->FindImage("BombEnemy1");

	MakeTag("Enemy");
	SetHp(30);

	m_speed = 200;

	m_Timer = new cTimer(2);
}

cBombEnemy ::~cBombEnemy()
{
	SAFE_DELETE(m_Timer);

	OBJECTMANAGER->AddObject(new cBossDeadEffect(m_pos));
}

void cBombEnemy::Init()
{
}

void cBombEnemy::Update()
{
	SetRect(RECT{
		long(m_pos.x - m_image[0]->info.Width / 2) ,
		long(m_pos.y - m_image[0]->info.Height / 2),
		long(m_pos.x + m_image[0]->info.Width / 2),
		long(m_pos.y + m_image[0]->info.Height / 2)
		});

	if (GetHp() <= 0)
	{
		DestroyObj();
		OBJECTMANAGER->score += 10;
	}

	if (m_pos.x > WINSIZEX + 50 || m_pos.x < -50 || m_pos.y > WINSIZEY + 50 || m_pos.y < -50)
		DestroyObj();

	//플레이어를 죽을 때까지 따라가는 적
	if (OBJECTMANAGER->freeze == false)
	{
		m_angle = atan2(OBJECTMANAGER->m_player->GetPos().y - m_pos.y, OBJECTMANAGER->m_player->GetPos().x - m_pos.x);
		m_pos += Vec2(cos(m_angle), sin(m_angle)) * 8;
	}
}

void cBombEnemy::Render()
{
	if (OBJECTMANAGER->freeze == true)
		RENDER->CenterRender(m_image[1], m_pos.x, m_pos.y);
	else
		RENDER->CenterRender(m_image[0], m_pos.x, m_pos.y);
}

void cBombEnemy::UIRender()
{
}

void cBombEnemy::Collision(cObject * obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false)
	{
		if (obj->GetTag() == "Player")
		{
			obj->HitHp(1);
			DestroyObj();
			OBJECTMANAGER->invincible = true;
		}
	}
	else
	{
		if (obj->GetTag() == "Player")
		{
			DestroyObj();
		}
	}
}
