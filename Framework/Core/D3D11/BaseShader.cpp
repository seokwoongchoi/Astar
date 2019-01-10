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
	if (FAILED(hr)) //hr값이 실패값 일때 true, 성공값일떄 false
	{
		if (error != nullptr)
		{
			//error안에 hlsl파일 어디에서 문제가있는지 적혀있음
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
