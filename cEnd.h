#pragma once

#include "cScene.h"

class cEnd : public cScene
{
private:
	cTexture* m_image;

public:
	cEnd();
	~cEnd();

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void UIRender() override;
};

