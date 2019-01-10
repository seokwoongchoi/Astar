#include "stdafx.h"
#include "Window.h"

function<void(const uint&, const uint&)> Window::OnResize = nullptr;

//������ ���ν���
//CALLBACK �Լ� : ���α׷��� ȣ���ϴ°Ծƴ϶� �ý����� ȣ��
LRESULT CALLBACK WndProc
(
	HWND handle, //�������� �ڵ�
	uint message, //�޼���
	WPARAM wParam, //�ΰ�����
	LPARAM lParam //�ΰ�����
)
{
	//if (ImGui::WndProc(handle, message, wParam, lParam))
	//	return true;

	if (Input::MouseProc != nullptr)
		Input::MouseProc(message, wParam, lParam);

	//switch ��
	//case���� ������ ���� �� ����
	switch (message)
	{
	case WM_SIZE: // ������ â�� ũ�Ⱑ �ٲ������
		if (Window::OnResize != nullptr && wParam != SIZE_MINIMIZED)
			Window::OnResize(lParam & 0xffff, (lParam >> 16) & 0xffff);
		break;
	case WM_CLOSE: // ������â�� ��������
	case WM_DESTROY:// �����찡 �ı�������
		PostQuitMessage(0); // ����޼����� ����
		break;
	default:
		//������ ó������ ���� �޼����� ó��
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

	//������ �ı�
	DestroyWindow(Settings::Get()->GetWindowHandle());
	//����س��� �����츦 ��� ����
	UnregisterClass(Settings::Get()->GetAppName().c_str(), Settings::Get()->GetWindowInstance());
}

void Window::Initialize()
{
	//������ Ŭ���� �����
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;//�������� �߰�����
	wndClass.cbWndExtra = 0;//�������� �߰�����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�������� ����
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);//Ŀ��
	wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);//������
	wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);//����������
	wndClass.hInstance = Settings::Get()->GetWindowInstance();//�������� ��ü
	wndClass.lpfnWndProc = (WNDPROC)WndProc; //������ ���ν����� �Լ� ������ //�Լ��� �̸��� �ּҰ�
	wndClass.lpszClassName = Settings::Get()->GetAppName().c_str(); // Ŭ�����̸�
	wndClass.lpszMenuName = nullptr; // �޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // ������ ��Ÿ��
	wndClass.cbSize = sizeof(WNDCLASSEX);

	//������ Ŭ���� ���
	WORD wHr = RegisterClassEx(&wndClass);
	assert(wHr != 0);
	//����׸�� �϶��� ����
	//���ڰ��� false�϶� �ߴ�, true�̸� ������

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

	//������ ����
	HWND handle = CreateWindowEx
	(
		WS_EX_APPWINDOW,//������ ��Ÿ��
		Settings::Get()->GetAppName().c_str(),//Ŭ������
		Settings::Get()->GetAppName().c_str(),//Ÿ��Ʋ��
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

	//������ �����ֱ�
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

	//���������� ������ RECT�� ����
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//������â �̵�
	MoveWindow
	(
		Settings::Get()->GetWindowHandle(),
		centerX,
		centerY,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		TRUE
	);

	//�츮�� ������â�� ȭ�� ���� �տ� ���
	SetForegroundWindow(Settings::Get()->GetWindowHandle());
	
	//��Ŀ��
	SetFocus(Settings::Get()->GetWindowHandle());

	//Ŀ�����̰�
	ShowCursor(TRUE);

	//������ �����ֱ�
	ShowWindow(Settings::Get()->GetWindowHandle(), SW_SHOWNORMAL);
	
	//������ ������Ʈ
	UpdateWindow(Settings::Get()->GetWindowHandle());
}
