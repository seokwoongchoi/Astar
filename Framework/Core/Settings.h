#pragma once

//디자인패턴 중 Singleton Pattern 사용
// - 전역적으로 사용할 수있다
// - 인스턴스(실체) 하나만 존제하도록 제한한다

//C++ -> OOP(Object Oriented Programming) : 객체지향프로그래밍
// - 캡슐화 : 데이터를 숨길수있다(private - 나만, protected - 나랑 자식이랑, public - 우리모두)
// - 추상화 : 순수가상함수
// - 다형성 : 오버로딩 -> 중복정의, 오버라이딩 -> 재정의 // 추상클래스를 상속받았을때
// - 상속 : 

// 반환값 함수이름(매개변수)
class Settings
{
public:
	//함수 앞에 staitc 키워드가 붙으면 전역으로 사용할 수 있다는 뜻
	//그러나 private 키워드 안에있으면 전역으로 쓸수없다
	static Settings* Get();
	static void Delete();

public:
	//Gatter Function
	//private 영역에 바로 접근을 못하니까 
	const wstring& GetAppName() const { return appName; }
	HINSTANCE GetWindowInstance() const { return hInstance; }
	HWND GetWindowHandle() const { return handle; }
	const float& GetWidth() const { return width; }
	const float& GetHeight() const { return height; }
	const bool& GetIsVsync() const { return bVsync; }
	const bool& GetIsFullScreen() const { return bFullScreen; }
	const D3D11_VIEWPORT& GetViewport() const { return viewport; }

	//Setter Function
	void SetAppName(const wstring& appName) { this->appName = appName; }
	void SetWindowInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }
	void SetWidth(const float& width) { this->width = width; }
	void SetHeight(const float& height) { this->height = height; }
	void SetIsVsync(const bool& bVsync) { this->bVsync = bVsync; }
	void SetIsFullScreen(const bool& bFullScreen) { this->bFullScreen = bFullScreen; }
	void SetViewport(const D3D11_VIEWPORT& viewport) { this->viewport = viewport; }

private:
	//싱글톤패턴을 사용하기때문에
	//외부에서 객체를 만수들 수 없도록 봉인
	Settings();
	virtual ~Settings() {}

private:
	//static 붙는 변수 : 정적변수
	//클래스 내부에있지만 전역변수
	//전역변수 이기때문에 컴파일단계에서 메모리 할당
	static Settings* instance;

	//멤버변수
	wstring appName;
	HINSTANCE hInstance;
	HWND handle;
	float width;
	float height;
	bool bVsync;
	bool bFullScreen;

	D3D11_VIEWPORT viewport;
};