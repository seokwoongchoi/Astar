#include "stdafx.h"
#include "BaseShader.h"

BaseShader::BaseShader(Graphics * graphics)
	: graphics(graphics)
	, shaderFilePath("")
	, functionName("")
{
}

bool BaseShader::CheckShaderError(const HRESULT & hr, ID3D10Blob * error)
{
	if (FAILED(hr)) //hr���� ���а� �϶� true, �������ϋ� false
	{
		if (error != nullptr)
		{
			//error�ȿ� hlsl���� ��𿡼� �������ִ��� ��������
			//LPVOID : void*
			string str = reinterpret_cast<const char*>(error->GetBufferPointer());
			MessageBoxA
			(
				Settings::Get()->GetWindowHandle(),
				str.c_str(),
				"Shader Error!!!",
				MB_OK
			);
		}
		return false;
	}

	return true;
}
