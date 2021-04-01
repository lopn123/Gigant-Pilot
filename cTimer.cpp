#include "DXUT.h"
#include "cTimer.h"

cTimer::cTimer(float delay)
	:m_delay(delay)
{
}

cTimer::~cTimer()
{
}

bool cTimer::Update()
{
	m_start += DXUTGetElapsedTime();

	if (m_start > m_delay)
	{
		m_start = 0.f;
		return true;
	}
	return false;
}
