#include "DXUT.h"
#include "cEnemyBulletMissile.h"
#include "cEnemy.h"
#include "cPlayer.h"

cEnemyBulletMissile::cEnemyBulletMissile(const Vec2& pos, int dmg)
	: m_pos(pos), m_dmg(dmg)
{
	m_image = IMAGEMANAGER->FindImage("EnemyBullet");
	MakeTag("EnemyBullet");

	m_Timer = new cTimer(2);
}

cEnemyBulletMissile::~cEnemyBulletMissile()
{
	SAFE_DELETE(m_Timer);
}

void cEnemyBulletMissile::Init()
{
}

void cEnemyBulletMissile::Update()
{
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

	if (OBJECTMANAGER->freeze == false)
	{
		//2�� ������ m_follow ������ false�� �ٲپ� �� �̻� ������� �ʰ� ����.
		if (m_Timer->Update())
		{
			m_follow = false;
		}

		if (m_follow == false) //m_follow�� false�� ���� ���ư��� �������� ��� ���ư�.
			m_pos += Vec2(cos(m_angle), sin(m_angle)) * 12;

		else //m_follow�� true�� ���� �÷��̾� ����
		{
			m_angle = atan2(OBJECTMANAGER->m_player->GetPos().y - m_pos.y, OBJECTMANAGER->m_player->GetPos().x - m_pos.x);
			m_pos += Vec2(cos(m_angle), sin(m_angle)) * 6;
		}
	}
}

void cEnemyBulletMissile::Render()
{
	RENDER->Render(m_image, m_pos.x, m_pos.y, 0);
}

void cEnemyBulletMissile::Release()
{
}

void cEnemyBulletMissile::UIRender()
{
}

void cEnemyBulletMissile::Collision(cObject* obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false) {
		if (obj->GetTag() == "Player")
		{
			obj->HitHp(m_dmg);
			DestroyObj();
			OBJECTMANAGER->invincible = true;
		}
	}
}
