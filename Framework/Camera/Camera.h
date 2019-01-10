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

	//Vector : 크기와 방향을 가지는 값
	//
	//direction 과 position 을 Vector 하나로 표현하려고 하니까 문제가 발생!!
	//이게 direction 인지 position 구분이 안됨
	//그래서 동치 좌표계를 사용함 : 3차원에 1차원을 추가해서 4차원 값을 사용(w)
	//direction -> w = 0;
	//position -> w = 1;

	//ex)
	//행렬 = 공간
	//1, 0, 0, 0, - x축
	//0, 1, 0, 0, - y축
	//0, 0, 1, 0, - z축
	//0, 0, 0, 1, - position
	
	//x  y  z

	D3DXVECTOR3 position; //카메라의 현재 위치 
	D3DXVECTOR3 forward; //카메라의 정면방향 - z축
	D3DXVECTOR3 up; // 카메라의 윗쪽방향 - y축
	D3DXVECTOR3 right;//카메라의 우측방향 - x축
	D3DXMATRIX view;//시점공간
	D3DXMATRIX projection;//투영공간
};