#include "DXUT.h"
#include "cEnemy.h"
#include "cEnemyBullet.h"
#include "cEnemyBulletMissile.h"
#include "cEnemyDirectShot.h"
#include "cEnemyDeadEffect.h"

cEnemy::cEnemy(int EnemyType, int speed, Vec2 Pos, bool copy)
	:m_EnemyType(EnemyType), m_speed(speed), Pos(Pos), m_copy(copy)
{
	m_image[0] = IMAGEMANAGER->FindImage("LEnemy");
	m_image[1] = IMAGEMANAGER->FindImage("LEnemy1");

	m_image[2] = IMAGEMANAGER->FindImage("REnemy");
	m_image[3] = IMAGEMANAGER->FindImage("REnemy1");

	temp = 0, count = 0;

	MakeTag("Enemy");
	SetHp(20);

	SetPos(m_EnemyType);
}

cEnemy ::~cEnemy()
{ 
	OBJECTMANAGER->AddObject(new cEnemyDeadEffect(m_pos));
}

void cEnemy::Init()
{
	m_OldTime = m_CurTime = timeGetTime();
}

void cEnemy::Update()
{
	if (Pos.x > WINSIZEX / 2)
	{
		SetRect(RECT{
			long(m_pos.x - m_image[0]->info.Width / 2) ,
			long(m_pos.y - m_image[0]->info.Height / 2),
			long(m_pos.x + m_image[0]->info.Width / 2),
			long(m_pos.y + m_image[0]->info.Height / 2)
			});
	}
	else if (Pos.x < WINSIZEX / 2)
	{
		SetRect(RECT{
			long(m_pos.x - m_image[2]->info.Width / 2) ,
			long(m_pos.y - m_image[2]->info.Height / 2),
			long(m_pos.x + m_image[2]->info.Width / 2),
			long(m_pos.y + m_image[2]->info.Height / 2)
			});
	}

	if (m_pos.x > WINSIZEX + 150 || m_pos.x < -150 || m_pos.y > WINSIZEY + 150 || m_pos.y < -150)
	{
		DestroyObj();
	}
	if (GetHp() <= 0)
	{
		DestroyObj();
		OBJECTMANAGER->score += 10;
	}

	if (OBJECTMANAGER->freeze == false)
	{
		EnemyPattern(m_EnemyType);
	}
}

void cEnemy::Render()
{
	if (Pos.x > WINSIZEX / 2)
	{
		if (OBJECTMANAGER->freeze == true)
			RENDER->CenterRender(m_image[1], m_pos.x, m_pos.y);
		else
			RENDER->CenterRender(m_image[0], m_pos.x, m_pos.y);
	}
	else if (Pos.x < WINSIZEX / 2)
	{
		if (OBJECTMANAGER->freeze == true)
			RENDER->CenterRender(m_image[3], m_pos.x, m_pos.y);
		else
			RENDER->CenterRender(m_image[2], m_pos.x, m_pos.y);
	}

	if(OBJECTMANAGER->freeze == false)
		m_CurTime = timeGetTime();
}

void cEnemy::UIRender()
{
}

void cEnemy::Collision(cObject * obj)
{
	if (OBJECTMANAGER->invincible == false && OBJECTMANAGER->shield == false)
	{
		if (obj->GetTag() == "Player")
		{
			obj->HitHp(1);
			DestroyObj();
			OBJECTMANAGER->invincible = true;
		}
	}
	else
	{
		if (obj->GetTag() == "Player")
		{
			DestroyObj();
		}
	}
	
}

void cEnemy::SetPos(int EnemyType)
{
	if (EnemyType == 0)
	{
		m_pos = Vec2(WINSIZEX + 150, (rand() % 850) + 50);
		Pos = m_pos;
	}
	else if (EnemyType == 1)
	{
		m_pos = Vec2(1400, -150);
		Pos = m_pos;
	}
	else if (EnemyType == 2)
	{
		m_pos = Vec2(1400, WINSIZEY + 150);
		Pos = m_pos;
	}
	else
	{
		m_pos = Pos;
	}
}

void cEnemy::EnemyPattern(int EnemyType)
{
	switch (EnemyType)
	{
	case 0: //°Á ∆–≈œ (¿œπ›√—)
		m_pos.x -= m_speed * DXUTGetElapsedTime();
		
		if (m_CurTime - m_OldTime >= 1000)
		{
			OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 0), 1));
			m_OldTime = m_CurTime;
		}

		break;
	case 1: // ¢◊ °Ê ∆–≈œ (¿œπ›√—)
		if (m_pos.y <= WINSIZEY / 2 - 50)
		{
			m_pos.x -= m_speed * DXUTGetElapsedTime();
			m_pos.y += m_speed * DXUTGetElapsedTime();

		}
		else
		{
			m_pos.x += m_speed * DXUTGetElapsedTime();
		}

		if (m_CurTime - m_OldTime >= 800)
		{
			OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 0), 1));
			m_OldTime = m_CurTime;
		}

		break;
	case 2: // ¢ÿ °Ê ∆–≈œ (¿œπ›√—)
		if (m_pos.y >= WINSIZEY / 2 + 50) 
		{
			m_pos.x -= m_speed * DXUTGetElapsedTime();
			m_pos.y -= m_speed * DXUTGetElapsedTime();
		}
		else
		{
			m_pos.x += m_speed * DXUTGetElapsedTime();
		}

		if (m_CurTime - m_OldTime >= 800)
		{
			OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 0), 1));
			m_OldTime = m_CurTime;
		}

		break;
	case 3: // °Á ∏  ∞°µÊ √§øÏ¥¬ ¿˚ ∆–≈œ (¿œπ›√—)
		if (m_copy == true)
		{
			for (int i = 0; i < 8; i++)
			{
				temp += 100;
				OBJECTMANAGER->AddObject(new cEnemy(3, m_speed, Vec2(m_pos.x, m_pos.y + temp), false));
			}

			m_copy = false;
		}

		m_pos.x -= m_speed * DXUTGetElapsedTime();

		if (m_CurTime - m_OldTime >= 2000)
		{
			OBJECTMANAGER->AddObject(new cEnemyBullet(Vec2(m_pos.x - 20, m_pos.y), Vec2(1000, 0), 1));
			m_OldTime = m_CurTime;
		}

		break;
	case 4: //¢Ÿ, ¢÷ ∆–≈œ ()
		m_pos.x += m_speed * DXUTGetElapsedTime();

		if (Pos.y < WINSIZEY / 2)
		{
			m_pos.y += (m_speed - 200) * DXUTGetElapsedTime();
		}
		else
		{
			m_pos.y -= (m_speed - 200) * DXUTGetElapsedTime();
		}
		break;
	case 5: //¢◊,¢ÿ ∆–≈œ ()
		m_pos.x -= m_speed * DXUTGetElapsedTime();

		if (Pos.y < WINSIZEY / 2)
		{
			m_pos.y += (m_speed - 200) * DXUTGetElapsedTime();
		}
		else
		{
			m_pos.y -= (m_speed - 200) * DXUTGetElapsedTime();
		}
		break;
	case 6: //°Á ¢Ÿ °Ê, °Á ¢÷ °Ê ∆–≈œ (¿Øµµ≈∫)
		if (m_pos.x > 100 && count == 0)
		{
			m_pos.x -= m_speed * DXUTGetElapsedTime();

			if (m_CurTime - m_OldTime >= 7000)
			{
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x - 20, m_pos.y), 1));
				m_OldTime = m_CurTime;
			}
		}
		else if (m_pos.x <= 100 && count == 0)
		{
			count++;
		}

		if (count == 1)
		{
			if (m_pos.y > WINSIZEY / 2)
			{
				if (m_pos.y >= WINSIZEY - 250)
				{
					m_pos.y -= (m_speed + 200) * DXUTGetElapsedTime();
				}
			}
			else if (m_pos.y < WINSIZEY / 2)
			{
				if (m_pos.y <= 250)
				{
					m_pos.y += (m_speed + 200) * DXUTGetElapsedTime();
				}
			}

			m_pos.x += (m_speed + 500) * DXUTGetElapsedTime();
		}

		break;
	case 7: //°Á, °Ê ∆–≈œ (¿Øµµ≈∫)
		if (Pos.x > WINSIZEX)
		{
			m_pos.x -= m_speed * DXUTGetElapsedTime();
		}
		else if (Pos.x < 0)
		{
			m_pos.x += m_speed * DXUTGetElapsedTime();
		}

		if (m_CurTime - m_OldTime >= 2000)
		{
			OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x, m_pos.y), 800, 1));
			m_OldTime = m_CurTime;
		}

		break;
	case 8: //°Ë, °È ∆–≈œ (¿Øµµ≈∫)
		if (Pos.y > WINSIZEY)
		{
			m_pos.y -= m_speed * DXUTGetElapsedTime();
		}
		else if (Pos.y < 0)
		{
			m_pos.y += m_speed * DXUTGetElapsedTime();
		}

		if (m_CurTime - m_OldTime >= 2000)
		{
			OBJECTMANAGER->AddObject(new cEnemyDirectShot(Vec2(m_pos.x, m_pos.y), 800, 1));
			m_OldTime = m_CurTime;
		}
		break;
	case 9: //≈Õ∑ø ∆–≈œ (¿Øµµ≈∫)
		if (count < 3)
		{
			if (m_pos.x >= WINSIZEX - 150)
			{
				m_pos.x -= m_speed * DXUTGetElapsedTime();
			}
			else if (m_pos.x <= 150)
			{
				m_pos.x += m_speed * DXUTGetElapsedTime();
			}

			if (m_CurTime - m_OldTime >= 2000)
			{
				OBJECTMANAGER->AddObject(new cEnemyBulletMissile(Vec2(m_pos.x, m_pos.y), 1));
				
				count++;
				m_OldTime = m_CurTime;
			}
		}
		else
		{
			if (Pos.x > WINSIZEX/2)
				m_pos.x += m_speed * DXUTGetElapsedTime();

			else
				m_pos.x -= m_speed * DXUTGetElapsedTime();
		}
		break;
	}
}