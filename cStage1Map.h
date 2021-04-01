#pragma once
class cStage1Map
{
private:
	cTexture * m_image;
	float m_speed;
public:
	cStage1Map();
	~cStage1Map();
public:
	void Update(float speed);
	void Render();
};

