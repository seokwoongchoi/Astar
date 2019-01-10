#include "stdafx.h"
#include "App.h"
#include "../Framework/Core/Window.h"

App::App()
{
	//������ ������ �ʱ�ȭ
	window = new Window();
	window->Initialize();

	//context ������ ����ý��� ���
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
	MSG msg; // �޼��������� ���� ����ü
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
	while (true) // ���η���(���ѷ���)
	{
		//�޼����� ������ �Ѿ
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)//������� �޼����� ������ 
				break;// while�� Ż��

			TranslateMessage(&msg);//Ű���� �Է°��� ���ؼ���
			DispatchMessage(&msg);//WndProc, ���������ν����� �޼��� ����
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
					// �׸��� ����
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
