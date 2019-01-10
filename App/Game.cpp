#include "stdafx.h"
#include "Game.h"
#include "../Framework/Scene/Scene.h"
#include "../Framework/Camera/Camera.h"

void Game::Initialize()
{
	sceneManager = context->GetSubsystem<SceneManager>();
	effectManager = context->GetSubsystem<EffectManager>();
	resourceManager = context->GetSubsystem<ResourceManager>();

	sceneManager->RegistScene("First", new Scene(context));
	sceneManager->SetCurrentScene("First");

	camera = new Camera(context);
	camera->SetOrthographicLH
	(
		Settings::Get()->GetWidth(),
		Settings::Get()->GetHeight(),
		0,
		1
	);

	shader = resourceManager->LoadFromFile<Shader>("Texture.hlsl");
	mesh = resourceManager->LoadFromFile<Mesh>("ScreenQuad");

	renderTexture = new RenderTexture(context->GetSubsystem<Graphics>());
	renderTexture->Create
	(
		Settings::Get()->GetWidth(),
		Settings::Get()->GetHeight()
	);
}

void Game::Update()
{
	context->UpdateSubsystems();
}

void Game::Render()
{
	renderTexture->SetRenderTarget();
	renderTexture->Clear();

	sceneManager->Render();
	effectManager->Render();

	if (context->GetSubsystem<Input>()->KeyDown(VK_SPACE))
		renderTexture->Save("Wowwwwww.png");
}

void Game::PostRender()
{
	camera->BindPipeline();
	shader->BindPipeline();
	mesh->BindPipeline();

	auto graphics = context->GetSubsystem<Graphics>();
	auto srv = renderTexture->GetShaderResourceView();
	graphics->GetDeviceContext()->PSSetShaderResources(0, 1, &srv);
	graphics->GetDeviceContext()->DrawIndexed(mesh->GetIndexCount(), 0, 0);

	ImGui::Begin("FPS");
	ImGui::Text("%f", ImGui::GetIO().Framerate);
	ImGui::End();
}

void Game::Destroy()
{
	SAFE_DELETE(renderTexture);
	SAFE_DELETE(camera);
}
