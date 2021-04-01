#pragma once
class cTexture
{
public:
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	cTexture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}
};