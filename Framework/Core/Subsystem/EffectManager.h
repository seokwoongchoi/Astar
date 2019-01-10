#pragma once
#include "ISubsystem.h"

class EffectManager : public ISubsystem
{
public:
	EffectManager(class Context* context);
	virtual ~EffectManager();

	void AddEffect
	(
		const string& effectFilePath,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& scale = D3DXVECTOR3(1, 1, 1)
	);

	void AddEffect
	(
		const string& textureFilePath,
		const string& animationFilePath,
		const D3DXVECTOR3& position,
		const D3DXVECTOR3& scale = D3DXVECTOR3(1, 1, 1)
	);

	void Initialize() override {}
	void Update() override;
	void Render();

private:
	vector<class Effect*> effects;
};