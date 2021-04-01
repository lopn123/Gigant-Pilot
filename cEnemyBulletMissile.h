#pragma once
#include "cObject.h"

class cEnemyBulletMissile : public cObject
{
private:
	cTexture* m_image;
	cTimer*	  m_Timer;

	Vec2	  m_pos, Pos;

	float	  Rot;

	int		  m_dmg;
	float     m_angle;
	bool      m_follow;

public:
	cEnemyBulletMissile(const Vec2& pos, int dmg);
	virtual ~cEnemyBulletMissile();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

