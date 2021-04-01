#pragma once
#include "cScene.h"

class cScrollMap;
class Stage : public cScene
{
private:
	cTexture* m_image;
	cTexture* m_image_bulletMod[2];
	cScrollMap* sc;
	cTimer* m_Timer;

	DWORD	        m_CurTime, m_CurTime2, m_CurTime3;
	DWORD			m_OldTime, m_OldTime2, m_OldTime3;

	int				stage, m_speed;

	bool			bossSpawn, chk;

	void			EnemySpawn1();
	void			EnemySpawn2();
public:
	Stage();
	~Stage();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;

};

