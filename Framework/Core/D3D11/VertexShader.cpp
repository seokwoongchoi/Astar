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
	HRESULT hr = D3DX11CompileFromFileA // hlsl 파일을 컴파일하는 함수(A : const char* // W : cosnt wchar*
	(
		shaderFilePath.c_str(), //hlsl 파일경로
		nullptr,
		nullptr,
		functionName.c_str(), //셰이더의 메인함수이름(진입함수 이름)
		"vs_5_0",//셰이더 버전
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&vsBlob, //이 함수에서 컴파일한 결과를 저장할 값
		&error, //이 함수에서 컴파일한 결과중 실패데이터를 저장하는 값
		nullptr
	);
	assert(CheckShaderError(hr, error));

	//ID3D11VertexShader* 생성
	hr = graphics->GetDevice()->CreateVertexShader
	(
		vsBlob->GetBufferPointer(),//버퍼의 시작주소
		vsBlob->GetBufferSize(),//버퍼의 사이즈
		nullptr,
		&vertexShader
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(error);
}

void VertexShader::CreateInputLayout(ID3D11InputLayout * layout)
{
	//layout값이 null이면 우리가 ID3D11InputLayout을 만든다
	//null이아니라면 layout이 이미 만들어져 들어온것이기 때문에 그냥 그걸 사용

	//layout이 들어왔다는건 버텍스 데이터를 기준으로 layout을 만든것
	//- 우리가 만들어놓은 D3D11_INPUT_ELEMENT_DESC를 기준으로 만들기때문에 거기에 등록해놓은 시멘틱 이름과
	//- 셰이더를 작성할때 사용한 시멘틱 이름이 무조건 같아야한다

	//layout이 안들어왔다는건 셰이더를 기준으로 layout을 만든것

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
	//vsBlob이 nullptr 이면 중단
	if (!vsBlob)
		assert(false);

	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescs;
	// 버텍스 셰이더를 분석해서 버텍스의 기초데이터를 저장할 동적배열
	// 최종적으로 이놈을가지고 InputLayout을 만듬

	ID3D11ShaderReflection* reflector = nullptr;
	//vsBlob을 분석해주는 녀석

	//Create Shader Reflection
	HRESULT hr = D3DReflect
	(
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		IID_ID3D11ShaderReflection, //IID : 인터페이스 아이디
		reinterpret_cast<void**>(&reflector)
	);
	assert(SUCCEEDED(hr));

	//Get Shader Information
	D3D11_SHADER_DESC shaderDesc;
	reflector->GetDesc(&shaderDesc);//Desc를 꺼내오는 함수

	//Read Vertex Shader
	for (uint i = 0; i < shaderDesc.InputParameters; i++)
	{
		//InputParameters : 버텍스 셰이더가 인자로 받는 매개변수의 갯수


		//vsBlob의 정보를 모두 가지고있는 reflector에서
		//파라미터 인덱스에 연결된 파라미터 정보를 가지고온다
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		reflector->GetInputParameterDesc(i, &paramDesc);

		string semanticName = paramDesc.SemanticName;
		D3D11_INPUT_ELEMENT_DESC elementDesc;


		if (semanticName.find("Instance") != string::npos)
		{
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 1;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //알아서 데이터사이즈를 정렬해줌
			elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA; // 이값을 버텍스 데이터로 사용하겠다는 뜻
			elementDesc.InstanceDataStepRate = 1; //
		}
		else
		{
			elementDesc.SemanticName = paramDesc.SemanticName;
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;
			elementDesc.InputSlot = 0;
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT; //알아서 데이터사이즈를 정렬해줌
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA; // 이값을 버텍스 데이터로 사용하겠다는 뜻
			elementDesc.InstanceDataStepRate = 0;
		}

		//Check DXGI FORMAT
		//다른 파라미터의 시멘틱 이름은 마음대로 써도되지만
		//POSITION은 무조건 POSITION으로 써줘야함
		string temp = elementDesc.SemanticName;
		if (temp == "POSITION") //만약 현제 파라미터의 시멘틱 이름이 POSITION 이라면 Vector3 포멧을 사용
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		else if (paramDesc.Mask == 1) //그냥 데이터 사이즈를 구분하는 구분선 정도로만 알면됨
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT; //부호가 없는 정수형(양수)
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT; //부호가 있는 정수형(음수, 양수)
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
