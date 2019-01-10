#pragma once
#include "BaseShader.h"

//ID3D11VertexShader* 의 래핑클래스
class VertexShader : public BaseShader
{
public:
	VertexShader(class Graphics* graphics);
	virtual ~VertexShader();

	//버텍스 셰이더 생성
	//디폴트매게변수 특징
	//값을 할당하지 않으면 대입하는 값이 들어감
	//함수 인자의 맨뒤에 위치해야함
	//한번 써주면됨(헤더든 Cpp 파일중 한곳에만 쓰면됨) -> 주로 헤더에 표기
	void CreateVertexShader(const string& shaderFilePath, const string& functionName = "VS");
	
	//레이아웃 생성
	void CreateInputLayout(ID3D11InputLayout* layout = nullptr);
	
	//파이프라인에 셋팅
	void BindPipeline();

private:
	//vsBlob(.hlsl 파일을 컴파일한 결과)을 분석해서 InputLayout을 만드는 함수
	//VS에서 기본데이터를 넘겨받기때문에 vsBlob을 분석함
	void Reflect();

private:
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;// hlsl 파일이 VS Stage 들어가기위해 변형하는 객체
	ID3D10Blob* vsBlob; //hlsl파일을 컴파일러가 컴파일하지않고 함수로 컴파일하는데 이때 컴파일 결과를 저장하는 값
};