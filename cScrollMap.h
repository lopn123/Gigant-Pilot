#pragma once
class cScrollMap
{
private:
	cTexture* m_image;
	float	  m_speed;
	Vec2	  m_pos;

public:
	cScrollMap();
	~cScrollMap();

public:
	void Render(int speed);
};

