#include "stdafx.h"
#include "EffectManager.h"
#include "../../Resource/Effect.h"

EffectManager::EffectManager(Context * context)
	: ISubsystem(context)
{
}

EffectManager::~EffectManager()
{
	effects.clear();
	effects.shrink_to_fit();
}

void EffectManager::AddEffect(const string & effectFilePath, const D3DXVECTOR3 & position, const D3DXVECTOR3 & scale)
{
	auto resourceManager = context->GetSubsystem<ResourceManager>();
	auto effect = resourceManager->LoadFromFile<Effect>(effectFilePath);

	effect->SetPosition(position);
	effect->SetScale(scale);
	effect->SetIsExist(true);

	effects.push_back(effect);
}

void EffectManager::AddEffect(const string & textureFilePath, const string & animationFilePath, const D3DXVECTOR3 & position, const D3DXVECTOR3 & scale)
{
	auto resourceManager = context->GetSubsystem<ResourceManager>();
	auto effect = new Effect(context);

	effect->SetTexture(textureFilePath);
	effect->SetAnimation(animationFilePath);
	effect->SetPosition(position);
	effect->SetScale(scale);
	effect->SetIsExist(true);

	resourceManager->RegistResource(effect);
	effects.push_back(effect);
}

void EffectManager::Update()
{
	for (uint i = 0; i < effects.size();)
	{
		effects[i]->Update();
		if (!effects[i]->GetIsExist())
			effects.erase(effects.begin() + i);
		else
			i++;
	}
}

void EffectManager::Render()
{
	for (auto effect : effects)
		effect->Render();
}
