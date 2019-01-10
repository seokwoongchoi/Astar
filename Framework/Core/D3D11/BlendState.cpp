#include "stdafx.h"
#include "BlendState.h"

BlendState::BlendState(Graphics * graphics)
	: graphics(graphics)
	, state(nullptr)
	, backState(nullptr)
{
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

BlendState::~BlendState()
{
	Clear();
}

void BlendState::Create()
{
	Clear();

	HRESULT hr = graphics->GetDevice()->CreateBlendState(&desc, &state);
	assert(SUCCEEDED(hr));
}

void BlendState::Clear()
{
	SAFE_RELEASE(state);
}

void BlendState::BindPipeline()
{
	graphics->GetDeviceContext()->OMGetBlendState(&backState, nullptr, nullptr);
	graphics->GetDeviceContext()->OMSetBlendState(state, nullptr, 0xffffffff);
}

void BlendState::UnbindPipeline()
{
	graphics->GetDeviceContext()->OMSetBlendState(backState, nullptr, 0xffffffff);
}

void BlendState::AlphaToCoverageEnable(const bool & val)
{
	desc.AlphaToCoverageEnable = val;
	Create();
}

void BlendState::BlendEnable(const bool & val)
{
	desc.RenderTarget[0].BlendEnable = val;
	Create();
}
