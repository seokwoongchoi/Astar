#include "stdafx.h"
#include "./App/Game.h"

// ---------Object------------
//  Class           Instance
//  설계도          설계도로 만들어진 실체

//우리 프로그램의 진입점, 여기서부터 프로그램 시작
int APIENTRY WinMain
(
	HINSTANCE hInstance, // 윈도우창의 실체의 핸들, 핸들 - 인식표(정수형)
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow
)
{
	//시드 초기화
	//이걸 안해주면 rand함수에서 같은값이 나옴
	srand(static_cast<uint>(time(nullptr)));

	//전역적으로 사용할 우리 프로그램의 기본값들
	Settings::Get()->SetAppName(L"D2D11Game");
	Settings::Get()->SetWindowInstance(hInstance);
	Settings::Get()->SetWindowHandle(nullptr);
	Settings::Get()->SetWidth(1280);
	Settings::Get()->SetHeight(720);
	Settings::Get()->SetIsVsync(false);
	Settings::Get()->SetIsFullScreen(false);

	//실질적인 게임로직이 들어있는 객체
	App* game = new Game();

	WPARAM wParam = game->Run();

	SAFE_DELETE(game);
	return wParam;
}