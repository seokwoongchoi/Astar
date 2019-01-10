#include "stdafx.h"
#include "App.h"
#include "../Framework/Core/Window.h"

App::App()
{
	//윈도우 생성과 초기화
	window = new Window();
	window->Initialize();

	//context 생성과 서브시스템 등록
	context = new Context();
	context->RegistSubsystem(new Graphics(context));
	context->RegistSubsystem(new DirectWrite(context));
	context->RegistSubsystem(new Timer(context));
	context->RegistSubsystem(new Input(context));
	context->RegistSubsystem(new SceneManager(context));
	context->RegistSubsystem(new ResourceManager(context));
	context->RegistSubsystem(new Audio(context));
	context->RegistSubsystem(new EffectManager(context));
	context->RegistSubsystem(new ColliderManager(context));
}

App::~App()
{
	SAFE_DELETE(context);
	SAFE_DELETE(window);
}

WPARAM App::Run()
{
	MSG msg; // 메세지정보를 담은 구조체
	ZeroMemory(&msg, sizeof(MSG));

	auto graphics = context->GetSubsystem<Graphics>();
	auto writer = context->GetSubsystem<DirectWrite>();

	ImGui::Create
	(
		Settings::Get()->GetWindowHandle(), 
		graphics->GetDevice(), 
		graphics->GetDeviceContext()
	);
	ImGui::StyleColorsDark();

	Initialize();
	while (true) // 메인루프(무한루프)
	{
		//메세지가 없으면 넘어감
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)//나가라는 메세지가 들어오면 
				break;// while문 탈출

			TranslateMessage(&msg);//키보드 입력값을 재해석함
			DispatchMessage(&msg);//WndProc, 윈도우프로시져로 메세지 전달
		}
		else
		{
			// Update-> Render-> Update-> Render ......

			Update();
			Render();
			ImGui::Update();

			////Demo
			//bool bDemoRender = true;
			//if (bDemoRender)
			//ImGui::ShowDemoWindow(&bDemoRender);

			graphics->BeginScene();
			{
				writer->BeginTextDraw();
				{
					// 그리기 시작
					PostRender();
					ImGui::Render();
				}
				writer->EndTextDraw();
			}
			graphics->EndScene();
		}
	}
	Destroy();
	ImGui::Delete();

	return msg.wParam;
}
