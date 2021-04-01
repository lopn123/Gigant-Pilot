#pragma once
#include "singleton.h"

class cTexture;
class cRenderManager : public singleton<cRenderManager>
{
private:
    struct sVertexType
    {
        D3DXVECTOR3 m_pos;
        D3DXVECTOR2 m_uv;

        inline static constexpr DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
    };
public:
    LPDIRECT3DVERTEXBUFFER9 m_vb;
    LPDIRECT3DINDEXBUFFER9 m_ib;
public:
    D3DXVECTOR3 m_camPos = D3DXVECTOR3(0.f, 0.f, 100.f);
	D3DXVECTOR3 m_camLook = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_camUp = D3DXVECTOR3(0.f, 1.f, 0.f);
public:
	int b=0;
	float Scale;
    cRenderManager();
    ~cRenderManager();
	int a = 2;
	void  SetCamPos(const D3DXVECTOR3 m_pos);
	void SetCamLook(const D3DXVECTOR3 m_pos);
	D3DXMATRIXA16 matView,matCam;
	void SetCamSize(float sizeX,float sizeY);
	float GetCamPosX();
	float GetCamPosY();
	bool bc =true;
	float SizeX=1, SizeY=1 ;
    void CamUpdate(D3DXVECTOR2 pos);
    void Render(cTexture* texturePtr, float x, float y, float z = 0, float rot=0);
    void CenterRender(cTexture* texturePtr, float x, float y, float z = 0, float rot=0);
	void ScaleRender(cTexture* texturePtr, float x, float y, float scale, float z = 0, float rot = 0);
	void AnimeRender(cTexture* texturePtr, float x, float y, float time, float z = 0);
	void AScaleRender(cTexture * texturePtr, float x, float y, float z, float rot);
	
};

#define RENDER cRenderManager::GetInstance()