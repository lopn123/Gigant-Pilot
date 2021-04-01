#include "DXUT.h"
#include "cBossDeadEffect.h"


cBossDeadEffect::cBossDeadEffect(Vec2 pos)
	: m_pos(pos)
{
	for (int i = 1; i <= 7; i++)
	{
		m_image[i-1] = IMAGEMANAGER->FindImage("BossDeadEffect" + to_string(i));
	}

	m_Timer = new cTimer(0.1);

	m_ani = 0;
}


cBossDeadEffect::~cBossDeadEffect()
{
	SAFE_DELETE(m_Timer);
}

void cBossDeadEffect::Init()
{
}

void cBossDeadEffect::Update()
{
}

void cBossDeadEffect::Render()
{
	RENDER->CenterRender(m_image[m_ani], m_pos.x, m_pos.y);

	//0.1초마다 m_ani 변수를 1씩 더하여 이미지를 바꾸고, m_ani가 7이 되었을 경우 더 이상 이미지가 없기 때문에 오브젝트를 삭제해준다.
	if (m_Timer->Update())
	{
		m_ani++;

		if (m_ani == 7)
			DestroyObj();
	}
}

void cBossDeadEffect::Release()
{
}
