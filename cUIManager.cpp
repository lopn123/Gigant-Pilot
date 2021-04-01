#include "DXUT.h"

cUIManager::cUIManager()
	: m_sprite(nullptr)
{
	D3DXCreateSprite(g_device, &m_sprite);
}

cUIManager::~cUIManager()
{
	m_sprite->Release();
}

void cUIManager::Begin()
{
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//g_device->SetTransform(D3DTS_WORLD, &matWorld);
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cUIManager::End()
{
	m_sprite->End();
}

void cUIManager::Render(cTexture* texturePtr, float x, float y, Vec2 size, float rot, D3DCOLOR color)
{                                   
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixTransformation2D(&mat, nullptr,0, &size, nullptr,rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cUIManager::Render(cTexture* texturePtr, float x, float y,float scale, float rot)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

//void cUIManager::CenterRender(cTexture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
//{
//	Render(texturePtr, x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2, size, rot, color);
//}

void cUIManager::CenterRender(cTexture* texturePtr, float x, float y, float rot)
{
	Render(texturePtr, x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2, rot);
}

void cUIManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cUIManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

void cUIManager::TextDraw(const string & str, D3DXVECTOR2 pos, float size, D3DCOLOR color, bool Center)
{
	D3DXMATRIXA16 mat;
	if (!Center)
	{
		D3DXCreateFontA(g_device, size, 0, 10, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, "Cooper Blk BT", &pFont);
		D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
	}
	else
	{
		D3DXCreateFontA(g_device, size, 0, 0, 1, FALSE, DEFAULT_CHARSET, 0, 0, 0, "Cooper Blk BT", &pFont);

		D3DXMatrixTranslation(&mat, pos.x - size * (str.size() * 0.25), pos.y - size / 2.f, 0);
	}
	m_sprite->SetTransform(&mat);
	pFont->DrawTextA(m_sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);
	SAFE_RELEASE(pFont);
}
