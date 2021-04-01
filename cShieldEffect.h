#pragma once
#include "cObject.h"

class cShieldEffect :public cObject
{
private:
	cTexture* m_image[8];
	cTimer*	  m_Timer[2];
	int		  m_ani;

public:
	cShieldEffect();
	~cShieldEffect();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};