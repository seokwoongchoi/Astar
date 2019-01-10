#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader(Graphics * graphics)
	: BaseShader(graphics)
	, inputLayout(nullptr)
	, vertexShader(nullptr)
	, vsBlob(nullptr)
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(inputLayout);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(vsBlob);
}

void VertexShader::CreateVertexShader(const string & shaderFilePath, const string & functionName)
{
	this->shaderFilePath = shaderFilePath;
	this->functionName = functionName;

	ID3D10Blob* error;
	HRESULT hr = D3DX11CompileFromFileA // hlsl ������ �������ϴ� �Լ�(A : const char* // W : cosnt wchar*
	(
		shaderFilePath.c_str(), //hlsl ���ϰ��
		nullptr,
		nullptr,
		functionName.c_str(), //���̴��� �����Լ��̸�(�����Լ� �̸�)
		"vs_5_0",//���̴� ����
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&vsBlob, //�� �Լ����� �������� ����� ������ ��
		&error, //�� �Լ����� �������� ����� ���е����͸� �����ϴ� ��
		nullptr
	);
	assert(CheckShaderError(hr, error));

	//ID3D11VertexShader* ����
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),//������ �����ּ�
		vsBlob->GetBufferSize(),//������ ������
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(error);
}

void VertexShader::CreateInputLayout(ID3D11InputLayout * layout)
{
	//layout���� null�̸� �츮�� ID3D11InputLayout�� �����
	//null�̾ƴ϶�� layout�� �̹� ������� ���°��̱� ������ �׳� �װ� ���

	//layout�� ���Դٴ°� ���ؽ� �����͸� �������� layout�� �����
	//- �츮�� �������� D3D11_INPUT_ELEMENT_DESC�� �������� ����⶧���� �ű⿡ ����س��� �ø�ƽ �̸���
	//- ���̴��� �ۼ��Ҷ� ����� �ø�ƽ �̸��� ������ ���ƾ��Ѵ�

	//layout�� �ȵ��Դٴ°� ���̴��� �������� layout�� �����

	if (!inputLayout)
		Reflect();
	else
		inputLayout = layout;
}

void VertexShader::BindPipeline()
{
	graphics->GetDeviceContext()->IASetInputLayout(inputLayout);
	graphics->GetDeviceContext()->VSSetShader(vertexShader, nullptr, 0);
}

void VertexShader::Reflect()
{
	//vsBlob�� nullptr �̸� �ߴ�
	if (!vsBlob)
		assert(false);

	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescs;
	// ���ؽ� ���̴��� �м��ؼ� ���ؽ��� ���ʵ����͸� ������ �����迭
	// ���������� �̳��������� InputLayout�� ����

	ID3D11ShaderReflection* reflector = nullptr;
	//vsBlob�� �м����ִ� �༮

	//Create Shader Reflection
	HRESULT hr = D3DReflect
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		IID_ID3D11ShaderReflection, //IID : �������̽� ���̵�
		reinterpret_cast<void**>(&reflector)
	);
	assert(SUCCEEDED(hr));

	//Get Shader Information
	D3D11_SHADER_DESC shaderDesc;
	reflector->GetDesc(&shaderDesc);//Desc�� �������� �Լ�

	//Read Vertex Shader
	for (uint i = 0; i < shaderDesc.InputParameters; i++)
	{
		//InputParameters : ���ؽ� ���̴��� ���ڷ� �޴� �Ű������� ����


		//vsBlob�� ������ ��� �������ִ� reflector����
		//�Ķ���� �ε����� ����� �Ķ���� ������ ������´�
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		reflector->GetInputParameterDesc(i, &paramDesc);

		string semanticName = paramDesc.SemanticName;
		D3D11_INPUT_ELEMENT_DESC elementDesc;


		if (semanticName.find("Instance") != string::npos)
		{
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 1;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //�˾Ƽ� �����ͻ���� ��������
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // �̰��� ���ؽ� �����ͷ� ����ϰڴٴ� ��
			elementDesc.InstanceDataStepRate = 1; //
		}
		else
		{
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //�˾Ƽ� �����ͻ���� ��������
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // �̰��� ���ؽ� �����ͷ� ����ϰڴٴ� ��
			elementDesc.InstanceDataStepRate = 0;
		}

		//Check DXGI FORMAT
		//�ٸ� �Ķ������ �ø�ƽ �̸��� ������� �ᵵ������
		//POSITION�� ������ POSITION���� �������
		string temp = elementDesc.SemanticName;
		if (temp == "POSITION") //���� ���� �Ķ������ �ø�ƽ �̸��� POSITION �̶�� Vector3 ������ ���
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		else if (paramDesc.Mask == 1) //�׳� ������ ����� �����ϴ� ���м� �����θ� �˸��
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT; //��ȣ�� ���� ������(���)
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT; //��ȣ�� �ִ� ������(����, ���)
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		inputLayoutDescs.push_back(elementDesc);
	}

	//Create InputLayout
	hr = graphics->GetDevice()->CreateInputLayout
	(
		inputLayoutDescs.data(),
		inputLayoutDescs.size(),
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		&inputLayout
	);
	assert(SUCCEEDED(hr));
	SAFE_RELEASE(reflector);
}
