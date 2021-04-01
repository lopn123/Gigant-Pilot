#include "DXUT.h"
#include "cEnemyBullet.h"
#include "cEnemy.h"
#include "cPlayer.h"

cEnemyBullet::cEnemyBullet(const Vec2& pos, Vec2 Pos, int dmg)
	: m_pos(pos), m_dir(Pos), m_dmg(dmg)
{
	m_image = IMAGEMANAGER->FindImage("EnemyBullet");
	MakeTag("EnemyBullet");
}

cEnemyBullet::~cEnemyBullet()
{

}

void cEnemyBullet::Init()
{
}

void cEnemyBullet::Update()
{
	SetRect(RECT{
	long(m_pos.x - m_image->info.Width / 2),
	long(m_pos.y - m_image->info.Height / 2),
	long(m_pos.x + m_image->info.Width / 2),
	long(m_pos.y + m_image->info.Height / 2)
	});

	//¸Ê ÀÌÅ» ½Ã »èÁ¦
	if (IsOutMap(m_pos))
	{
		DestroyObj();
	}

	if(OBJECTMANAGER->freeze == false)
		m_pos -= m_dir * DXUTGetElapsedTime();
}

void cEnemyBullet::Render()
{
	RENDER->Render(m_image, m_pos.x, m_pos.y);
}

void cEnemyBullet::Release()
{
}

void cEnemyBullet::UIRender()
{
}

void cEnemyBullet::Collision(cObject* obj)
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
