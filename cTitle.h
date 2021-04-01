#pragma once
#include "cScene.h"

#define PI 3.141592

class cTitle : public cScene
{
private:

	cTexture* m_image;

	cTexture* m_image_PlayOn;
	cTexture* m_image_SettingOn;
	cTexture* m_image_CreditOn;
	cTexture* m_image_ExitOn;
	
	cTexture* m_image_PlayOff;
	cTexture* m_image_SettingOff;
	cTexture* m_image_CreditOff;
	cTexture* m_image_ExitOff;

	cTexture* m_image_Play;
	cTexture* m_image_Setting;
	cTexture* m_image_Credit;
	cTexture* m_image_Exit;

	cTexture* credit;
	cTexture* setting;

	Vec2	  ButtonPos;

	int		  CurStatus, Return;

public:
	cTitle();
	~cTitle();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
};

