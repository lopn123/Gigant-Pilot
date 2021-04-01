#include "DXUT.h"
#include "cObject.h"
#include "cPlayer.h"

void cObjectManager::Update()
{
	RT = {0,0,0,0};
	for (auto iter = m_objList.begin(); iter != m_objList.end();)
	{
		
		(*iter)->Update();
	
		if((*iter)->GetRect().bottom != RT.bottom && (*iter)->GetRect().right != RT.right && (*iter)->GetRect().left != RT.left && (*iter)->GetRect().top != RT.top)
		{
			for (auto& Other : m_objList)
			{
		if((*iter) != Other)
				if (IntersectRect(&Rt, &(*iter)->GetRect(), &Other->GetRect()))
				{
  					(*iter)->Collision(Other);
				}
			}
		}
			if ((*iter)->IsValid())
		{
      			delete (*iter);
			iter = m_objList.erase(iter);
		}
		else
			++iter;
	}


}

void cObjectManager::Render()
{
	for (auto iter = m_objList.begin(); iter != m_objList.end();)
	{
		(*iter)->Render();
		++iter;
	}
}


cObject * cObjectManager::AddObject(cObject * _newObj)
{
	if (_newObj)
		m_objList.push_back(_newObj);
	else
	{
		std::cout << "ºó¿ÀºêÁ§Æ®";
	}
	return _newObj;
}

void cObjectManager::UIRender()
{
	for (auto iter :m_objList)
	{
		iter->UIRender();
	}
}

void cObjectManager::Release()
{
	for (auto iter : m_objList)
	{
		SAFE_DELETE(iter);

	}
	m_objList.clear();
}