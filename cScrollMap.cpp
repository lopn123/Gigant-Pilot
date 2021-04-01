#include "DXUT.h"
#include "cScrollMap.h"


cScrollMap::cScrollMap()
{
	m_image = IMAGEMANAGER->FindImage("Stage1");
	m_pos.x = WINSIZEX / 2;
	m_pos.y = WINSIZEY / 2;
	m_speed = 0;
}


cScrollMap::~cScrollMap()
{
}

void cScrollMap::Render(int speed)
{
	m_speed += speed * DXUTGetElapsedTime();
	float RenderPos = (int)m_speed % m_image->info.Width;
	RENDER->CenterRender(m_image, m_pos.x + m_image->info.Width - RenderPos, m_pos.y);
	RENDER->CenterRender(m_image, m_pos.x - RenderPos, m_pos.y);
}


