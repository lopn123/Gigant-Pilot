#pragma once
#include "cObject.h"

class cEnemyDirectShot : public cObject
{
private:
	cTexture* m_image;
	Vec2	  m_pos, Pos, StartPos;

	int		  m_dmg, m_speed;
	float     Rot;

public:
	cEnemyDirectShot(const Vec2& pos, int speed, int dmg);
	virtual ~cEnemyDirectShot();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

