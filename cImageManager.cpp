#include "DXUT.h"

cImageManager::cImageManager()
{
}


cImageManager::~cImageManager()
{
	for (auto iter : m_images)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
}

//�ҷ��� �̹����� �θ� �̸��� ���
cTexture* cImageManager::AddImage(const string& key, const string& path, int num )
{
	
	 
	auto find = m_images.find(key);//�̹� �ִ� �̸��� �ٽ� ������ �ϴ°� �ƴ��� Ȯ���غ���
	
	if (find == m_images.end())
	{
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;

			if(D3DXCreateTextureFromFileExA(g_device,path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,0,0,
				D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			cTexture* text = new cTexture(texturePtr, info);
			m_images.insert(make_pair(key, text));
			return text;
		}
		#pragma region �ε�����
		DEBUG_LOG("ERROR! �̹��� �ε��� �����߽��ϴ�. ���ϰ�θ� �ٽ� Ȯ�����ּ���");
		DEBUG_LOG("\tkey :" << key.c_str() << "\t path : " << path.c_str());
#pragma endregion
		//�̹��� �ε��� �����������(���� ����, cpu�޸� �������) �̰����� ���� �ȴ�
		return nullptr;
	}
	//�̹� �ҷ��� �̹����� �ٽ� �ҷ����� �߰ų�
	//�ٸ� �̹����� ���� �̸����� ���� ������� �̰����� ���� �ȴ�
	return find->second;
}

cTexture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);//�̸����� �̹����� ã�ƺ���
	if (find == m_images.end()) return nullptr;//������ nullptr�� ��´�
	return find->second;//������ �װ� ��´�
}