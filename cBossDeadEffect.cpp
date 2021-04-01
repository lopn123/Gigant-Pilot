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

	//0.1�ʸ��� m_ani ������ 1�� ���Ͽ� �̹����� �ٲٰ�, m_ani�� 7�� �Ǿ��� ��� �� �̻� �̹����� ���� ������ ������Ʈ�� �������ش�.
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
