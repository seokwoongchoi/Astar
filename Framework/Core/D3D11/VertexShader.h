#pragma once
#include "BaseShader.h"

//ID3D11VertexShader* �� ����Ŭ����
class VertexShader : public BaseShader
{
public:
	VertexShader(class Graphics* graphics);
	virtual ~VertexShader();

	//���ؽ� ���̴� ����
	//����Ʈ�ŰԺ��� Ư¡
	//���� �Ҵ����� ������ �����ϴ� ���� ��
	//�Լ� ������ �ǵڿ� ��ġ�ؾ���
	//�ѹ� ���ָ��(����� Cpp ������ �Ѱ����� �����) -> �ַ� ����� ǥ��
	void CreateVertexShader(const string& shaderFilePath, const string& functionName = "VS");
	
	//���̾ƿ� ����
	void CreateInputLayout(ID3D11InputLayout* layout = nullptr);
	
	//���������ο� ����
	void BindPipeline();

private:
	//vsBlob(.hlsl ������ �������� ���)�� �м��ؼ� InputLayout�� ����� �Լ�
	//VS���� �⺻�����͸� �Ѱܹޱ⶧���� vsBlob�� �м���
	void Reflect();

private:
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;// hlsl ������ VS Stage �������� �����ϴ� ��ü
	ID3D10Blob* vsBlob; //hlsl������ �����Ϸ��� �����������ʰ� �Լ��� �������ϴµ� �̶� ������ ����� �����ϴ� ��
};