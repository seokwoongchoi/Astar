#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Context * context)
	: context(context)
	, position(0, 0, 0)
	, forward(0, 0, 1)
	, up(0, 1, 0)
	, right(1, 0, 0)
{
	timer = context->GetSubsystem<Timer>();
	input = context->GetSubsystem<Input>();

	//원래 행렬을 그냥쓰면 영행렬로 초기화됨(영행렬 - 모든 원소가 0인 행렬)
	//영행렬을 그냥 곱하면 무조건 영행렬이 나오기때문에 쓸 수 가 없음
	//그래서 자기자신에 곱해도 자기자신이 나오는 단위행렬(항등행렬)을 만듬
	//그걸 만들어주는 함수가 D3DXMatrixIdentity() 함수임

	//단위행렬(항등행렬) : E
	//1, 0, 0, 0,
	//0, 1, 0, 0,
	//0, 0, 1, 0,
	//0, 0, 0, 1,

	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	//시야공간을 만들어주는 놈
	//LH : Left Hand
	//LHC(왼손좌표계)		: UpVector - +y, FrontVector - +z, RightVector - +x
	//RHC(오른손좌표계)	: UpVector - +y, FrontVector - -z, RightVector - +x 


	//Cross(외적)의 값 :  두백터의 수직인 벡터(좌표계에 따라 수직백터의 방향이 다름)
	//D3DXVec3Cross();
	
	//Dot(내적)의 값 : 두백터의 cos_theta 값
	//D3DXVec3Dot();
	D3DXMatrixLookAtLH
	(
		&view,//내가 만들 시야공간
		&position,//카메라의 위치
		&(position + forward), //카메라가 보는 방향
		&up//카메라의 윗방향
	);

	cbuffer = new ConstantBuffer(context->GetSubsystem<Graphics>());
	cbuffer->Create<CameraData>();
}

Camera::~Camera()
{
	SAFE_DELETE(cbuffer);
}

void Camera::SetOrthographicLH(const float & w, const float & h, const float & zn, const float & zf)
{
	D3DXMatrixOrthoLH(&projection, w, h, zn, zf);
}

void Camera::SetOrthographicOffCenterLH(const float & left, const float & right, const float & bottom, const float & top, const float & zn, const float & zf)
{
	D3DXMatrixOrthoOffCenterLH(&projection, left, right, bottom, top, zn, zf);
}

const D3DXVECTOR3 Camera::ScreenToWorldPoint(const D3DXVECTOR2 & screenPoint)
{
	D3D11_VIEWPORT viewport = Settings::Get()->GetViewport();

	//Convert Screen pixel to view space
	float pointX = +2.0f * screenPoint.x / viewport.Width - 1.0f;
	float pointY = -2.0f * screenPoint.y / viewport.Height + 1.0f;

	//Unprojection point
	D3DXMATRIX unprojection;
	D3DXMatrixInverse(&unprojection, nullptr, &(view * projection));

	D3DXVECTOR3 worldPoint;
	D3DXVec3TransformCoord(&worldPoint, &D3DXVECTOR3(pointX, pointY, 1.0), &unprojection);

	return worldPoint;
}

void Camera::Update()
{
	if (input->KeyPress(VK_SHIFT))
	{
		if (input->KeyPress(VK_W))
			position += up * 200.0f * timer->GetDeltaTimeSec();
		else if (input->KeyPress(VK_S))
			position += -up * 200.0f * timer->GetDeltaTimeSec();

		if (input->KeyPress(VK_A))
			position += -right * 200.0f * timer->GetDeltaTimeSec();
		else if (input->KeyPress(VK_D))
			position += right * 200.0f * timer->GetDeltaTimeSec();

		D3DXMatrixLookAtLH(&view, &position, &(position + forward), &up);
	}
}

void Camera::BindPipeline()
{
	auto data = static_cast<CameraData*>(cbuffer->Map());
	//행렬을 전치시켜주는 함수 : 전치행렬을 반환해줌
	//전치행렬 : 행과 열을 뒤집은 행렬
	//M_T
	//여기서 행렬을 전치해주는 이유는
	//셰이더는 열우선 행렬을 사용하고 DX는 행우선 행렬을 사용하기때문에
	//계산 속도가 더 빠른 셰이더에 우리가 맞춰주기위해 전치를 해줌
	D3DXMatrixTranspose(&data->View, &view);  
	D3DXMatrixTranspose(&data->Projection, &projection);
	cbuffer->Unmap();
	cbuffer->SetVS(0);
}
