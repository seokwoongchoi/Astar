#pragma once
#include "IResource.h"

class Effect : public IResource
{
public:
	Effect(class Context* context);
	virtual ~Effect();

	const bool& GetIsExist() const { return bExist; }

	void SetIsExist(const bool& bExist) { this->bExist = bExist; }
	void SetPosition(const D3DXVECTOR3& position) { transform->SetWorldPosition(position); }
	void SetScale(const D3DXVECTOR3& scale) { transform->SetWorldScale(scale); }
	void SetTexture(const string& filePath);
	void SetAnimation(const string& filePath);

	void Update();
	void Render();

	void Write(Xml::XMLDocument& doc) override {}
	void Read(Xml::XMLElement* element) override {}

	void SaveToFile(const string& saveFilePath) override;
	void LoadFromFile(const string& loadFilePath) override;

private:
	ResourceManager* resourceManager;

	Shader* shader;
	Texture2D* texture;
	Mesh* mesh;
	class SpriteAnimator* animator;
	Transform* transform;
	BlendState* state;
	bool bExist;
};