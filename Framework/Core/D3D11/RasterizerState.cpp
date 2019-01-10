#include "stdafx.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(Graphics * graphics)
	: graphics(graphics)
	, state(nullptr)
	, backState(nullptr)
{
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.FrontCounterClockwise = false;
}

RasterizerState::~RasterizerState()
{
	Clear();
}

void RasterizerState::Create()
{
	Clear();

	HRESULT hr = graphics->GetDevice()->CreateRasterizerState(&desc, &state);
	assert(SUCCEEDED(hr));
}

void RasterizerState::Clear()
{
	SAFE_RELEASE(state);
}

void RasterizerState::BindPipeline()
{
	graphics->GetDeviceContext()->RSGetState(&backState);
	graphics->GetDeviceContext()->RSSetState(state);
}

void RasterizerState::UnbindPipeline()
{
	graphics->GetDeviceContext()->RSSetState(backState);
}

void RasterizerState::CullMode(const D3D11_CULL_MODE & val)
{
	desc.CullMode = val;
	Create();
}

void RasterizerState::FillMode(const D3D11_FILL_MODE & val)
{
	desc.FillMode = val;
	Create();
}

void RasterizerState::FrontCounterClockwise(const bool & val)
{
	desc.FrontCounterClockwise = val;
	Create();
}
