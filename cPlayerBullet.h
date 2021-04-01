#pragma once
#include "cObject.h"

class cPlayerBullet : public cObject
{
private:
	cTexture* m_image;
	Vec2	  m_pos, m_dir;
	int		  m_dmg;

public:
	cPlayerBullet(const Vec2& pos, Vec2 Pos, int dmg);
	virtual ~cPlayerBullet();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

