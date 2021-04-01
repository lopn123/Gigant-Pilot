#pragma once
class cTimer
{
public :
	float m_start = 0;
	float m_delay = 0;
public:
	cTimer(float delay);
	
	~cTimer();
	bool Update();
};

