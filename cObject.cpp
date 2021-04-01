#include "DXUT.h"
#include "cObject.h"

cObject::cObject(const string & _name)
	:m_objName(_name)
{
}


void cObject::Init()
{
}

void cObject::Update()
{
}

void cObject::Render()
{
}

void cObject::Release()
{
}

void cObject::Collision(cObject * obj)
{
	
}

void cObject::UIRender()
{
}

bool cObject::IsOutMap(Vec2 pos)
{
	return (pos.x > WINSIZEX
		|| pos.x  < 0
		|| pos.y  > WINSIZEY
		|| pos.y  < 0);
}
