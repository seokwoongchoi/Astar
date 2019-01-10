#include "stdafx.h"
#include "Window.h"

function<void(const uint&, const uint&)> Window::OnResize = nullptr;

//윈도우 프로시져
//CALLBACK 함수 : 프로그래머 호출하는게아니라 시스템이 호출
LRESULT CALLBACK WndProc
(
	HWND handle, //윈도우의 핸들
	uint message, //메세지
	WPARAM wParam, //부가정보
	LPARAM lParam //부가정보
)
{
	//if (ImGui::WndProc(handle, message, wParam, lParam))
	//	return true;

	if (Input::MouseProc != nullptr)
		Input::MouseProc(message, wParam, lParam);

	//switch 문
	//case값에 변수를 넣을 수 없음
	switch (message)
	{
	case WM_SIZE: // 윈도우 창의 크기가 바뀌었을때
		if (Window::OnResize != nullptr && wParam != SIZE_MINIMIZED)
			Window::OnResize(lParam & 0xffff, (lParam >> 16) & 0xffff);
		break;
	case WM_CLOSE: // 윈도우창이 닫혔을때
	case WM_DESTROY:// 윈도우가 파괴됬을때
		PostQuitMessage(0); // 종료메세지를 날림
		break;
	default:
		//위에서 처리되지 않은 메세지를 처리
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}

Window::Window()
{
}

Window::~Window()
{
	if (Settings::Get()->GetIsFullScreen() == true)
		ChangeDisplaySettings(nullptr, 0);

	//윈도우 파괴
	DestroyWindow(Settings::Get()->GetWindowHandle());
	//등록해놓은 윈도우를 등록 해제
	UnregisterClass(Settings::Get()->GetAppName().c_str(), Settings::Get()->GetWindowInstance());
}

void Window::Initialize()
{
	//윈도우 클래스 만들기
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;//윈도우의 추가공간
	wndClass.cbWndExtra = 0;//윈도우의 추가공간
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //윈도우의 배경색
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);//커서
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);//아이콘
	wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);//작은아이콘
	wndClass.hInstance = Settings::Get()->GetWindowInstance();//윈도우의 실체
	wndClass.lpfnWndProc = (WNDPROC)WndProc; //윈도우 프로시져의 함수 포인터 //함수의 이름은 주소값
	wndClass.lpszClassName = Settings::Get()->GetAppName().c_str(); // 클래스이름
	wndClass.lpszMenuName = nullptr; // 메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // 윈도우 스타일
	wndClass.cbSize = sizeof(WNDCLASSEX);

	//윈도우 클래스 등록
	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);
	//디버그모드 일때만 동작
	//인자값이 false일때 중단, true이면 지나감

	if (Settings::Get()->GetIsFullScreen())
	{
		DEVMODE devMode;
		ZeroMemory(&devMode, sizeof(DEVMODE));

		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = static_cast<DWORD>(Settings::Get()->GetWidth());
		devMode.dmPelsHeight = static_cast<DWORD>(Settings::Get()->GetHeight());
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}

	DWORD option = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (Settings::Get()->GetIsFullScreen() == true)
		option |= WS_POPUP;
	else
		option |= WS_OVERLAPPEDWINDOW;

	//윈도우 생성
	HWND handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,//윈도우 스타일
		Settings::Get()->GetAppName().c_str(),//클래스명
		Settings::Get()->GetAppName().c_str(),//타이틀명
		option,
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y
		CW_USEDEFAULT,//width
		CW_USEDEFAULT,//height
		nullptr,
		nullptr,
		Settings::Get()->GetWindowInstance(),
		nullptr
	);
	assert(handle != nullptr);
	Settings::Get()->SetWindowHandle(handle);

	//윈도우 보여주기
	RECT rect;//left, top, right, bottom
	ZeroMemory(&rect, sizeof(RECT));

	rect.left = 0;
	rect.top = 0;
	rect.right = static_cast<LONG>(Settings::Get()->GetWidth());
	rect.bottom = static_cast<LONG>(Settings::Get()->GetHeight());

	uint centerX
		= static_cast<uint>
		(
			(GetSystemMetrics(SM_CXSCREEN) - Settings::Get()->GetWidth()) * 0.5f
		);
	uint centerY
		= static_cast<uint>
		(
			(GetSystemMetrics(SM_CYSCREEN) - Settings::Get()->GetHeight()) * 0.5f
		);

	//위에서만든 윈도우 RECT를 조정
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//윈도우창 이동
	MoveWindow
	(
		Settings::Get()->GetWindowHandle(),
		centerX,
		centerY,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		TRUE
	);

	//우리의 윈도우창을 화면 제일 앞에 띄움
	SetForegroundWindow(Settings::Get()->GetWindowHandle());
	
	//포커싱
	SetFocus(Settings::Get()->GetWindowHandle());

	//커서보이게
	ShowCursor(TRUE);

	//윈도우 보여주기
	ShowWindow(Settings::Get()->GetWindowHandle(), SW_SHOWNORMAL);
	
	//윈도우 업데이트
	UpdateWindow(Settings::Get()->GetWindowHandle());
}
