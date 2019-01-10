#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "../Camera/Camera.h"
#include "../Component/Grid.h"
#include "../Component/Collider.h"
#include "../Tilemap/Tilemap.h"

Scene::Scene(Context* context)
	: context(context)
{
	//Create Camera
	camera = new Camera(context);
	camera->SetOrthographicOffCenterLH
	(
		0.0f,
		Settings::Get()->GetWidth(),
		0.0f,
		Settings::Get()->GetHeight(),
		0,
		1
	);

	tilemap = new Tilemap(context);
	tilemap->Create(1280, 720);
}

Scene::~Scene()
{
	SAFE_DELETE(tilemap);
	SAFE_DELETE(camera);
}

void Scene::Update()
{
	camera->Update();
	tilemap->Update(camera);

	if (context->GetSubsystem<Input>()->KeyDown(VK_SPACE))
	{
		tilemap->FindPath(camera);
	}
}

void Scene::Render()
{
	camera->BindPipeline();
	tilemap->Render();
}

