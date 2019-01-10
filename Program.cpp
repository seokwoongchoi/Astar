#include "stdafx.h"
#include "./App/Game.h"

// ---------Object------------
//  Class           Instance
//  ���赵          ���赵�� ������� ��ü

//�츮 ���α׷��� ������, ���⼭���� ���α׷� ����
int APIENTRY WinMain
(
	HINSTANCE hInstance, // ������â�� ��ü�� �ڵ�, �ڵ� - �ν�ǥ(������)
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	//�õ� �ʱ�ȭ
	//�̰� �����ָ� rand�Լ����� �������� ����
	srand(static_cast<uint>(time(nullptr)));

	//���������� ����� �츮 ���α׷��� �⺻����
	Settings::Get()->SetAppName(L"D2D11Game");
	Settings::Get()->SetWindowInstance(hInstance);
	Settings::Get()->SetWindowHandle(nullptr);
	Settings::Get()->SetWidth(1280);
	Settings::Get()->SetHeight(720);
	Settings::Get()->SetIsVsync(false);
	Settings::Get()->SetIsFullScreen(false);

	//�������� ���ӷ����� ����ִ� ��ü
	App* game = new Game();

	WPARAM wParam = game->Run();

	SAFE_DELETE(game);
	return wParam;
}