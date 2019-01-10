#include "stdafx.h"
#include "Effect.h"
#include "../Component/Animator.h"

Effect::Effect(Context * context)
	: IResource(context)
	, texture(nullptr)
	, bExist(false)
{
	resourceManager = context->GetSubsystem<ResourceManager>();

	shader = resourceManager->LoadFromFile<Shader>("Sprite.hlsl");
	mesh = resourceManager->LoadFromFile<Mesh>("Quad");
	animator = new SpriteAnimator(context);
	transform = new Transform(context);
	state = new BlendState(context->GetSubsystem<Graphics>());
	state->AlphaToCoverageEnable(true);
}

Effect::~Effect()
{
	SAFE_DELETE(state);
	SAFE_DELETE(transform);
	SAFE_DELETE(animator);
}

void Effect::SetTexture(const string & filePath)
{
	texture = resourceManager->LoadFromFile<Texture2D>(filePath);
}

void Effect::SetAnimation(const string & filePath)
{
	animator->RegistAnimation(filePath);
	animator->SetCurrentAnimation(0);
	animator->Play();
}

void Effect::Update()
{
	if (bExist)
	{
		animator->Update();
		if (!animator->GetIsPlaying())
			bExist = false;
	}
}

void Effect::Render()
{
	if (bExist)
	{
		state->BindPipeline();
		shader->BindPipeline();
		mesh->BindPipeline();
		animator->BindPipeline();
		transform->BindPipeline();

		texture->SetPS(0);

		auto graphics = context->GetSubsystem<Graphics>();
		graphics->GetDeviceContext()->DrawIndexed
		(
			mesh->GetIndexCount(), 0, 0
		);
		state->UnbindPipeline();
	}
}

void Effect::SaveToFile(const string & saveFilePath)
{
}

void Effect::LoadFromFile(const string & loadFilePath)
{
}
