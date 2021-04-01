#pragma once
#include "cObject.h"

class cEnemyBullet : public cObject
{
private:
	cTexture* m_image;
	Vec2	  m_pos, m_dir, Pos;

	int		  m_dmg;
	float	  Rot;

public:
	cEnemyBullet(const Vec2& pos, Vec2 Pos, int dmg);
	virtual ~cEnemyBullet();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

