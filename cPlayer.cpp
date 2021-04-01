#include "DXUT.h"
#include "cPlayer.h"
#include "cPlayerBullet.h"
#include "cShieldEffect.h"

cPlayer::cPlayer()
	:m_pos(200, 400)
{
	m_image[0] = IMAGEMANAGER->FindImage("Player");
	m_image[1] = IMAGEMANAGER->FindImage("Player1");
	m_image[2] = IMAGEMANAGER->FindImage("Player2");

	m_Timer[0] = new cTimer(0.1);
	m_Timer[1] = new cTimer(2);
	m_Timer[2] = new cTimer(3);
	m_Timer[3] = new cTimer(5);

	MakeTag("Player");
	SetHp(50);
	OBJECTMANAGER->m_player = this;
	m_move = 15;

	Ani = false;

	OBJECTMANAGER->bulletMod = 0;
}


cPlayer::~cPlayer()
{
	for (auto iter:m_Timer)
	{
		SAFE_DELETE(iter);
	}
}

void cPlayer::Init()
{
	m_OldTime = m_CurTime = timeGetTime();
	m_OldTime2 = m_CurTime2 = timeGetTime();
}

void cPlayer::Update()
{
	SetRect(RECT{
		long(m_pos.x - m_image[0]->info.Width / 2) + 25 ,
		long(m_pos.y - m_image[0]->info.Height / 2) + 25,
		long(m_pos.x + m_image[0]->info.Width / 2 - 25),
		long(m_pos.y + m_image[0]->info.Height / 2 - 25)
		});

	SetPos(m_pos);

	KeyPress();
}

void cPlayer::Render()
{
	if (OBJECTMANAGER->invincible == true)
	{
		if (m_Timer[0]->Update())
		{
			if (Ani == false)
			{
				Ani = true;
				RENDER->CenterRender(m_image[1], m_pos.x, m_pos.y);
			}
			else if(Ani == true)
			{
				Ani = false;
				RENDER->CenterRender(m_image[2], m_pos.x, m_pos.y);
			}
		}
	}
	else
		RENDER->CenterRender(m_image[0], m_pos.x, m_pos.y);
	
	m_CurTime = timeGetTime();
	m_CurTime2 = timeGetTime();
	
}

void cPlayer::UIRender()
{
}

void cPlayer::Collision(cObject* obj)
{
}

void cPlayer::KeyPress()
{
	//�̵�
	if (KEYMANAGER->IsStayKeyDown(VK_UP) && m_pos.y - m_move >= 0)
	{
		m_pos.y -= m_move;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && m_pos.y + m_move <= WINSIZEY)
	{
		m_pos.y += m_move;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && m_pos.x - m_move >= 0)
	{
		m_pos.x -= m_move;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && m_pos.x + m_move <= WINSIZEX)
	{
		m_pos.x += m_move;
	}

	//�Ѿ� �߻�
	if (KEYMANAGER->IsStayKeyDown('Z') && m_CurTime - m_OldTime >= 200 && OBJECTMANAGER->bulletMod == 0)
	{
		OBJECTMANAGER->AddObject(new cPlayerBullet(Vec2(m_pos.x + 80, m_pos.y), Vec2(800, 0), 10));

		m_OldTime = m_CurTime;
	}
	else if (KEYMANAGER->IsStayKeyDown('Z') && m_CurTime - m_OldTime >= 600 && OBJECTMANAGER->bulletMod == 1)
	{
		OBJECTMANAGER->AddObject(new cPlayerBullet(Vec2(m_pos.x + 80, m_pos.y), Vec2(600, -150), 7));
		OBJECTMANAGER->AddObject(new cPlayerBullet(Vec2(m_pos.x + 80, m_pos.y), Vec2(600, 0), 7));
		OBJECTMANAGER->AddObject(new cPlayerBullet(Vec2(m_pos.x + 80, m_pos.y), Vec2(600, 150), 7));

		m_OldTime = m_CurTime;
	}

	//�÷��̾� �Ѿ� ��ü
	if (KEYMANAGER->IsStayKeyDown(VK_SHIFT) && m_CurTime2 - m_OldTime2 >= 3000)
	{
		if (OBJECTMANAGER->bulletMod != 1)
			OBJECTMANAGER->bulletMod++;
		else
			OBJECTMANAGER->bulletMod = 0;

		m_OldTime2 = timeGetTime();
	}

	//��ų
	if (KEYMANAGER->IsStayKeyDown(VK_SPACE) && OBJECTMANAGER->freeze == false && OBJECTMANAGER->skillCool == 0)
	{
		OBJECTMANAGER->freeze = true;
		OBJECTMANAGER->skillCool = 30;
	}

	//����
	if (KEYMANAGER->IsStayKeyDown(VK_CONTROL) && OBJECTMANAGER->shield == false && OBJECTMANAGER->shieldCool == 0)
	{
		OBJECTMANAGER->shield = true;
		OBJECTMANAGER->shieldCool = 20;
		OBJECTMANAGER->AddObject(new cShieldEffect());
	}

	//������ Ȱ��ȭ �Ǿ� ���� �� 2�ʰ� ������ ���� ��Ȱ��ȭ
	if (OBJECTMANAGER->invincible == true && m_Timer[1]->Update())
	{
		OBJECTMANAGER->invincible = false;
	}
	//������ Ȱ��ȭ �Ǿ� ���� �� 3�ʰ� ������ ���� ��Ȱ��ȭ
	if (OBJECTMANAGER->freeze == true && m_Timer[2]->Update())
	{
		OBJECTMANAGER->freeze = false;
	}
	//���尡 Ȱ��ȭ �Ǿ� ���� �� 5�ʰ� ������ ���� ��Ȱ��ȭ
	if (OBJECTMANAGER->shield == true && m_Timer[3]->Update())
	{
		OBJECTMANAGER->shield = false;
	}

	//��ų ��Ÿ��
	if (OBJECTMANAGER->skillCool > 0)
	{
		OBJECTMANAGER->skillCool -= DXUTGetElapsedTime();

		if (OBJECTMANAGER->skillCool < 0)
			OBJECTMANAGER->skillCool = 0;
	}
	//���� ��Ÿ��
	if (OBJECTMANAGER->shieldCool > 0)
	{
		OBJECTMANAGER->shieldCool -= DXUTGetElapsedTime();

		if (OBJECTMANAGER->shieldCool < 0)
			OBJECTMANAGER->shieldCool = 0;
	}
}