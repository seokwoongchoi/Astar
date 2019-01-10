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
	D3D11_MAPPED_SUBRESOURCE mappedResource; //����

	//���ħ
	HRESULT hr = graphics->GetDeviceContext()->Map
	(
		cbuffer,
		0,
		D3D11_MAP_WRITE_DISCARD, //�ӹ��ϼ��ϸ� ������ ���
		0,
		&mappedResource // �����Ӹ�
	);
	assert(SUCCEEDED(hr));
	
	return mappedResource.pData; //���� �⵿
}

void ConstantBuffer::Unmap()
{
	//�������
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