#pragma once
#include "cObject.h"

class cEnemyDeadEffect:public cObject
{
private:
	cTexture* m_image[7];
	cTimer*   m_Timer;
	Vec2	  m_pos;
	int		  m_ani;

public:
	cEnemyDeadEffect(Vec2 pos);
	~cEnemyDeadEffect();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

