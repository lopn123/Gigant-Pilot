#pragma once
#include "cObject.h"
class cObject;
class cEnemyRadianBullet : public cObject
{
private:
	cTexture* m_image;

	Vec2 m_pos, Pos;
	Vec2 m_rot;
	float Rot;
	int  m_speed, m_dmg;

public:
	cEnemyRadianBullet(Vec2 pos, Vec2 rot, int speed, int dmg);
	virtual ~cEnemyRadianBullet();
public:
	virtual void Update();
	virtual void Render();
	virtual void UIRender();
	virtual void Release();
	virtual void Collision(cObject* obj);
};

