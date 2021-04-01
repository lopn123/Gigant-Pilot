#pragma once
#include "cObject.h"

class cTimer;
class cPlayer : public cObject
{
private:
	Vec2			m_pos;
	int				m_move;

	bool			Ani;
	cTexture*		m_image[3];
	cTimer*			m_Timer[4];

	DWORD	        m_CurTime, m_CurTime2;
	DWORD			m_OldTime, m_OldTime2;

	void			KeyPress();

public:
	cPlayer();
	virtual ~cPlayer();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
	virtual void Collision(cObject* obj) override;
};

