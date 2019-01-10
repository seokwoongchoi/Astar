#include "stdafx.h"
#include "Settings.h"

//함수 내부에있으면 메모리할당이 객체가 생성될때(런타임단계에서) 할당되기때문에
//전역공간에서 미리 할당해줘야한다
Settings* Settings::instance = nullptr;

Settings * Settings::Get()
{
	if (!instance)
		instance = new Settings();

	return instance;
}

void Settings::Delete()
{
	SAFE_DELETE(instance);
}

//이니셜라이즈 -> 객체의 생성과 동시에 초기화가 일어남
//참조자는 무조건 이니셜라이즈에서 초기화 해야한다

//* -> 포인터는 생성만 해놔도 상관없음
//& -> 공간을 참조하는 놈이기때문에 생성과 동시에 할당이 일어나야함
Settings::Settings()
	: appName(L"")
	, hInstance(nullptr)
	, handle(nullptr)
	, width(0)
	, height(0)
	, bVsync(true)
	, bFullScreen(false)
{
}
