#include "stdafx.h"
#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(Graphics * graphics)
	: graphics(graphics)
	, cbuffer(nullptr)
{
}

ConstantBuffer::~ConstantBuffer()
{
	Clear();
}

inline void ConstantBuffer::Clear()
{
	SAFE_RELEASE(cbuffer);
}

void * ConstantBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource; //²¿ºÀ

	//°á°èÄ§
	HRESULT hr = graphics->GetDeviceContext()->Map
	(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //ÀÓ¹«¿Ï¼öÇÏ¸é Àº¹ÐÈ÷ Æó±â
		0,
		&mappedResource // ²¿ºÀÀÓ¸í
	);
	assert(SUCCEEDED(hr));
	
	return mappedResource.pData; //²¿ºÀ Ãâµ¿
}

void ConstantBuffer::Unmap()
{
	//°á°èÇØÁ¦
	graphics->GetDeviceContext()->Unmap(cbuffer, 0);
}

void ConstantBuffer::SetVS(const uint & startSlot)
{
	graphics->GetDeviceContext()->VSSetConstantBuffers
	(
		startSlot,
		1,
		&cbuffer
	);
}

void ConstantBuffer::SetPS(const uint & startSlot)
{
	graphics->GetDeviceContext()->PSSetConstantBuffers
	(
		startSlot,
		1,
		&cbuffer
	);
}