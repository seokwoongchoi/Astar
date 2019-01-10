#pragma once
#include "ISubsystem.h"

//Pipeline -> 기본 데이이터를 가공해서 출력해주는 흐름
//Directx11 에서는 Pipeline 을 Stage로 구분

//IA : 기본데이터를 입력받음
//IA <----- ID3D11Buffer* -----기본데이터(Vertex) : VertexBuffer
//   <----- ID3D11Buffer* -----기본데이터(Index)  : IndexBuffer
//   <----- ID3D11InputLayout* ----- Vertex 구성 정보
//   <----- Primitive Topology ----- Vertex 를 어떤 형태로 처리할것인지

//VS : 공간 변환(Local->World->View->Projection)
//VS - cbuffer(b0) <----- ID3D11Buffer* ----- Data : ConstantBuffer
//VS - Texture2D(t0) <----- ID3D11ShaderResourceView* ----- ID3D11Texture2D*
//VS - SamlerState(s0) <----- ID3D11SamplerState*

//RS : 변환된 정점을 어떻게 체울지(그릴지) 
//RS <------ ID3D11RasterizerState*
//   FrontCouterClockWise : 앞면의 판단 기준(true - 반시계, false - 시계)
//	 CullMode : CullFront, CullBack, CullNoe - 위에서 정한 fccw를 기준으로 어디를 자를지
//   FillMode : Wireframe, Solid

//PS : 변환된 정점과 RS에서 정한 방식으로 픽셀을 찍음
//PS - cbuffer(b0) <----- ID3D11Buffer* ----- Data : ConstantBuffer
//PS - Texture2D(t0) <----- ID3D11ShaderResourceView* ----- ID3D11Texture2D*
//PS - SamlerState(s0) <----- ID3D11SamplerState*

//OM : 렌더타겟들에 그려진 백버퍼들을 병합
//OM <----- ID3D11RenderTargetView* <----- ID3D11Texture*
//OM <----- ID3D11DepthStencilView* <----- ID3D11Texture*
//OM : 렌더타겟뷰랑 뎁스스텐실뷰 두개를 사용하는 이유는 
//	   렌더타겟뷰 하나만으로는 깊이정보를 저장할 수 가 없어서 뎁스스텐실 뷰를 추가로 사용
//     D3DXVECTOR3 -> x, y, z-->깊이
//OM : ID3D11BlendState*


//Pipeline을 모두 셋팅한후 DrawCall을 해줘야 그려짐
//Draw : VertexBuffer 만으로 그리는 놈
//DrawIndices : VertexBuffer와 IndexBuffer 를 가지고 그리는놈

//Device, DeviceContext 관리하는놈
class Graphics : public ISubsystem
{
public:
	Graphics(class Context* context);
	virtual ~Graphics();

	//Getter=================================================================
	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }
	//=======================================================================

	void Initialize() override;//DirecxtX 11 의 초기화
	void Update() override {} //여기서는 업데이트를 사용하지않지만 부모가 강제했기때문에 빈 함수를 만들어줌

	void ResizeClient(const uint& width, const uint& height); //백버퍼를 만들어주는 함수
	
	//=========더블버퍼링======================================================
	void BeginScene(); //그리기 시작하는 함수
	void EndScene(); //그린걸 출력하는 함수
	//========================================================================

private:
	ID3D11Device* device; // 뭔가 만드는놈
	ID3D11DeviceContext* deviceContext;// 뭔가 그리는놈(세팅하는놈)
	IDXGISwapChain* swapChain; // 더블 버퍼링

	//일단 넘어감
	ID3D11Debug* debugDevice;
	uint gpuMemorySize;
	wstring gpuDescription;
	uint numerator;
	uint denominator;

	D3DXCOLOR clearColor;//하나씩 지우면 처리비용이 비싸기때문에 색을 덮어씌워서 지움, 그때 사용하는 색상
	ID3D11DepthStencilView* depthStencilView; //메인 깊이버퍼
	ID3D11RenderTargetView* renderTargetView; // 매인 렌더타겟버퍼
	D3D11_VIEWPORT viewport;//렌더타겟을 윈도우창 어느 영역에 표시할지에 대한 좌표값, 보여질 영역
};