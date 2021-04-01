#include "DXUT.h"
#include "cPlayerBullet.h"
#include "cPlayer.h"

cPlayerBullet::cPlayerBullet(const Vec2 &pos, Vec2 Pos, int dmg)
	: m_pos(pos), m_dir(Pos), m_dmg(dmg)
{
	if(OBJECTMANAGER->bulletMod == 0)
		m_image = IMAGEMANAGER->FindImage("Bullet");
	else if(OBJECTMANAGER->bulletMod == 1)
		m_image = IMAGEMANAGER->FindImage("Bullet2");

	MakeTag("PlayerBullet");
}

cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Init()
{

}

void cPlayerBullet::Update()
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

	m_pos += m_dir * DXUTGetElapsedTime();
}

void cPlayerBullet::Render()
{
	RENDER->CenterRender(m_image, m_pos.x, m_pos.y);
}

void cPlayerBullet::Release()
{
}

void cPlayerBullet::UIRender()
{
}

void cPlayerBullet::Collision(cObject* obj)
{
	if (obj->GetTag() == "Enemy") //적과 부딪히면
	{
		obj->HitHp(m_dmg); //m_dmg 만큼 적 체력 감소한 후,
		DestroyObj(); //총알 삭제
	}
	if (obj->GetTag() == "Boss")
	{
		obj->HitHp(m_dmg);
		DestroyObj();
	}
}
