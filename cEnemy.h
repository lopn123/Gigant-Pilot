#pragma once
#include "cObject.h"

class cEnemy : public cObject
{
private:
	cTexture*		m_image[4];

	Vec2			m_pos, Pos;

	int				m_speed, temp;
	int				m_EnemyType, count;
	bool			m_copy;

	DWORD			m_CurTime;
	DWORD			m_OldTime;

	void SetPos(int EnemyType);
	void EnemyPattern(int EnemyType);

public:
	cEnemy(int EnemyType, int speed, Vec2 Pos = Vec2(0, 0), bool copy = false);
	virtual ~cEnemy();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

