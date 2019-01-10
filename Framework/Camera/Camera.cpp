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

	//���� ����� �׳ɾ��� ����ķ� �ʱ�ȭ��(����� - ��� ���Ұ� 0�� ���)
	//������� �׳� ���ϸ� ������ ������� �����⶧���� �� �� �� ����
	//�׷��� �ڱ��ڽſ� ���ص� �ڱ��ڽ��� ������ �������(�׵����)�� ����
	//�װ� ������ִ� �Լ��� D3DXMatrixIdentity() �Լ���

	//�������(�׵����) : E
	//1, 0, 0, 0,
	//0, 1, 0, 0,
	//0, 0, 1, 0,
	//0, 0, 0, 1,

	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&projection);

	//�þ߰����� ������ִ� ��
	//LH : Left Hand
	//LHC(�޼���ǥ��)		: UpVector - +y, FrontVector - +z, RightVector - +x
	//RHC(��������ǥ��)	: UpVector - +y, FrontVector - -z, RightVector - +x 


	//Cross(����)�� �� :  �ι����� ������ ����(��ǥ�迡 ���� ���������� ������ �ٸ�)
	//D3DXVec3Cross();
	
	//Dot(����)�� �� : �ι����� cos_theta ��
	//D3DXVec3Dot();
	D3DXMatrixLookAtLH
	(
		&view,//���� ���� �þ߰���
		&position,//ī�޶��� ��ġ
		&(position + forward), //ī�޶� ���� ����
		&up//ī�޶��� ������
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
	//����� ��ġ�����ִ� �Լ� : ��ġ����� ��ȯ����
	//��ġ��� : ��� ���� ������ ���
	//M_T
	//���⼭ ����� ��ġ���ִ� ������
	//���̴��� ���켱 ����� ����ϰ� DX�� ��켱 ����� ����ϱ⶧����
	//��� �ӵ��� �� ���� ���̴��� �츮�� �����ֱ����� ��ġ�� ����
	D3DXMatrixTranspose(&data->View, &view);  
	D3DXMatrixTranspose(&data->Projection, &projection);
	cbuffer->Unmap();
	cbuffer->SetVS(0);
}
