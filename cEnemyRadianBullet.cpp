#include "DXUT.h"
#include "cEnemyRadianBullet.h"
#include "cTimer.h"
#include "cPlayer.h"
cEnemyRadianBullet::cEnemyRadianBullet(Vec2 pos, Vec2 rot, int speed, int dmg)
	:m_pos(pos), m_rot(rot), m_speed(speed), m_dmg(dmg)
{
	m_image = IMAGEMANAGER->FindImage("EnemyBullet");

	MakeTag("EnemyBullet");
	Pos = pos;
}

cEnemyRadianBullet::~cEnemyRadianBullet()
{
}

void cEnemyRadianBullet::Update()
{
	Rot = atan2(m_pos.y - Pos.y, m_pos.x - Pos.x);

	SetPos(m_pos);

	SetRect(RECT{
	long(m_pos.x - m_image->info.Width / 2),
	long(m_pos.y - m_image->info.Height / 2),
	long(m_pos.x + m_image->info.Width / 2),
	long(m_pos.y + m_image->info.Height / 2)
	});

	if (IsOutMap(m_pos))
		DestroyObj();

	if(OBJECTMANAGER->freeze == false)
		m_pos -= m_rot * m_speed * DXUTGetElapsedTime();
}

void cEnemyRadianBullet::Render()
{
	RENDER->Render(m_image, m_pos.x, m_pos.y,0,-Rot + 6.4);
}

void cEnemyRadianBullet::UIRender()
{
}

void cEnemyRadianBullet::Release()
{
}

void cEnemyRadianBullet::Collision(cObject * obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false)
	{
		if (obj->GetTag() == "Player")
		{
			obj->HitHp(m_dmg); //m_dmg 만큼 플레이어 체력 감소
			DestroyObj();
			OBJECTMANAGER->invincible = true;
		}
	}
}
