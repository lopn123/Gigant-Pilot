#include "DXUT.h"
#include "cBoss.h"
#include "cEnemy.h"
#include "cBombEnemy.h"
#include "cEnemyBullet.h"
#include "cEnemyBulletMissile.h"
#include "cEnemyDirectShot.h"
#include "cEnemyRadianBullet.h"
#include "cBossDeadEffect.h"

cBoss::cBoss()
{
	m_image = IMAGEMANAGER->FindImage("Boss");
	MakeTag("Boss");
	SetHp(2000);

	m_pos = Vec2(WINSIZEX + 50, WINSIZEY/2);
	m_speed = 700;

	m_pattern1 = 1, m_pattern2 = 1, m_pattern3 = 1, count = 1, num = 10,
	angle = 0, rot = 0, Rot = D3DX_PI * 2 / 50, Rot2 = D3DX_PI * 2 / 20;

	SetTimer();
}


cBoss::~cBoss()
{
	for (auto iter : m_Timer)
	{
		SAFE_DELETE(iter);
	}
	
	OBJECTMANAGER->AddObject(new cBossDeadEffect(m_pos)); //보스 폭발(사망) 이펙트
}

void cBoss::Init()
{
	m_OldTime = m_CurTime = timeGetTime();
	m_OldTime2 = m_CurTime2 = timeGetTime();
}

void cBoss::Update()
{
	SetRect(RECT{
		long(m_pos.x - m_image->info.Width / 2) ,
		long(m_pos.y - m_image->info.Height / 2),
		long(m_pos.x + m_image->info.Width / 2),
		long(m_pos.y + m_image->info.Height / 2)
		});

	//맵 이탈 시 가운데로 이동
	if (m_pos.x > WINSIZEX + 50 || m_pos.x < 0 || m_pos.y > WINSIZEY || m_pos.y < 0)
	{
		m_pos = Vec2(WINSIZEX / 2, WINSIZEY / 2);
	}

	//보스의 체력이 0이하로 내려갔을 때 오브젝트 삭제, 점수 추가 및 End화면으로 전환
	if (GetHp() <= 0)
	{
		DestroyObj();
		OBJECTMANAGER->score += 10000;

		SCENEMANAGER->ChangeScene("End");
	}

	//얼음(스킬)상태가 아닐 때 등장 및 패턴 작동
	if (OBJECTMANAGER->freeze == false)
	{
		if (m_pos.x >= WINSIZEX - 150)
			m_pos.x -= m_speed * DXUTGetElapsedTime();
		else
		{
			pattern();
		}
	}
}

void cBoss::Render()
{
	//이미지출력
	RENDER->CenterRender(m_image, m_pos.x, m_pos.y);

	if(OBJECTMANAGER->freeze == false)
		m_CurTime = timeGetTime();
}

void cBoss::UIRender()
{
}

void cBoss::Collision(cObject * obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false) //무적과 쉴드가 비활성화 상태일 때 
	{
		if (obj->GetTag() == "Player") //플레이어와 충돌했다면
		{
			obj->HitHp(1); //플레이어 체력 1 차감한 후,
			OBJECTMANAGER->invincible = true; //플레이어 무적을 활성화시킨다.
		}
	}
}

void cBoss::pattern()
{
	if (GetHp() >= 1400)
	{
		if (m_CurTime - m_OldTime > 0 && m_CurTime - m_OldTime <= 3000)
		{
			if (m_Timer[0]->Update() && m_pattern1 == 1)
			{
				for (int dir_y = 300; dir_y <= 700; dir_y += 100)
				{
					OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, dir_y), 1));
				}
				m_pattern1++;
			}
			else if (m_Timer[0]->Update() && m_pattern1 == 2)
			{
				for (int dir_y = -300; dir_y >= -700; dir_y -= 100)
				{
					OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, dir_y), 1));
				}

				m_pattern1++;
			}
			else if (m_Timer[0]->Update() && m_pattern1 == 3)
			{
				OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 0), 1));
				OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 100), 1));
				OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 200), 1));
				OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, -100), 1));
				OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, -200), 1));

				m_pattern1 = 1;
			}
		}
		else if (m_CurTime - m_OldTime > 3000 && m_CurTime - m_OldTime <= 6000)
		{
			if (m_Timer[1]->Update() && m_pattern2 == 1)
			{
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y), 1));
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y - 80), 1));
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y + 80), 1));
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y - 160), 1));
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y + 160), 1));
				m_pattern2++;
			}
			else if (m_Timer[1]->Update() && m_pattern2 == 2)
			{
				OBJECTMANAGER->AddObject(new cBombEnemy(Vec2(m_pos.x, 100)));
				OBJECTMANAGER->AddObject(new cBombEnemy(Vec2(m_pos.x, 800)));
				m_pattern2 = 1;
			}
		}
		else if (m_CurTime - m_OldTime > 6000 && m_CurTime - m_OldTime <= 12000)
		{
			if (m_Timer[2]->Update())
			{
				for (int dir_y = 500; dir_y <= 900; dir_y += 100)
				{
					OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1400, dir_y), 1));
				}
				for (int dir_y = -500; dir_y >= -900; dir_y -= 100)
				{
					OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1400, dir_y), 1));
				}
				OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x - 20, m_pos.y - 100), 1000, 1));
				OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x - 20, m_pos.y), 1000, 1));
				OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x - 20, m_pos.y + 100), 1000, 1));
			}
		}
		else if (m_CurTime - m_OldTime > 12000)
		{
			m_OldTime = m_CurTime;
			m_pattern1 = 1, m_pattern2 = 1;
		}
	}

	else if (GetHp() >= 700)
	{
		if (count == 1)
		{
			m_pattern1 = 1, m_pattern2 = 1;
			temp = m_speed;
			m_speed = 2500;
			count++;
		}

		if (m_pattern1 == 1)
		{
			m_OldTime = m_CurTime;

			if (m_pos.x - m_speed * DXUTGetElapsedTime() >= 0)
			{
				m_pos.x -= m_speed * DXUTGetElapsedTime();
			}
			else
			{
				m_speed = 500;
				m_pattern1++;
			}
		}
		else if (m_pattern1 == 2)
		{
			m_OldTime = m_CurTime;

			if (m_pos.x + m_speed * DXUTGetElapsedTime() <= WINSIZEX / 2)
			{
				m_pos.x += m_speed * DXUTGetElapsedTime();
			}
			else
			{
				m_speed = temp;
				m_pattern1++;
			}
		}

		if (m_CurTime - m_OldTime > 0 && m_CurTime - m_OldTime <= 12000)
		{
			if (m_Timer[3]->Update() && m_pattern2 == 1)
			{
				rot += D3DXToRadian(50);              
				Start.x = m_pos.x + 200 * cos(rot);
				Start.y = m_pos.y + 200 * sin(rot);

				for (float i = 0; i < 8; i++, angle += Rot)
				{
					Vec2 Direction = Vec2(m_pos.x + (cosf(angle) * 90), m_pos.y + (sinf(angle) * 90));

					Direction = Direction - m_pos;

					D3DXVec2Normalize(&Direction, &Direction);

					OBJECTMANAGER->AddObject(new cEnemyRadianBullet(m_pos, Direction, 300, 1));
				}
				m_pattern2++;
			}
			else if (m_Timer[4]->Update() && m_pattern2 == 2)
			{
				Start.x = m_pos.x + 200 * cos(rot);
				Start.y = m_pos.y + 200 * sin(rot);

				for (float i = 0; i < 46; i++, angle += Rot)
				{
					Vec2 Direction = Vec2(m_pos.x + (cosf(angle) * 90), m_pos.y + (sinf(angle) * 90));

					Direction = Direction - m_pos;

					D3DXVec2Normalize(&Direction, &Direction);

					OBJECTMANAGER->AddObject(new cEnemyRadianBullet(m_pos, Direction, 300, 1));
				}
				m_pattern2 = 1;
			}
		}
		else if (m_CurTime - m_OldTime > 12000 && m_CurTime - m_OldTime <= 15000)
		{
			if (m_Timer[5]->Update() && m_pattern3 == 1)
			{
				OBJECTMANAGER->AddObject(new cEnemy(9, 300, Vec2(-100, 50)));
				OBJECTMANAGER->AddObject(new cEnemy(9, 300, Vec2(-100, WINSIZEY - 50)));
				m_pattern3++;
			}
			else if (m_Timer[5]->Update() && m_pattern3 == 2)
			{
				OBJECTMANAGER->AddObject(new cEnemy(9, 300, Vec2(WINSIZEX + 100, 50)));
				OBJECTMANAGER->AddObject(new cEnemy(9, 300, Vec2(WINSIZEX + 100, WINSIZEY -50)));
				m_pattern3 = 0;
			}
		}
		else if (m_CurTime - m_OldTime > 15000 && m_CurTime - m_OldTime <= 18500)
		{
			if (m_Timer[5]->Update())
			{
				Start.x = m_pos.x + 200 * cos(rot);
				Start.y = m_pos.y + 200 * sin(rot);

				for (float i = 0; i < 20; i++, angle += Rot2)
				{
					Vec2 Direction = Vec2(m_pos.x + (cosf(angle) * 90), m_pos.y + (sinf(angle) * 90));

					Direction = Direction - m_pos;

					D3DXVec2Normalize(&Direction, &Direction);

					OBJECTMANAGER->AddObject(new cEnemyRadianBullet(m_pos, Direction, 300, 1));
				}
			}
		}
		else if (m_CurTime - m_OldTime > 22000)
		{
			m_pattern3 = 1;
			m_OldTime = m_CurTime;
		}
	}
	else if (GetHp() > 0)
	{
		if (count == 2)
		{
			m_pattern1 = 1, m_pattern2 = 1, m_pattern3 = 1;
			count = 1, temp = 300;
			m_OldTime = m_CurTime;
		}

		if(m_Timer[5]->Update())
			OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x, m_pos.y), 700, 1));

		if (m_Timer[5]->Update())
		{
			Rot2 = D3DX_PI * 2 / num;

			Start.x = m_pos.x + 200 * cos(rot);
			Start.y = m_pos.y + 200 * sin(rot);

			for (float i = 0; i < num; i++, angle += Rot2)
			{
				Vec2 Direction = Vec2(m_pos.x + (cosf(angle) * 90), m_pos.y + (sinf(angle) * 90));

				Direction = Direction - m_pos;

				D3DXVec2Normalize(&Direction, &Direction);

				OBJECTMANAGER->AddObject(new cEnemyRadianBullet(m_pos, Direction, temp, 1));
			}

			if (num != 25)
			{
				num += 5;
			}
			else
			{
				num = 10;
			}
			if (temp != 600)
			{
				temp += 100;
			}
			else
			{
				temp = 300;
			}
		}

	}
}

void cBoss::SetTimer()
{
	m_Timer[0] = new cTimer(0.45f);
	m_Timer[1] = new cTimer(1.4f);
	m_Timer[2] = new cTimer(0.1f);
	m_Timer[3] = new cTimer(0.85f);
	m_Timer[4] = new cTimer(1.7f);
	m_Timer[5] = new cTimer(1.f);
	m_Timer[6] = new cTimer(3.f);
}
