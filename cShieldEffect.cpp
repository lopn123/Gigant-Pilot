#include "DXUT.h"
#include "cShieldEffect.h"
#include "cPlayer.h"

#define m_pos OBJECTMANAGER->m_player->GetPos()

cShieldEffect::cShieldEffect()
{
	for (int i = 1; i <= 8; i++)
	{
		m_image[i - 1] = IMAGEMANAGER->FindImage("ShieldEffect" + to_string(i));
	}

	m_Timer[0] = new cTimer(0.05);
	m_Timer[1] = new cTimer(4.65);

	m_ani = 1;
}


cShieldEffect::~cShieldEffect()
{
	for (auto iter : m_Timer)
	{
		SAFE_DELETE(iter);
	}
}

void cShieldEffect::Init()
{
}

void cShieldEffect::Update()
{
	SetRect(RECT{
		long(m_pos.x - m_image[0]->info.Width / 2),
		long(m_pos.y - m_image[0]->info.Height / 2),
		long(m_pos.x + m_image[0]->info.Width / 2),
		long(m_pos.y + m_image[0]->info.Height / 2)
		});


}

void cShieldEffect::Render()
{
	RENDER->CenterRender(m_image[m_ani-1], m_pos.x, m_pos.y);

	//m_ani 변수가 8보다 작을 때는 0.05초마다 1씩 더하여 이미지를 바꾸고,
	if (m_Timer[0]->Update() && m_ani < 8)
	{
		m_ani++;
	}
	else if (m_Timer[1]->Update() && m_ani == 8) //m_ani가 8이 되었을 때는 4.65초 이후에 쉴드를 삭제.
	{
		DestroyObj();
	}
}

void cShieldEffect::Release()
{
}