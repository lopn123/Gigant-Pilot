#include "DXUT.h"
#include "cEnemyDirectShot.h"
#include "cEnemy.h"
#include "cPlayer.h"

cEnemyDirectShot::cEnemyDirectShot(const Vec2& pos, int speed, int dmg)
	: m_pos(pos), m_speed(speed), m_dmg(dmg)
{
	m_image = IMAGEMANAGER->FindImage("EnemyBullet");
	MakeTag("EnemyBullet");

	D3DXVec2Normalize(&Pos, &Vec2(m_pos - OBJECTMANAGER->m_player->GetPos()));

	StartPos = pos;
}

cEnemyDirectShot::~cEnemyDirectShot()
{
}

void cEnemyDirectShot::Init()
{
}

void cEnemyDirectShot::Update()
{
	Rot = atan2(m_pos.y - Pos.y, m_pos.x - Pos.x);

	if (OBJECTMANAGER->freeze == false)
	{
		m_pos -= Pos * m_speed * DXUTGetElapsedTime();
	}

	SetRect(RECT{
	long(m_pos.x - m_image->info.Width / 2),
	long(m_pos.y - m_image->info.Height / 2),
	long(m_pos.x + m_image->info.Width / 2),
	long(m_pos.y + m_image->info.Height / 2)
		});

	if (IsOutMap(m_pos))
	{
		DestroyObj();
	}
}

void cEnemyDirectShot::Render()
{
	RENDER->Render(m_image, m_pos.x, m_pos.y);
}

void cEnemyDirectShot::Release()
{
}

void cEnemyDirectShot::UIRender()
{
}

void cEnemyDirectShot::Collision(cObject * obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false) 
	{
		if (obj->GetTag() == "Player")
		{
			obj->HitHp(m_dmg);
			DestroyObj();
			OBJECTMANAGER->invincible = true;
		}
	}
}
