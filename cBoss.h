#pragma once
#include "cObject.h"

class cBoss : public cObject
{
private:
	cTexture*		m_image;
	cTimer*			m_Timer[7];

	Vec2			m_pos, Start;

	DWORD			m_CurTime, m_CurTime2;
	DWORD			m_OldTime, m_OldTime2;
	
	int				m_speed, speed,temp, count, num;

	int				m_pattern1, m_pattern2, m_pattern3;

	float			angle, Rot, Rot2, rot;

	void		    pattern();
	void			SetTimer();
public:
	cBoss();
	virtual ~cBoss();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

