#pragma once
#include "stdafx.h"

struct CAMERA_DATA
{
	D3DXMATRIX view;
	D3DXMATRIX proj;
};

struct TRANSFORM_DATA
{
	D3DXMATRIX world;
};

struct TEXTURE_DATA
{
	D3DXVECTOR2 sprite_offset;
	D3DXVECTOR2 sprite_size;
	D3DXVECTOR2 texture_size;
	float is_texture;
	float padding;
	D3DXCOLOR color_key;
};

struct COLOR_DATA
{
	D3DXCOLOR color;
};