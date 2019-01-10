#pragma once

class Camera
{
public:
	Camera(class Context* context);
	virtual ~Camera();

	const D3DXVECTOR3& GetPosition() const { return position; }
	const D3DXMATRIX& GetViewMatrix() const { return view; }
	const D3DXMATRIX& GetProjectionMatrix() const { return projection; }

	void SetOrthographicLH
	(
		const float& w,
		const float& h,
		const float& zn,
		const float& zf
	);

	void SetOrthographicOffCenterLH
	(
		const float& left,
		const float& right,
		const float& bottom,
		const float& top,
		const float& zn,
		const float& zf
	);

	const D3DXVECTOR3 ScreenToWorldPoint(const D3DXVECTOR2& screenPoint);

	void Update();
	void BindPipeline();

private:
	class Context* context;
	class Timer* timer;
	class Input* input;
	class ConstantBuffer* cbuffer;

	//Vector : ũ��� ������ ������ ��
	//
	//direction �� position �� Vector �ϳ��� ǥ���Ϸ��� �ϴϱ� ������ �߻�!!
	//�̰� direction ���� position ������ �ȵ�
	//�׷��� ��ġ ��ǥ�踦 ����� : 3������ 1������ �߰��ؼ� 4���� ���� ���(w)
	//direction -> w = 0;
	//position -> w = 1;

	//ex)
	//��� = ����
	//1, 0, 0, 0, - x��
	//0, 1, 0, 0, - y��
	//0, 0, 1, 0, - z��
	//0, 0, 0, 1, - position
	
	//x  y  z

	D3DXVECTOR3 position; //ī�޶��� ���� ��ġ 
	D3DXVECTOR3 forward; //ī�޶��� ������� - z��
	D3DXVECTOR3 up; // ī�޶��� ���ʹ��� - y��
	D3DXVECTOR3 right;//ī�޶��� �������� - x��
	D3DXMATRIX view;//��������
	D3DXMATRIX projection;//��������
};