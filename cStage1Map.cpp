#include "DXUT.h"
#include "cStage1Map.h"

cStage1Map::cStage1Map()
	:m_speed(0)
{
	m_image = IMAGEMANAGER->AddImage("Map", "./image/Map.jpg");

}

cStage1Map::~cStage1Map()
{
}

void cStage1Map::Update(float speed)
{
	m_speed -= speed * DXUTGetElapsedTime();
}

void cStage1Map::Render()
{
	float RenderPos = (int)m_speed % m_image->info.Height;
	RENDER->CenterRender(m_image,1000/2,800/2 + m_image->info.Height - RenderPos);
	RENDER->CenterRender(m_image, 1000/2 , 800 / 2 - RenderPos);
}
