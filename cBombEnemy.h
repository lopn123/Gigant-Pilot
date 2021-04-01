#pragma once
#include "cObject.h"

class cBombEnemy : public cObject
{
private:
	cTexture*		m_image[2];
	cTimer*			m_Timer;

	Vec2			m_pos;
	int				m_speed;
	float			m_angle;

public:
	cBombEnemy(Vec2 pos);
	virtual ~cBombEnemy();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

