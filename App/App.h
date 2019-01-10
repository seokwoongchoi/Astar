#pragma once

class App
{
public:
	App();//생성자 -> 초기화
	virtual ~App();//소멸자 -> 지울때
	//상속이 될수도 있기때문에 소멸자 앞에 virtual 붙임
	//상속시에 부모 소멸자에 virtual이 안붙어 있으면 자식소멸자가 호출이 안됨

	//우리 프로그램의 메인 루프
	virtual WPARAM Run();

	//순수가상함수 - 몸체가 없다
	//자식클래스에서 무조건 재정의 되야한다 : 오버라이딩
	virtual void Initialize() = 0; //초기화
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0; // 후처리
	virtual void Destroy() = 0; //삭제

protected:
	//메인 시스템
	class Window* window; // 윈도우 생성
	class Context* context; // 서브시스템 관리
};