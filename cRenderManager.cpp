#include "DXUT.h"

cRenderManager::cRenderManager()
{

    g_device->CreateVertexBuffer(sizeof(sVertexType) * 4, D3DUSAGE_WRITEONLY, sVertexType::FVF, D3DPOOL_DEFAULT, &m_vb, NULL);

    sVertexType* pVertices = nullptr;

    m_vb->Lock(0, 0, (void**)&pVertices, 0);

    pVertices[0].m_pos = D3DXVECTOR3(-0.5f, 0.5f, 0.f);
    pVertices[1].m_pos = D3DXVECTOR3(0.5f, 0.5f, 0.f);
    pVertices[2].m_pos = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
    pVertices[3].m_pos = D3DXVECTOR3(0.5f, -0.5f, 0.f);

    //0   1
    //
    //2 3

    pVertices[0].m_uv = D3DXVECTOR2(0, 0);
    pVertices[1].m_uv = D3DXVECTOR2(1, 0);
    pVertices[2].m_uv = D3DXVECTOR2(0, 1);
    pVertices[3].m_uv = D3DXVECTOR2(1, 1);

    m_vb->Unlock();

    g_device->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_ib, NULL);

    WORD idx[] = { 1, 2, 0, 1, 3, 2 };

    void* pIndices = NULL;

    m_ib->Lock(0, 0, &pIndices, 0);
    memcpy(pIndices, idx, sizeof(WORD) * 6);
    m_ib->Unlock();
    //--빌보딩용 버퍼 생성

    //빌보딩용 버퍼 적용
    g_device->SetStreamSource(0, m_vb, 0, sizeof(sVertexType));
    g_device->SetFVF(sVertexType::FVF);
    g_device->SetIndices(m_ib);
    //--빌보딩용 버퍼 적용

    g_device->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //g_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    //투영 행렬 적용
    D3DXMATRIXA16 matProj;

    D3DXMatrixOrthoRH(&matProj, WINSIZEX*SizeX, WINSIZEY*SizeY, 0, 100);
    g_device->SetTransform(D3DTS_PROJECTION, &matProj);
    //--투영 행렬 적용

    m_camPos = D3DXVECTOR3(0.f, 0.f, 100.f);
    m_camLook = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_camUp = D3DXVECTOR3(0.f, 0.f, 0.f);

    D3DXMatrixLookAtRH(&matView, &m_camPos, &m_camLook, &m_camUp);
    g_device->SetTransform(D3DTS_VIEW, &matView);
}

cRenderManager::~cRenderManager()
{
    m_ib->Release();
    m_vb->Release();
}

void cRenderManager::SetCamPos(const D3DXVECTOR3 m_pos)
{
	m_camPos = m_pos;
}

void cRenderManager::SetCamLook(const D3DXVECTOR3 m_pos)
{
	m_camLook = m_pos ;
}

void cRenderManager::SetCamSize(float sizeX,float sizeY)
{
    D3DXMATRIXA16 matProj;

	D3DXMatrixOrthoRH(&matProj, WINSIZEX*sizeX, WINSIZEY*sizeY, 0, 100);
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
}

float cRenderManager::GetCamPosX()
{
	return m_camPos.x;
}

float cRenderManager::GetCamPosY()
{
	return m_camPos.y;
}





void cRenderManager::CamUpdate(D3DXVECTOR2 pos)
{
	
	  D3DXMATRIXA16 matCam;
  m_camUp = D3DXVECTOR3(0, 1.f, 0.f);
  m_camPos = Vec3(pos.x,pos.y,100);
  m_camLook = Vec3(pos.x,pos.y,0);
	 D3DXMatrixLookAtRH(&matCam, &Vec3(m_camPos.x -WINSIZEX /2  ,-m_camPos.y +WINSIZEY /2 , 100), &Vec3 (m_camLook.x- WINSIZEX / 2 ,-m_camLook.y + WINSIZEY / 2,0), &m_camUp);
	//  D3DXMatrixLookAtRH(&matCam, &m_camPos, &m_camLook, &m_camUp);

	  g_device->SetTransform(D3DTS_VIEW, &matCam);
	
}

void cRenderManager::Render(cTexture* texturePtr, float x, float y, float z,float rot)
{
    D3DXMATRIXA16 matPos, matScale, matWorld,matRot;
    D3DXMatrixTranslation(&matPos, x - WINSIZEX / 2 + texturePtr->info.Width / 2, -(y - WINSIZEY / 2 + texturePtr->info.Height / 2), z);
    D3DXMatrixScaling(&matScale, texturePtr->info.Width, texturePtr->info.Height, 1);
	D3DXMatrixRotationZ(&matRot,rot);
    matWorld = matScale * matRot* matPos;
    g_device->SetTransform(D3DTS_WORLD, &matWorld);
    g_device->SetTexture(0, texturePtr->texturePtr);
    g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void cRenderManager::CenterRender(cTexture* texturePtr, float x, float y, float z, float rot)
{
    D3DXMATRIXA16 matPos, matScale, matWorld,matRot;
    D3DXMatrixTranslation(&matPos, x - WINSIZEX / 2, -(y - WINSIZEY / 2), z);
    D3DXMatrixScaling(&matScale, texturePtr->info.Width , texturePtr->info.Height, 1);
	D3DXMatrixRotationZ(&matRot,rot);
    matWorld = matScale * matRot * matPos;
    g_device->SetTransform(D3DTS_WORLD, &matWorld);
    g_device->SetTexture(0, texturePtr->texturePtr);
    g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void cRenderManager::ScaleRender(cTexture * texturePtr, float x, float y, float scale, float z, float rot)
{
	D3DXMATRIXA16 matPos, matScale, matWorld, matRot;
	D3DXMatrixTranslation(&matPos, x - WINSIZEX / 2, -(y - WINSIZEY / 2), z);
	D3DXMatrixScaling(&matScale, texturePtr->info.Width * scale, texturePtr->info.Height * scale, 1);
	D3DXMatrixRotationZ(&matRot, rot);
	matWorld = matScale * matRot * matPos;
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
	g_device->SetTexture(0, texturePtr->texturePtr);
	g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void cRenderManager::AnimeRender(cTexture * texturePtr, float x, float y, float time, float z)
{
	D3DXMATRIXA16 matPos, matScale, matWorld;
	D3DXMatrixTranslation(&matPos, x - WINSIZEX / 2, -(y - WINSIZEY / 2), z);
	D3DXMatrixScaling(&matScale, texturePtr->info.Width, texturePtr->info.Height, 1);
	matWorld = matScale * matPos;
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
	g_device->SetTexture(0, texturePtr->texturePtr);
	g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

void cRenderManager::AScaleRender(cTexture * texturePtr, float x, float y, float z, float rot)
{
	D3DXMATRIXA16 matPos, matScale, matWorld, matRot;
	D3DXMatrixTranslation(&matPos, x - WINSIZEX / 2, -(y - WINSIZEY / 2), z);
	D3DXMatrixScaling(&matScale, texturePtr->info.Width * 200, texturePtr->info.Height * 20, 1);
	D3DXMatrixRotationZ(&matRot, rot);
	matWorld = matScale * matRot * matPos;
	g_device->SetTransform(D3DTS_WORLD, &matWorld);
	g_device->SetTexture(0, texturePtr->texturePtr);
	g_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}