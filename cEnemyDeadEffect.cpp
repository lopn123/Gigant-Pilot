#include "DXUT.h"
#include "cEnemyDeadEffect.h"


cEnemyDeadEffect::cEnemyDeadEffect(Vec2 pos)
	: m_pos(pos)
{
	for (int i = 1; i <= 7; i++)
	{
		m_image[i-1] = IMAGEMANAGER->FindImage("EnemyDeadEffect" + to_string(i));
	}

	m_Timer = new cTimer(0.03);

	m_ani = 0;
}


cEnemyDeadEffect::~cEnemyDeadEffect()
{
	SAFE_DELETE(m_Timer);
}

void cEnemyDeadEffect::Init()
{
}

void cEnemyDeadEffect::Update()
{
}

void cEnemyDeadEffect::Render()
{
	RENDER->CenterRender(m_image[m_ani], m_pos.x, m_pos.y);

	if (m_Timer->Update())
	{
		m_ani++;

		if (m_ani == 7)
			DestroyObj();
	}
}

void cEnemyDeadEffect::Release()
{
}
