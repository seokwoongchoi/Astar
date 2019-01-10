#pragma once
#include "ISubsystem.h"

//Pipeline -> �⺻ �������͸� �����ؼ� ������ִ� �帧
//Directx11 ������ Pipeline �� Stage�� ����

//IA : �⺻�����͸� �Է¹���
//IA <----- ID3D11Buffer* -----�⺻������(Vertex) : VertexBuffer
//   <----- ID3D11Buffer* -----�⺻������(Index)  : IndexBuffer
//   <----- ID3D11InputLayout* ----- Vertex ���� ����
//   <----- Primitive Topology ----- Vertex �� � ���·� ó���Ұ�����

//VS : ���� ��ȯ(Local->World->View->Projection)
//VS - cbuffer(b0) <----- ID3D11Buffer* ----- Data : ConstantBuffer
//VS - Texture2D(t0) <----- ID3D11ShaderResourceView* ----- ID3D11Texture2D*
//VS - SamlerState(s0) <----- ID3D11SamplerState*

//RS : ��ȯ�� ������ ��� ü����(�׸���) 
//RS <------ ID3D11RasterizerState*
//   FrontCouterClockWise : �ո��� �Ǵ� ����(true - �ݽð�, false - �ð�)
//	 CullMode : CullFront, CullBack, CullNoe - ������ ���� fccw�� �������� ��� �ڸ���
//   FillMode : Wireframe, Solid

//PS : ��ȯ�� ������ RS���� ���� ������� �ȼ��� ����
//PS - cbuffer(b0) <----- ID3D11Buffer* ----- Data : ConstantBuffer
//PS - Texture2D(t0) <----- ID3D11ShaderResourceView* ----- ID3D11Texture2D*
//PS - SamlerState(s0) <----- ID3D11SamplerState*

//OM : ����Ÿ�ٵ鿡 �׷��� ����۵��� ����
//OM <----- ID3D11RenderTargetView* <----- ID3D11Texture*
//OM <----- ID3D11DepthStencilView* <----- ID3D11Texture*
//OM : ����Ÿ�ٺ�� �������ٽǺ� �ΰ��� ����ϴ� ������ 
//	   ����Ÿ�ٺ� �ϳ������δ� ���������� ������ �� �� ��� �������ٽ� �並 �߰��� ���
//     D3DXVECTOR3 -> x, y, z-->����
//OM : ID3D11BlendState*


//Pipeline�� ��� �������� DrawCall�� ����� �׷���
//Draw : VertexBuffer ������ �׸��� ��
//DrawIndices : VertexBuffer�� IndexBuffer �� ������ �׸��³�

//Device, DeviceContext �����ϴ³�
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

	void Initialize() override;//DirecxtX 11 �� �ʱ�ȭ
	void Update() override {} //���⼭�� ������Ʈ�� ������������� �θ� �����߱⶧���� �� �Լ��� �������

	void ResizeClient(const uint& width, const uint& height); //����۸� ������ִ� �Լ�
	
	//=========������۸�======================================================
	void BeginScene(); //�׸��� �����ϴ� �Լ�
	void EndScene(); //�׸��� ����ϴ� �Լ�
	//========================================================================

private:
	ID3D11Device* device; // ���� ����³�
	ID3D11DeviceContext* deviceContext;// ���� �׸��³�(�����ϴ³�)
	IDXGISwapChain* swapChain; // ���� ���۸�

	//�ϴ� �Ѿ
	ID3D11Debug* debugDevice;
	uint gpuMemorySize;
	wstring gpuDescription;
	uint numerator;
	uint denominator;

	D3DXCOLOR clearColor;//�ϳ��� ����� ó������� ��α⶧���� ���� ������� ����, �׶� ����ϴ� ����
	ID3D11DepthStencilView* depthStencilView; //���� ���̹���
	ID3D11RenderTargetView* renderTargetView; // ���� ����Ÿ�ٹ���
	D3D11_VIEWPORT viewport;//����Ÿ���� ������â ��� ������ ǥ�������� ���� ��ǥ��, ������ ����
};